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

void MediaRendererVisitor::visit(Movie &movie) {
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
        // Visualizzazione sommaria
        QHBoxLayout *summaryLayout = new QHBoxLayout();
        layout->addLayout(summaryLayout);
        
        QLabel *coverLabel = new QLabel();
        QPixmap coverPixmap(movie.getCoverPath());
        if (coverPixmap.isNull()) {
            coverPixmap = QPixmap(":/images/movie_placeholder.png");
        }
        coverLabel->setPixmap(coverPixmap.scaled(100, 150, Qt::KeepAspectRatio));
        summaryLayout->addWidget(coverLabel);
        
        QVBoxLayout *infoLayout = new QVBoxLayout();
        summaryLayout->addLayout(infoLayout);
        
        QLabel *titleLabel = new QLabel(movie.getTitle());
        QFont titleFont = titleLabel->font();
        titleFont.setBold(true);
        titleLabel->setFont(titleFont);
        infoLayout->addWidget(titleLabel);
        
        QLabel *directorLabel = new QLabel("by " + movie.getDirector());
        infoLayout->addWidget(directorLabel);
        
        QLabel *yearLabel = new QLabel(movie.getReleaseDate().toString("yyyy") + 
                                      " • " + QString::number(movie.getDuration()) + " min");
        infoLayout->addWidget(yearLabel);
        
        infoLayout->addStretch();
    }
    else if (renderMode == "list") {
        // Visualizzazione a lista
        QHBoxLayout *listLayout = new QHBoxLayout();
        layout->addLayout(listLayout);
        
        QLabel *iconLabel = new QLabel();
        QPixmap icon(":/images/movie_icon.png");
        if (icon.isNull()) {
            icon = QPixmap(16, 16);
            icon.fill(Qt::transparent);
        }
        iconLabel->setPixmap(icon);
        listLayout->addWidget(iconLabel);
        
        QLabel *titleLabel = new QLabel(movie.getTitle() + " - " + movie.getDirector() + 
                                       " (" + movie.getReleaseDate().toString("yyyy") + ")");
        listLayout->addWidget(titleLabel);
        
        listLayout->addStretch();
    }
}

void MediaRendererVisitor::visit(Magazine &magazine) {
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
        QPixmap coverPixmap(magazine.getCoverPath());
        if (coverPixmap.isNull()) {
            coverPixmap = QPixmap(":/images/magazine_placeholder.png");
        }
        coverLabel->setPixmap(coverPixmap.scaled(200, 300, Qt::KeepAspectRatio));
        headerLayout->addWidget(coverLabel);
        
        // Dettagli
        QVBoxLayout *detailsLayout = new QVBoxLayout();
        headerLayout->addLayout(detailsLayout);
        
        QLabel *titleLabel = new QLabel(magazine.getTitle());
        QFont titleFont = titleLabel->font();
        titleFont.setPointSize(16);
        titleFont.setBold(true);
        titleLabel->setFont(titleFont);
        detailsLayout->addWidget(titleLabel);
        
        QLabel *issueLabel = new QLabel("Issue: " + magazine.getIssue());
        detailsLayout->addWidget(issueLabel);
        
        QLabel *volumeLabel = new QLabel("Volume: " + QString::number(magazine.getVolume()) + 
                                        ", Issue: " + QString::number(magazine.getIssueNumber()));
        detailsLayout->addWidget(volumeLabel);
        
        QLabel *publisherLabel = new QLabel("Publisher: " + magazine.getPublisher());
        detailsLayout->addWidget(publisherLabel);
        
        QLabel *dateLabel = new QLabel("Published: " + magazine.getReleaseDate().toString("yyyy-MM-dd"));
        detailsLayout->addWidget(dateLabel);
        
        QLabel *topicLabel = new QLabel("Topic: " + magazine.getTopic());
        detailsLayout->addWidget(topicLabel);
        
        detailsLayout->addStretch();
        
        // Descrizione
        QLabel *descriptionTitle = new QLabel("Description:");
        QFont descFont = descriptionTitle->font();
        descFont.setBold(true);
        descriptionTitle->setFont(descFont);
        layout->addWidget(descriptionTitle);
        
        QLabel *descriptionLabel = new QLabel(magazine.getDescription());
        descriptionLabel->setWordWrap(true);
        layout->addWidget(descriptionLabel);
    } 
    else if (renderMode == "summary") {
        // Visualizzazione sommaria
        QHBoxLayout *summaryLayout = new QHBoxLayout();
        layout->addLayout(summaryLayout);
        
        QLabel *coverLabel = new QLabel();
        QPixmap coverPixmap(magazine.getCoverPath());
        if (coverPixmap.isNull()) {
            coverPixmap = QPixmap(":/images/magazine_placeholder.png");
        }
        coverLabel->setPixmap(coverPixmap.scaled(100, 150, Qt::KeepAspectRatio));
        summaryLayout->addWidget(coverLabel);
        
        QVBoxLayout *infoLayout = new QVBoxLayout();
        summaryLayout->addLayout(infoLayout);
        
        QLabel *titleLabel = new QLabel(magazine.getTitle());
        QFont titleFont = titleLabel->font();
        titleFont.setBold(true);
        titleLabel->setFont(titleFont);
        infoLayout->addWidget(titleLabel);
        
        QLabel *issueLabel = new QLabel(magazine.getIssue() + " • Vol. " + 
                                      QString::number(magazine.getVolume()));
        infoLayout->addWidget(issueLabel);
        
        QLabel *topicLabel = new QLabel(magazine.getTopic());
        infoLayout->addWidget(topicLabel);
        
        infoLayout->addStretch();
    }
    else if (renderMode == "list") {
        // Visualizzazione a lista
        QHBoxLayout *listLayout = new QHBoxLayout();
        layout->addLayout(listLayout);
        
        QLabel *iconLabel = new QLabel();
        QPixmap icon(":/images/magazine_icon.png");
        if (icon.isNull()) {
            icon = QPixmap(16, 16);
            icon.fill(Qt::transparent);
        }
        iconLabel->setPixmap(icon);
        listLayout->addWidget(iconLabel);
        
        QLabel *titleLabel = new QLabel(magazine.getTitle() + " - " + magazine.getIssue() + 
                                      " (" + magazine.getTopic() + ")");
        listLayout->addWidget(titleLabel);
        
        listLayout->addStretch();
    }
}

