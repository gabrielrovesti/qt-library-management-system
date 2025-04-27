#ifndef JSONPERSISTENCEMANAGER_H
#define JSONPERSISTENCEMANAGER_H

#include <QString>
#include <QVector>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include "../model/abstractmedia.h"

class JsonPersistenceManager {
public:
    JsonPersistenceManager();
    
    bool saveLibrary(const QString &filePath, const QVector<AbstractMedia*> &mediaList);
    QVector<AbstractMedia*> loadLibrary(const QString &filePath);
    
private:
    QJsonArray mediaListToJsonArray(const QVector<AbstractMedia*> &mediaList);
    QVector<AbstractMedia*> jsonArrayToMediaList(const QJsonArray &array);
};

#endif // JSONPERSISTENCEMANAGER_H