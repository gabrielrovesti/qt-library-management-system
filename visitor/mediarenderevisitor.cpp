#include "mediarenderervisitor.h"
#include "../model/book.h"
#include "../model/movie.h"
#include "../model/magazine.h"
#include "../model/ebook.h"
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPixmap>
#include <QFont>

MediaRendererVisitor::MediaRendererVisitor(const QString &mode)
    : resultWidget(nullptr), renderMode(mode) {
}

MediaRendererVisitor::~MediaRendererVisitor() {
    // Il widget verrà distrutto dal suo parent
}

void MediaRendererVisitor::visit(Book &book) {
    // Se c'era un widget precedente, lo distruggiamo
    if (resultWidget) {
        delete resultWidget;
        resultWidget = nullptr;
    }
    
    resultWidget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(resultWidget);
    
    if (renderMode == "detail") {
        // Visualizzazione dettagliata
        QHBoxLayout *headerLayout = new QHBoxLayout();
        layout->addLayout(headerLayout);
        
        // Immagine di copertina
        QLabel *coverLabel = new QLabel();
        QPixmap coverPixmap(book.getCoverPath());
        if (coverPixmap.isNull()) {
            coverPixmap = QPixmap(":/images/book_placeholder.png");
        }
        coverLabel->setPixmap(coverPixmap.scaled(200, 300, Qt::KeepAspectRatio));
        headerLayout->addWidget(coverLabel);
        
        // Dettagli
        QVBoxLayout *detailsLayout = new QVBoxLayout();
        headerLayout->addLayout(detailsLayout);
        
        QLabel *titleLabel = new QLabel(book.getTitle());
        QFont titleFont = titleLabel->font();
        titleFont.setPointSize(16);
        titleFont.setBold(true);
        titleLabel->setFont(titleFont);
        detailsLayout->addWidget(titleLabel);
        
        QLabel *authorLabel = new QLabel("Author: " + book.getAuthor());
        detailsLayout->addWidget(authorLabel);
        
        QLabel *publisherLabel = new QLabel("Publisher: " + book.getPublisher());
        detailsLayout->addWidget(publisherLabel);
        
        QLabel *dateLabel = new QLabel("Published: " + book.getReleaseDate().toString("yyyy-MM-dd"));
        detailsLayout->addWidget(dateLabel);
        
        QLabel *isbnLabel = new QLabel("ISBN: " + book.getIsbn());
        detailsLayout->addWidget(isbnLabel);
        
        QLabel *pagesLabel = new QLabel("Pages: " + QString::number(book.getPageCount()));
        detailsLayout->addWidget(pagesLabel);
        
        QLabel *genreLabel = new QLabel("Genre: " + book.getGenre());
        detailsLayout->addWidget(genreLabel);
        
        detailsLayout->addStretch();
        
        // Descrizione
        QLabel *descriptionTitle = new QLabel("Description:");
        QFont descFont = descriptionTitle->font();
        descFont.setBold(true);
        descriptionTitle->setFont(descFont);
        layout->addWidget(descriptionTitle);
        
        QLabel *descriptionLabel = new QLabel(book.getDescription());
        descriptionLabel->setWordWrap(true);
        layout->addWidget(descriptionLabel);
    } 
    else if (renderMode == "summary") {
        // Visualizzazione sommaria
        QHBoxLayout *summaryLayout = new QHBoxLayout();
        layout->addLayout(summaryLayout);
        
        QLabel *coverLabel = new QLabel();
        QPixmap coverPixmap(book.getCoverPath());
        if (coverPixmap.isNull()) {
            coverPixmap = QPixmap(":/images/book_placeholder.png");
        }
        coverLabel->setPixmap(coverPixmap.scaled(100, 150, Qt::KeepAspectRatio));
        summaryLayout->addWidget(coverLabel);
        
        QVBoxLayout *infoLayout = new QVBoxLayout();
        summaryLayout->addLayout(infoLayout);
        
        QLabel *titleLabel = new QLabel(book.getTitle());
        QFont titleFont = titleLabel->font();
        titleFont.setBold(true);
        titleLabel->setFont(titleFont);
        infoLayout->addWidget(titleLabel);
        
        QLabel *authorLabel = new QLabel("by " + book.getAuthor());
        infoLayout->addWidget(authorLabel);
        
        QLabel *yearLabel = new QLabel(book.getReleaseDate().toString("yyyy"));
        infoLayout->addWidget(yearLabel);
        
        infoLayout->addStretch();
    }
    else if (renderMode == "list") {
        // Visualizzazione a lista
        QHBoxLayout *listLayout = new QHBoxLayout();
        layout->addLayout(listLayout);
        
        QLabel *iconLabel = new QLabel();
        QPixmap icon(":/images/book_icon.png");
        if (icon.isNull()) {
            icon = QPixmap(16, 16);
            icon.fill(Qt::transparent);
        }
        iconLabel->setPixmap(icon);
        listLayout->addWidget(iconLabel);
        
        QLabel *titleLabel = new QLabel(book.getTitle() + " - " + book.getAuthor());
        listLayout->addWidget(titleLabel);
        
        listLayout->addStretch();
    }
}

