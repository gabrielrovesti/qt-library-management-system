#include "jsonpersistencemanager.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTextStream>

JsonPersistenceManager::JsonPersistenceManager() {
}

bool JsonPersistenceManager::saveLibrary(const QString &filePath, const QVector<AbstractMedia*> &mediaList) {
    QJsonObject root;
    QJsonArray mediaArray = mediaListToJsonArray(mediaList);
    root["library"] = mediaArray;
    
    QJsonDocument doc(root);
    QFile file(filePath);
    
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return false;
    }
    
    QTextStream out(&file);
    out << doc.toJson();
    file.close();
    
    return true;
}

QVector<AbstractMedia*> JsonPersistenceManager::loadLibrary(const QString &filePath) {
    QFile file(filePath);
    
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return QVector<AbstractMedia*>();
    }
    
    QByteArray data = file.readAll();
    file.close();
    
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (doc.isNull() || !doc.isObject()) {
        return QVector<AbstractMedia*>();
    }
    
    QJsonObject root = doc.object();
    QJsonArray mediaArray = root["library"].toArray();
    
    return jsonArrayToMediaList(mediaArray);
}

QJsonArray JsonPersistenceManager::mediaListToJsonArray(const QVector<AbstractMedia*> &mediaList) {
    QJsonArray array;
    
    for (const AbstractMedia *media : mediaList) {
        array.append(media->toJson());
    }
    
    return array;
}

QVector<AbstractMedia*> JsonPersistenceManager::jsonArrayToMediaList(const QJsonArray &array) {
    QVector<AbstractMedia*> mediaList;
    
    for (const QJsonValue &val : array) {
        if (val.isObject()) {
            AbstractMedia *media = AbstractMedia::fromJson(val.toObject());
            if (media) {
                mediaList.append(media);
            }
        }
    }
    
    return mediaList;
}