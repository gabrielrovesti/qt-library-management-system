#include "movie.h"
#include "../visitor/mediavisitor.h"

Movie::Movie(int id, const QString &title, const QDate &releaseDate,
          const QString &publisher, const QString &description,
          const QString &coverPath, const QString &director,
          int duration, const QString &cast)
    : AbstractMedia(id, title, releaseDate, publisher, description, coverPath),
      director(director), duration(duration), cast(cast) {
}

QString Movie::getDirector() const {
    return director;
}

int Movie::getDuration() const {
    return duration;
}

QString Movie::getCast() const {
    return cast;
}

void Movie::setDirector(const QString &director) {
    this->director = director;
}

void Movie::setDuration(int duration) {
    this->duration = duration;
}

void Movie::setCast(const QString &cast) {
    this->cast = cast;
}

QString Movie::getMediaType() const {
    return "Movie";
}

void Movie::accept(MediaVisitor &visitor) {
    visitor.visit(*this);
}

QJsonObject Movie::toJson() const {
    QJsonObject json = AbstractMedia::toJson();
    json["type"] = "Movie";
    json["director"] = director;
    json["duration"] = duration;
    json["cast"] = cast;
    return json;
}

Movie* Movie::fromJson(const QJsonObject &json) {
    if (json["type"].toString() != "Movie") {
        return nullptr;
    }
    
    return new Movie(
        json["id"].toInt(),
        json["title"].toString(),
        QDate::fromString(json["releaseDate"].toString(), Qt::ISODate),
        json["publisher"].toString(),
        json["description"].toString(),
        json["coverPath"].toString(),
        json["director"].toString(),
        json["duration"].toInt(),
        json["cast"].toString()
    );
}