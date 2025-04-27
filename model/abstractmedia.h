#ifndef ABSTRACTMEDIA_H
#define ABSTRACTMEDIA_H

#include <QString>
#include <QDate>
#include <QJsonObject>

class MediaVisitor;

class AbstractMedia {
private:
    int id;
    QString title;
    QDate releaseDate;
    QString publisher;
    QString description;
    QString coverPath;

public:
    AbstractMedia(int id, const QString &title, const QDate &releaseDate,
                 const QString &publisher, const QString &description,
                 const QString &coverPath);
    virtual ~AbstractMedia();
    
    // Getters
    int getId() const;
    QString getTitle() const;
    QDate getReleaseDate() const;
    QString getPublisher() const;
    QString getDescription() const;
    QString getCoverPath() const;
    
    // Setters
    void setTitle(const QString &title);
    void setReleaseDate(const QDate &date);
    void setPublisher(const QString &publisher);
    void setDescription(const QString &description);
    void setCoverPath(const QString &path);
    
    // Metodi virtuali puri
    virtual QString getMediaType() const = 0;
    virtual void accept(MediaVisitor &visitor) = 0;
    
    // Serializzazione/deserializzazione
    virtual QJsonObject toJson() const;
    static AbstractMedia* fromJson(const QJsonObject &json);
};

#endif // ABSTRACTMEDIA_H