#ifndef BOOK_H
#define BOOK_H

#include "abstractmedia.h"

class Book : public AbstractMedia {
private:
    QString author;
    QString isbn;
    int pageCount;
    QString genre;
    
public:
    Book(int id, const QString &title, const QDate &releaseDate,
         const QString &publisher, const QString &description,
         const QString &coverPath, const QString &author,
         const QString &isbn, int pageCount, const QString &genre);
    
    // Getters
    QString getAuthor() const;
    QString getIsbn() const;
    int getPageCount() const;
    QString getGenre() const;
    
    // Setters
    void setAuthor(const QString &author);
    void setIsbn(const QString &isbn);
    void setPageCount(int count);
    void setGenre(const QString &genre);
    
    // Implementazione metodi virtuali
    QString getMediaType() const override;
    void accept(MediaVisitor &visitor) override;
    
    // Serializzazione/deserializzazione
    QJsonObject toJson() const override;
    static Book* fromJson(const QJsonObject &json);
};

#endif // BOOK_H