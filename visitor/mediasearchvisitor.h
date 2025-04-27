#ifndef MEDIASEARCHVISITOR_H
#define MEDIASEARCHVISITOR_H

#include "mediavisitor.h"
#include <QString>

class MediaSearchVisitor : public MediaVisitor {
private:
    QString query;
    bool caseSensitive;
    bool matchFound;
    
public:
    MediaSearchVisitor(const QString &query, bool caseSensitive = false);
    
    void visit(Book &book) override;
    void visit(Movie &movie) override;
    void visit(Magazine &magazine) override;
    void visit(EBook &ebook) override;
    
    bool isMatch() const;
    void setQuery(const QString &query);
    void setCaseSensitive(bool sensitive);
};

#endif // MEDIASEARCHVISITOR_H