void MediaRendererVisitor::visit(EBook &ebook) {
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
        QPixmap coverPixmap(ebook.getCoverPath());
        if (coverPixmap.isNull()) {
            coverPixmap = QPixmap(":/images/ebook_placeholder.png");
        }
        coverLabel->setPixmap(coverPixmap.scaled(200, 300, Qt::KeepAspectRatio));
        headerLayout->addWidget(coverLabel);
        
        // Dettagli
        QVBoxLayout *detailsLayout = new QVBoxLayout();
        headerLayout->addLayout(detailsLayout);
        
        QLabel *titleLabel = new QLabel(ebook.getTitle());
        QFont titleFont = titleLabel->font();
        titleFont.setPointSize(16);
        titleFont.setBold(true);
        titleLabel->setFont(titleFont);
        detailsLayout->addWidget(titleLabel);
        
        QLabel *authorLabel = new QLabel("Author: " + ebook.getAuthor());
        detailsLayout->addWidget(authorLabel);
        
        QLabel *publisherLabel = new QLabel("Publisher: " + ebook.getPublisher());
        detailsLayout->addWidget(publisherLabel);
        
        QLabel *dateLabel = new QLabel("Published: " + ebook.getReleaseDate().toString("yyyy-MM-dd"));
        detailsLayout->addWidget(dateLabel);
        
        QLabel *isbnLabel = new QLabel("ISBN: " + ebook.getIsbn());
        detailsLayout->addWidget(isbnLabel);
        
        QLabel *pagesLabel = new QLabel("Pages: " + QString::number(ebook.getPageCount()));
        detailsLayout->addWidget(pagesLabel);
        
        QLabel *formatLabel = new QLabel("Format: " + ebook.getFormat());
        detailsLayout->addWidget(formatLabel);
        
        QLabel *sizeLabel = new QLabel("File Size: " + QString::number(ebook.getFileSizeMB()) + " MB");
        detailsLayout->addWidget(sizeLabel);
        
        detailsLayout->addStretch();
        
        // Descrizione
        QLabel *descriptionTitle = new QLabel("Description:");
        QFont descFont = descriptionTitle->font();
        descFont.setBold(true);
        descriptionTitle->setFont(descFont);
        layout->addWidget(descriptionTitle);
        
        QLabel *descriptionLabel = new QLabel(ebook.getDescription());
        descriptionLabel->setWordWrap(true);
        layout->addWidget(descriptionLabel);
    } 
    else if (renderMode == "summary") {
        // Visualizzazione sommaria
        QHBoxLayout *summaryLayout = new QHBoxLayout();
        layout->addLayout(summaryLayout);
        
        QLabel *coverLabel = new QLabel();
        QPixmap coverPixmap(ebook.getCoverPath());
        if (coverPixmap.isNull()) {
            coverPixmap = QPixmap(":/images/ebook_placeholder.png");
        }
        coverLabel->setPixmap(coverPixmap.scaled(100, 150, Qt::KeepAspectRatio));
        summaryLayout->addWidget(coverLabel);
        
        QVBoxLayout *infoLayout = new QVBoxLayout();
        summaryLayout->addLayout(infoLayout);
        
        QLabel *titleLabel = new QLabel(ebook.getTitle());
        QFont titleFont = titleLabel->font();
        titleFont.setBold(true);
        titleLabel->setFont(titleFont);
        infoLayout->addWidget(titleLabel);
        
        QLabel *authorLabel = new QLabel("by " + ebook.getAuthor());
        infoLayout->addWidget(authorLabel);
        
        QLabel *formatLabel = new QLabel(ebook.getFormat() + " • " + 
                                       QString::number(ebook.getFileSizeMB()) + " MB");
        infoLayout->addWidget(formatLabel);
        
        infoLayout->addStretch();
    }
    else if (renderMode == "list") {
        // Visualizzazione a lista
        QHBoxLayout *listLayout = new QHBoxLayout();
        layout->addLayout(listLayout);
        
        QLabel *iconLabel = new QLabel();
        QPixmap icon(":/images/ebook_icon.png");
        if (icon.isNull()) {
            icon = QPixmap(16, 16);
            icon.fill(Qt::transparent);
        }
        iconLabel->setPixmap(icon);
        listLayout->addWidget(iconLabel);
        
        QLabel *titleLabel = new QLabel(ebook.getTitle() + " - " + ebook.getAuthor() + 
                                      " (" + ebook.getFormat() + ")");
        listLayout->addWidget(titleLabel);
        
        listLayout->addStretch();
    }
}

QWidget* MediaRendererVisitor::getWidget() const {
    return resultWidget;
}

void MediaRendererVisitor::setRenderMode(const QString &mode) {
    renderMode = mode;
}