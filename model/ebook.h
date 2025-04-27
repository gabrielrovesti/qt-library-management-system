#ifndef EBOOK_H
#define EBOOK_H

#include "abstractmedia.h"

class EBook : public AbstractMedia {
private:
    QString author;
    QString isbn;
    int pageCount;
    QString format; // PDF, EPUB, etc.
    float fileSizeMB;
    
public:
    EBook(int id, const QString &title, const QDate &releaseDate,
          const QString &publisher, const QString &description,
          const QString &coverPath, const QString &author,
          const QString &isbn, int pageCount, const QString &format,
          float fileSizeMB);
    
    // Getters
    QString getAuthor() const;
    QString getIsbn() const;
    int getPageCount() const;
    QString getFormat() const;
    float getFileSizeMB() const;
    
    // Setters
    void setAuthor(const QString &author);
    void setIsbn(const QString &isbn);
    void setPageCount(int count);
    void setFormat(const QString &format);
    void setFileSizeMB(float size);
    
    // Implementazione metodi virtuali
    QString getMediaType() const override;
    void accept(MediaVisitor &visitor) override;
    
    // Serializzazione/deserializzazione
    QJsonObject toJson() const override;
    static EBook* fromJson(const QJsonObject &json);
};

#endif // EBOOK_H