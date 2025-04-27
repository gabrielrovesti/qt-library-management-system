#ifndef MAGAZINE_H
#define MAGAZINE_H

#include "abstractmedia.h"

class Magazine : public AbstractMedia {
private:
    QString issue;
    int volume;
    int issueNumber;
    QString topic;
    
public:
    Magazine(int id, const QString &title, const QDate &releaseDate,
             const QString &publisher, const QString &description,
             const QString &coverPath, const QString &issue,
             int volume, int issueNumber, const QString &topic);
    
    // Getters
    QString getIssue() const;
    int getVolume() const;
    int getIssueNumber() const;
    QString getTopic() const;
    
    // Setters
    void setIssue(const QString &issue);
    void setVolume(int volume);
    void setIssueNumber(int issueNumber);
    void setTopic(const QString &topic);
    
    // Implementazione metodi virtuali
    QString getMediaType() const override;
    void accept(MediaVisitor &visitor) override;
    
    // Serializzazione/deserializzazione
    QJsonObject toJson() const override;
    static Magazine* fromJson(const QJsonObject &json);
};

#endif // MAGAZINE_H