void MediaRendererVisitor::visit(Movie &movie) {
    // Implementazione simile a Book ma con attributi specifici di Movie
    if (resultWidget) {
        delete resultWidget;
        resultWidget = nullptr;
    }
    
    resultWidget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(resultWidget);
    
    if (renderMode == "detail") {
        // Visualizzazione dettagliata
        QHBoxLayout *headerLayout = new QHBoxLayout();
        layout->addLayout(headerLayout);
        
        // Immagine di copertina
        QLabel *coverLabel = new QLabel();
        QPixmap coverPixmap(movie.getCoverPath());
        if (coverPixmap.isNull()) {
            coverPixmap = QPixmap(":/images/movie_placeholder.png");
        }
        coverLabel->setPixmap(coverPixmap.scaled(200, 300, Qt::KeepAspectRatio));
        headerLayout->addWidget(coverLabel);
        
        // Dettagli
        QVBoxLayout *detailsLayout = new QVBoxLayout();
        headerLayout->addLayout(detailsLayout);
        
        QLabel *titleLabel = new QLabel(movie.getTitle());
        QFont titleFont = titleLabel->font();
        titleFont.setPointSize(16);
        titleFont.setBold(true);
        titleLabel->setFont(titleFont);
        detailsLayout->addWidget(titleLabel);
        
        QLabel *directorLabel = new QLabel("Director: " + movie.getDirector());
        detailsLayout->addWidget(directorLabel);
        
        QLabel *publisherLabel = new QLabel("Studio: " + movie.getPublisher());
        detailsLayout->addWidget(publisherLabel);
        
        QLabel *dateLabel = new QLabel("Released: " + movie.getReleaseDate().toString("yyyy-MM-dd"));
        detailsLayout->addWidget(dateLabel);
        
        QLabel *durationLabel = new QLabel("Duration: " + QString::number(movie.getDuration()) + " minutes");
        detailsLayout->addWidget(durationLabel);
        
        QLabel *castLabel = new QLabel("Cast: " + movie.getCast());
        castLabel->setWordWrap(true);
        detailsLayout->addWidget(castLabel);
        
        detailsLayout->addStretch();
        
        // Descrizione
        QLabel *descriptionTitle = new QLabel("Synopsis:");
        QFont descFont = descriptionTitle->font();
        descFont.setBold(true);
        descriptionTitle->setFont(descFont);
        layout->addWidget(descriptionTitle);
        
        QLabel *descriptionLabel = new QLabel(movie.getDescription());
        descriptionLabel->setWordWrap(true);
        layout->addWidget(descriptionLabel);
    } 
    else if (renderMode == "summary") {
        // Implementazione sommaria
        // ...
    }
    else if (renderMode == "list") {
        // Implementazione lista
        // ...
    }
}

void MediaRendererVisitor::visit(Magazine &magazine) {
    // Implementazione simile a Book ma con attributi specifici di Magazine
    // ...
}

void MediaRendererVisitor::visit(EBook &ebook) {
    // Implementazione simile a Book ma con attributi specifici di EBook
    // ...
}

QWidget* MediaRendererVisitor::getWidget() const {
    return resultWidget;
}

void MediaRendererVisitor::setRenderMode(const QString &mode) {
    renderMode = mode;
}