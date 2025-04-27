#include "abstractmedia.h"
#include "book.h"
#include "movie.h"
#include "magazine.h"
#include "ebook.h"

AbstractMedia::AbstractMedia(int id, const QString &title, const QDate &releaseDate,
                           const QString &publisher, const QString &description,
                           const QString &coverPath)
    : id(id), title(title), releaseDate(releaseDate), publisher(publisher),
      description(description), coverPath(coverPath) {
}

AbstractMedia::~AbstractMedia() {
}

int AbstractMedia::getId() const {
    return id;
}

QString AbstractMedia::getTitle() const {
    return title;
}

QDate AbstractMedia::getReleaseDate() const {
    return releaseDate;
}

QString AbstractMedia::getPublisher() const {
    return publisher;
}

QString AbstractMedia::getDescription() const {
    return description;
}

QString AbstractMedia::getCoverPath() const {
    return coverPath;
}

void AbstractMedia::setTitle(const QString &title) {
    this->title = title;
}

void AbstractMedia::setReleaseDate(const QDate &date) {
    this->releaseDate = date;
}

void AbstractMedia::setPublisher(const QString &publisher) {
    this->publisher = publisher;
}

void AbstractMedia::setDescription(const QString &description) {
    this->description = description;
}

void AbstractMedia::setCoverPath(const QString &path) {
    this->coverPath = path;
}

QJsonObject AbstractMedia::toJson() const {
    QJsonObject json;
    json["id"] = id;
    json["title"] = title;
    json["releaseDate"] = releaseDate.toString(Qt::ISODate);
    json["publisher"] = publisher;
    json["description"] = description;
    json["coverPath"] = coverPath;
    return json;
}

AbstractMedia* AbstractMedia::fromJson(const QJsonObject &json) {
    QString type = json["type"].toString();
    
    if (type == "Book") {
        return Book::fromJson(json);
    } else if (type == "Movie") {
        return Movie::fromJson(json);
    } else if (type == "Magazine") {
        return Magazine::fromJson(json);
    } else if (type == "EBook") {
        return EBook::fromJson(json);
    }
    
    return nullptr;
}