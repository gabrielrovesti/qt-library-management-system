#include "mediasearchvisitor.h"
#include "../model/book.h"
#include "../model/movie.h"
#include "../model/magazine.h"
#include "../model/ebook.h"

MediaSearchVisitor::MediaSearchVisitor(const QString &query, bool caseSensitive)
    : query(query), caseSensitive(caseSensitive), matchFound(false) {
}

void MediaSearchVisitor::visit(Book &book) {
    Qt::CaseSensitivity cs = caseSensitive ? Qt::CaseSensitive : Qt::CaseInsensitive;
    
    // Check if query is in any relevant field
    matchFound = book.getTitle().contains(query, cs) ||
                 book.getAuthor().contains(query, cs) ||
                 book.getIsbn().contains(query, cs) ||
                 book.getPublisher().contains(query, cs) ||
                 book.getDescription().contains(query, cs) ||
                 book.getGenre().contains(query, cs);
}

void MediaSearchVisitor::visit(Movie &movie) {
    Qt::CaseSensitivity cs = caseSensitive ? Qt::CaseSensitive : Qt::CaseInsensitive;
    
    // Check if query is in any relevant field
    matchFound = movie.getTitle().contains(query, cs) ||
                 movie.getDirector().contains(query, cs) ||
                 movie.getCast().contains(query, cs) ||
                 movie.getPublisher().contains(query, cs) ||
                 movie.getDescription().contains(query, cs);
}

void MediaSearchVisitor::visit(Magazine &magazine) {
    Qt::CaseSensitivity cs = caseSensitive ? Qt::CaseSensitive : Qt::CaseInsensitive;
    
    // Check if query is in any relevant field
    matchFound = magazine.getTitle().contains(query, cs) ||
                 magazine.getIssue().contains(query, cs) ||
                 magazine.getPublisher().contains(query, cs) ||
                 magazine.getDescription().contains(query, cs) ||
                 magazine.getTopic().contains(query, cs);
}

void MediaSearchVisitor::visit(EBook &ebook) {
    Qt::CaseSensitivity cs = caseSensitive ? Qt::CaseSensitive : Qt::CaseInsensitive;
    
    // Check if query is in any relevant field
    matchFound = ebook.getTitle().contains(query, cs) ||
                 ebook.getAuthor().contains(query, cs) ||
                 ebook.getIsbn().contains(query, cs) ||
                 ebook.getPublisher().contains(query, cs) ||
                 ebook.getDescription().contains(query, cs) ||
                 ebook.getFormat().contains(query, cs);
}

bool MediaSearchVisitor::isMatch() const {
    return matchFound;
}

void MediaSearchVisitor::setQuery(const QString &query) {
    this->query = query;
    matchFound = false;
}

void MediaSearchVisitor::setCaseSensitive(bool sensitive) {
    caseSensitive = sensitive;
}