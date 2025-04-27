#include "book.h"
#include "../visitor/mediavisitor.h"

Book::Book(int id, const QString &title, const QDate &releaseDate,
         const QString &publisher, const QString &description,
         const QString &coverPath, const QString &author,
         const QString &isbn, int pageCount, const QString &genre)
    : AbstractMedia(id, title, releaseDate, publisher, description, coverPath),
      author(author), isbn(isbn), pageCount(pageCount), genre(genre) {
}

QString Book::getAuthor() const {
    return author;
}

QString Book::getIsbn() const {
    return isbn;
}

int Book::getPageCount() const {
    return pageCount;
}

QString Book::getGenre() const {
    return genre;
}

void Book::setAuthor(const QString &author) {
    this->author = author;
}

void Book::setIsbn(const QString &isbn) {
    this->isbn = isbn;
}

void Book::setPageCount(int count) {
    this->pageCount = count;
}

void Book::setGenre(const QString &genre) {
    this->genre = genre;
}

QString Book::getMediaType() const {
    return "Book";
}

void Book::accept(MediaVisitor &visitor) {
    visitor.visit(*this);
}

QJsonObject Book::toJson() const {
    QJsonObject json = AbstractMedia::toJson();
    json["type"] = "Book";
    json["author"] = author;
    json["isbn"] = isbn;
    json["pageCount"] = pageCount;
    json["genre"] = genre;
    return json;
}

Book* Book::fromJson(const QJsonObject &json) {
    if (json["type"].toString() != "Book") {
        return nullptr;
    }
    
    return new Book(
        json["id"].toInt(),
        json["title"].toString(),
        QDate::fromString(json["releaseDate"].toString(), Qt::ISODate),
        json["publisher"].toString(),
        json["description"].toString(),
        json["coverPath"].toString(),
        json["author"].toString(),
        json["isbn"].toString(),
        json["pageCount"].toInt(),
        json["genre"].toString()
    );
}