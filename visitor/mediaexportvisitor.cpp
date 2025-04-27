#include "mediaexportvisitor.h"
#include "../model/book.h"
#include "../model/movie.h"
#include "../model/magazine.h"
#include "../model/ebook.h"
#include <QTextStream>

MediaExportVisitor::MediaExportVisitor(const QString &format)
    : format(format) {
}

void MediaExportVisitor::visit(Book &book) {
    if (format == "csv") {
        QString line = QString("%1,%2,%3,%4,%5,%6,%7,%8")
            .arg(book.getId())
            .arg(book.getTitle().replace(",", "\\,"))
            .arg(book.getAuthor().replace(",", "\\,"))
            .arg(book.getIsbn())
            .arg(book.getPublisher().replace(",", "\\,"))
            .arg(book.getReleaseDate().toString("yyyy-MM-dd"))
            .arg(book.getPageCount())
            .arg(book.getGenre().replace(",", "\\,"));
        result.append(line);
    } 
    else if (format == "xml") {
        QString xml;
        QTextStream stream(&xml);
        stream << "<book id=\"" << book.getId() << "\">\n";
        stream << "  <title>" << book.getTitle().toHtmlEscaped() << "</title>\n";
        stream << "  <author>" << book.getAuthor().toHtmlEscaped() << "</author>\n";
        stream << "  <isbn>" << book.getIsbn() << "</isbn>\n";
        stream << "  <publisher>" << book.getPublisher().toHtmlEscaped() << "</publisher>\n";
        stream << "  <releaseDate>" << book.getReleaseDate().toString("yyyy-MM-dd") << "</releaseDate>\n";
        stream << "  <pageCount>" << book.getPageCount() << "</pageCount>\n";
        stream << "  <genre>" << book.getGenre().toHtmlEscaped() << "</genre>\n";
        stream << "  <description>" << book.getDescription().toHtmlEscaped() << "</description>\n";
        stream << "</book>";
        result.append(xml);
    } 
    else { // text
        QString text;
        QTextStream stream(&text);
        stream << "Book: " << book.getTitle() << "\n";
        stream << "ID: " << book.getId() << "\n";
        stream << "Author: " << book.getAuthor() << "\n";
        stream << "ISBN: " << book.getIsbn() << "\n";
        stream << "Publisher: " << book.getPublisher() << "\n";
        stream << "Release Date: " << book.getReleaseDate().toString("yyyy-MM-dd") << "\n";
        stream << "Pages: " << book.getPageCount() << "\n";
        stream << "Genre: " << book.getGenre() << "\n";
        stream << "Description:\n" << book.getDescription() << "\n";
        result.append(text);
    }
}

void MediaExportVisitor::visit(Movie &movie) {
    // Implementazione simile a Book ma con attributi specifici di Movie
    // ...
}

void MediaExportVisitor::visit(Magazine &magazine) {
    // Implementazione simile a Book ma con attributi specifici di Magazine
    // ...
}

void MediaExportVisitor::visit(EBook &ebook) {
    // Implementazione simile a Book ma con attributi specifici di EBook
    // ...
}

QString MediaExportVisitor::getResult() const {
    return result.join("\n");
}

void MediaExportVisitor::setFormat(const QString &format) {
    this->format = format;
    result.clear();
}