#include "bookviewstrategy.h"
#include "../model/book.h"
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPixmap>
#include <QLineEdit>
#include <QDateEdit>
#include <QTextEdit>
#include <QSpinBox>
#include <QFormLayout>
#include <QPushButton>
#include <QFileDialog>

QWidget* BookViewStrategy::createDetailView(AbstractMedia *media) {
    Book *book = dynamic_cast<Book*>(media);
    if (!book) return nullptr;
    
    QWidget *widget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(widget);
    
    // Header with cover and basic info
    QHBoxLayout *headerLayout = new QHBoxLayout();
    layout->addLayout(headerLayout);
    
    // Cover image
    QLabel *coverLabel = new QLabel();
    QPixmap coverPixmap(book->getCoverPath());
    if (coverPixmap.isNull()) {
        coverPixmap = QPixmap(":/images/book_placeholder.png");
    }
    coverLabel->setPixmap(coverPixmap.scaled(200, 300, Qt::KeepAspectRatio));
    headerLayout->addWidget(coverLabel);
    
    // Basic information
    QVBoxLayout *infoLayout = new QVBoxLayout();
    headerLayout->addLayout(infoLayout);
    
    QLabel *titleLabel = new QLabel(book->getTitle());
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(16);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    infoLayout->addWidget(titleLabel);
    
    QLabel *authorLabel = new QLabel("Author: " + book->getAuthor());
    infoLayout->addWidget(authorLabel);
    
    QLabel *publisherLabel = new QLabel("Publisher: " + book->getPublisher());
    infoLayout->addWidget(publisherLabel);
    
    QLabel *dateLabel = new QLabel("Published: " + book->getReleaseDate().toString("yyyy-MM-dd"));
    infoLayout->addWidget(dateLabel);
    
    QLabel *isbnLabel = new QLabel("ISBN: " + book->getIsbn());
    infoLayout->addWidget(isbnLabel);
    
    QLabel *pagesLabel = new QLabel("Pages: " + QString::number(book->getPageCount()));
    infoLayout->addWidget(pagesLabel);
    
    QLabel *genreLabel = new QLabel("Genre: " + book->getGenre());
    infoLayout->addWidget(genreLabel);
    
    infoLayout->addStretch();
    
    // Description
    QLabel *descTitleLabel = new QLabel("Description:");
    QFont descFont = descTitleLabel->font();
    descFont.setBold(true);
    descTitleLabel->setFont(descFont);
    layout->addWidget(descTitleLabel);
    
    QLabel *descLabel = new QLabel(book->getDescription());
    descLabel->setWordWrap(true);
    layout->addWidget(descLabel);
    
    return widget;
}

QWidget* BookViewStrategy::createSummaryView(AbstractMedia *media) {
    Book *book = dynamic_cast<Book*>(media);
    if (!book) return nullptr;
    
    QWidget *widget = new QWidget();
    QHBoxLayout *layout = new QHBoxLayout(widget);
    
    // Small cover
    QLabel *coverLabel = new QLabel();
    QPixmap coverPixmap(book->getCoverPath());
    if (coverPixmap.isNull()) {
        coverPixmap = QPixmap(":/images/book_placeholder.png");
    }
    coverLabel->setPixmap(coverPixmap.scaled(100, 150, Qt::KeepAspectRatio));
    layout->addWidget(coverLabel);
    
    // Basic info
    QVBoxLayout *infoLayout = new QVBoxLayout();
    layout->addLayout(infoLayout);
    
    QLabel *titleLabel = new QLabel(book->getTitle());
    QFont titleFont = titleLabel->font();
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    infoLayout->addWidget(titleLabel);
    
    QLabel *authorLabel = new QLabel("By " + book->getAuthor());
    infoLayout->addWidget(authorLabel);
    
    QLabel *yearLabel = new QLabel(book->getReleaseDate().toString("yyyy"));
    infoLayout->addWidget(yearLabel);
    
    infoLayout->addStretch();
    
    return widget;
}

