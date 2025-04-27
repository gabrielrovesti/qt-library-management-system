#ifndef MEDIAVISITOR_H
#define MEDIAVISITOR_H

class Book;
class Movie;
class Magazine;
class EBook;

class MediaVisitor {
public:
    virtual ~MediaVisitor() = default;
    
    virtual void visit(Book &book) = 0;
    virtual void visit(Movie &movie) = 0;
    virtual void visit(Magazine &magazine) = 0;
    virtual void visit(EBook &ebook) = 0;
};

#endif // MEDIAVISITOR_H