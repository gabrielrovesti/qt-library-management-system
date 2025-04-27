#include "ebook.h"
#include "../visitor/mediavisitor.h"

EBook::EBook(int id, const QString &title, const QDate &releaseDate,
          const QString &publisher, const QString &description,
          const QString &coverPath, const QString &author,
          const QString &isbn, int pageCount, const QString &format,
          float fileSizeMB)
    : AbstractMedia(id, title, releaseDate, publisher, description, coverPath),
      author(author), isbn(isbn), pageCount(pageCount), format(format),
      fileSizeMB(fileSizeMB) {
}

QString EBook::getAuthor() const {
    return author;
}

QString EBook::getIsbn() const {
    return isbn;
}

int EBook::getPageCount() const {
    return pageCount;
}

QString EBook::getFormat() const {
    return format;
}

float EBook::getFileSizeMB() const {
    return fileSizeMB;
}

void EBook::setAuthor(const QString &author) {
    this->author = author;
}

void EBook::setIsbn(const QString &isbn) {
    this->isbn = isbn;
}

void EBook::setPageCount(int count) {
    this->pageCount = count;
}

void EBook::setFormat(const QString &format) {
    this->format = format;
}

void EBook::setFileSizeMB(float size) {
    this->fileSizeMB = size;
}

QString EBook::getMediaType() const {
    return "EBook";
}

void EBook::accept(MediaVisitor &visitor) {
    visitor.visit(*this);
}

QJsonObject EBook::toJson() const {
    QJsonObject json = AbstractMedia::toJson();
    json["type"] = "EBook";
    json["author"] = author;
    json["isbn"] = isbn;
    json["pageCount"] = pageCount;
    json["format"] = format;
    json["fileSizeMB"] = fileSizeMB;
    return json;
}

EBook* EBook::fromJson(const QJsonObject &json) {
    if (json["type"].toString() != "EBook") {
        return nullptr;
    }
    
    return new EBook(
        json["id"].toInt(),
        json["title"].toString(),
        QDate::fromString(json["releaseDate"].toString(), Qt::ISODate),
        json["publisher"].toString(),
        json["description"].toString(),
        json["coverPath"].toString(),
        json["author"].toString(),
        json["isbn"].toString(),
        json["pageCount"].toInt(),
        json["format"].toString(),
        json["fileSizeMB"].toDouble()
    );
}