QWidget* BookViewStrategy::createEditView(AbstractMedia *media) {
    Book *book = dynamic_cast<Book*>(media);
    bool isNew = (book == nullptr);
    if (isNew) {
        book = new Book(0, "", QDate::currentDate(), "", "", "", "", "", 0, "");
    }
    
    QWidget *widget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(widget);
    
    // Form layout for common fields
    QFormLayout *formLayout = new QFormLayout();
    layout->addLayout(formLayout);
    
    QLineEdit *titleEdit = new QLineEdit(book->getTitle());
    formLayout->addRow("Title:", titleEdit);
    
    QLineEdit *authorEdit = new QLineEdit(book->getAuthor());
    formLayout->addRow("Author:", authorEdit);
    
    QLineEdit *isbnEdit = new QLineEdit(book->getIsbn());
    formLayout->addRow("ISBN:", isbnEdit);
    
    QLineEdit *publisherEdit = new QLineEdit(book->getPublisher());
    formLayout->addRow("Publisher:", publisherEdit);
    
    QDateEdit *releaseDateEdit = new QDateEdit(book->getReleaseDate());
    releaseDateEdit->setCalendarPopup(true);
    formLayout->addRow("Release Date:", releaseDateEdit);
    
    QSpinBox *pageCountEdit = new QSpinBox();
    pageCountEdit->setRange(1, 10000);
    pageCountEdit->setValue(book->getPageCount());
    formLayout->addRow("Page Count:", pageCountEdit);
    
    QLineEdit *genreEdit = new QLineEdit(book->getGenre());
    formLayout->addRow("Genre:", genreEdit);
    
    // Cover selection
    QHBoxLayout *coverLayout = new QHBoxLayout();
    formLayout->addRow("Cover:", coverLayout);
    
    QLineEdit *coverPathEdit = new QLineEdit(book->getCoverPath());
    coverLayout->addWidget(coverPathEdit);
    
    QPushButton *browseButton = new QPushButton("Browse...");
    coverLayout->addWidget(browseButton);
    
    // Description field
    QLabel *descriptionLabel = new QLabel("Description:");
    layout->addWidget(descriptionLabel);
    
    QTextEdit *descriptionEdit = new QTextEdit(book->getDescription());
    layout->addWidget(descriptionEdit);
    
    // Button row
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    layout->addLayout(buttonLayout);
    
    buttonLayout->addStretch();
    
    QPushButton *saveButton = new QPushButton("Save");
    buttonLayout->addWidget(saveButton);
    
    QPushButton *cancelButton = new QPushButton("Cancel");
    buttonLayout->addWidget(cancelButton);
    
    // Connect the browse button to file dialog
    QObject::connect(browseButton, &QPushButton::clicked, [coverPathEdit]() {
        QString filePath = QFileDialog::getOpenFileName(nullptr, "Select Cover Image", "", 
                                                     "Images (*.png *.jpg *.jpeg *.bmp)");
        if (!filePath.isEmpty()) {
            coverPathEdit->setText(filePath);
        }
    });
    
    // Connect save and cancel buttons
    QObject::connect(saveButton, &QPushButton::clicked, [=]() {
        book->setTitle(titleEdit->text());
        book->setAuthor(authorEdit->text());
        book->setIsbn(isbnEdit->text());
        book->setPublisher(publisherEdit->text());
        book->setReleaseDate(releaseDateEdit->date());
        book->setPageCount(pageCountEdit->value());
        book->setGenre(genreEdit->text());
        book->setCoverPath(coverPathEdit->text());
        book->setDescription(descriptionEdit->toPlainText());
        
        // Signal to parent that editing is complete
        widget->parentWidget()->findChild<QPushButton*>("saveButton")->click();
    });
    
    QObject::connect(cancelButton, &QPushButton::clicked, [=]() {
        if (isNew) {
            delete book;
        }
        widget->parentWidget()->findChild<QPushButton*>("cancelButton")->click();
    });
    
    return widget;
}