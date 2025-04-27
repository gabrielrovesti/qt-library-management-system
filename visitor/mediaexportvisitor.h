#ifndef MEDIAEXPORTVISITOR_H
#define MEDIAEXPORTVISITOR_H

#include "mediavisitor.h"
#include <QString>
#include <QStringList>

class MediaExportVisitor : public MediaVisitor {
private:
    QString format; // "csv", "xml", "text"
    QStringList result;
    
public:
    MediaExportVisitor(const QString &format = "text");
    
    void visit(Book &book) override;
    void visit(Movie &movie) override;
    void visit(Magazine &magazine) override;
    void visit(EBook &ebook) override;
    
    QString getResult() const;
    void setFormat(const QString &format);
};

#endif // MEDIAEXPORTVISITOR_H