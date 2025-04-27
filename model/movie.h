#ifndef MOVIE_H
#define MOVIE_H

#include "abstractmedia.h"

class Movie : public AbstractMedia {
private:
    QString director;
    int duration; // in minutes
    QString cast;
    
public:
    Movie(int id, const QString &title, const QDate &releaseDate,
          const QString &publisher, const QString &description,
          const QString &coverPath, const QString &director,
          int duration, const QString &cast);
    
    // Getters
    QString getDirector() const;
    int getDuration() const;
    QString getCast() const;
    
    // Setters
    void setDirector(const QString &director);
    void setDuration(int duration);
    void setCast(const QString &cast);
    
    // Implementazione metodi virtuali
    QString getMediaType() const override;
    void accept(MediaVisitor &visitor) override;
    
    // Serializzazione/deserializzazione
    QJsonObject toJson() const override;
    static Movie* fromJson(const QJsonObject &json);
};

#endif // MOVIE_H