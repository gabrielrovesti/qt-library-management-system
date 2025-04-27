#include "mainwindow.h"
#include "medialistwidget.h"
#include "mediadetailwidget.h"
#include "mediaeditwidget.h"
#include "mediasearchdialog.h"

#include "../factory/bookfactory.h"
#include "../factory/moviefactory.h"
#include "../factory/magazinefactory.h"
#include "../factory/ebookfactory.h"

#include <QMenuBar>
#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), currentFilePath("") {
    
    // Create media factories
    mediaFactories.append(new BookFactory());
    mediaFactories.append(new MovieFactory());
    mediaFactories.append(new MagazineFactory());
    mediaFactories.append(new EBookFactory());
    
    setupUI();
    setupMenus();
    setupConnections();
    updateWindowTitle();
}

MainWindow::~MainWindow() {
    // Clean up media items
    for (AbstractMedia *media : mediaList) {
        delete media;
    }
    mediaList.clear();
    
    // Clean up factories
    for (MediaFactory *factory : mediaFactories) {
        delete factory;
    }
    mediaFactories.clear();
}

void MainWindow::setupUI() {
    // Create central stack widget
    centralStack = new QStackedWidget(this);
    setCentralWidget(centralStack);
    
    // Create media list widget
    listWidget = new MediaListWidget(this);
    centralStack->addWidget(listWidget);
    
    // Create detail widget
    detailWidget = new MediaDetailWidget(this);
    centralStack->addWidget(detailWidget);
    
    // Set initial widget
    centralStack->setCurrentWidget(listWidget);
    
    // Create status bar
    statusBar()->showMessage("Ready");
    
    // Set window properties
    resize(800, 600);
}

void MainWindow::setupMenus() {
    // File menu
    QMenu *fileMenu = menuBar()->addMenu("&File");
    
    QAction *newAct = fileMenu->addAction("&New", this, &MainWindow::newLibrary);
    newAct->setShortcut(QKeySequence::New);
    
    QAction *openAct = fileMenu->addAction("&Open...", this, &MainWindow::openLibrary);
    openAct->setShortcut(QKeySequence::Open);
    
    QAction *saveAct = fileMenu->addAction("&Save", this, &MainWindow::saveLibrary);
    saveAct->setShortcut(QKeySequence::Save);
    
    QAction *saveAsAct = fileMenu->addAction("Save &As...", this, &MainWindow::saveLibraryAs);
    saveAsAct->setShortcut(QKeySequence::SaveAs);
    
    fileMenu->addSeparator();
    
    QAction *exitAct = fileMenu->addAction("E&xit", this, &QWidget::close);
    exitAct->setShortcut(QKeySequence::Quit);
    
    // Edit menu
    QMenu *editMenu = menuBar()->addMenu("&Edit");
    
    QAction *addAct = editMenu->addAction("&Add Media...", this, &MainWindow::addMedia);
    addAct->setShortcut(QKeySequence("Ctrl+N"));
    
    QAction *searchAct = editMenu->addAction("&Search...", this, &MainWindow::search);
    searchAct->setShortcut(QKeySequence::Find);
    
    // Help menu
    QMenu *helpMenu = menuBar()->addMenu("&Help");
    
    QAction *aboutAct = helpMenu->addAction("&About", this, &MainWindow::about);
    
    // Toolbar
    toolbar = addToolBar("Main Toolbar");
    toolbar->addAction(newAct);
    toolbar->addAction(openAct);
    toolbar->addAction(saveAct);
    toolbar->addSeparator();
    toolbar->addAction(addAct);
    toolbar->addAction(searchAct);
}

void MainWindow::setupConnections() {
    // Connect signals from list widget
    connect(listWidget, &MediaListWidget::mediaSelected, 
            this, &MainWindow::showMediaDetails);
    connect(listWidget, &MediaListWidget::editRequested, 
            this, &MainWindow::editMedia);
    connect(listWidget, &MediaListWidget::removeRequested, 
            this, &MainWindow::removeMedia);
    
    // Connect signals from detail widget
    connect(detailWidget, &MediaDetailWidget::backRequested, 
            this, &MainWindow::showMediaList);
    connect(detailWidget, &MediaDetailWidget::editRequested, 
            this, &MainWindow::editMedia);
}

void MainWindow::updateWindowTitle() {
    QString title = "Library Manager";
    if (!currentFilePath.isEmpty()) {
        QFileInfo fileInfo(currentFilePath);
        title += " - " + fileInfo.fileName();
    }
    setWindowTitle(title);
}

QVector<AbstractMedia*>& MainWindow::getMediaList() {
    return mediaList;
}

void MainWindow::newLibrary() {
    // Check for unsaved changes
    if (!mediaList.isEmpty()) {
        QMessageBox::StandardButton reply = QMessageBox::question(this, 
            "New Library", "Are you sure you want to create a new library? Any unsaved changes will be lost.",
            QMessageBox::Yes | QMessageBox::No);
            
        if (reply == QMessageBox::No) {
            return;
        }
    }
    
    // Clear existing media
    for (AbstractMedia *media : mediaList) {
        delete media;
    }
    mediaList.clear();
    
    // Update UI
    currentFilePath = "";
    updateWindowTitle();
    listWidget->updateMediaList();
    showMediaList();
    
    statusBar()->showMessage("New library created", 3000);
}

void MainWindow::openLibrary() {
    // Check for unsaved changes
    if (!mediaList.isEmpty()) {
        QMessageBox::StandardButton reply = QMessageBox::question(this, 
            "Open Library", "Are you sure you want to open a library? Any unsaved changes will be lost.",
            QMessageBox::Yes | QMessageBox::No);
            
        if (reply == QMessageBox::No) {
            return;
        }
    }
    
    // Show file dialog
    QString filePath = QFileDialog::getOpenFileName(this, "Open Library", "", "JSON Files (*.json)");
    if (filePath.isEmpty()) {
        return;
    }
    
    // Clear existing media
    for (AbstractMedia *media : mediaList) {
        delete media;
    }
    mediaList.clear();
    
    // Load from file
    mediaList = persistenceManager.loadLibrary(filePath);
    
    // Update UI
    currentFilePath = filePath;
    updateWindowTitle();
    listWidget->updateMediaList();
    showMediaList();
    
    statusBar()->showMessage("Library loaded from " + filePath, 3000);
}

void MainWindow::saveLibrary() {
    if (currentFilePath.isEmpty()) {
        saveLibraryAs();
        return;
    }
    
    if (persistenceManager.saveLibrary(currentFilePath, mediaList)) {
        statusBar()->showMessage("Library saved to " + currentFilePath, 3000);
    } else {
        QMessageBox::warning(this, "Save Error", "Could not save library to " + currentFilePath);
    }
}

void MainWindow::saveLibraryAs() {
    QString filePath = QFileDialog::getSaveFileName(this, "Save Library As", "", "JSON Files (*.json)");
    if (filePath.isEmpty()) {
        return;
    }
    
    if (persistenceManager.saveLibrary(filePath, mediaList)) {
        currentFilePath = filePath;
        updateWindowTitle();
        statusBar()->showMessage("Library saved to " + filePath, 3000);
    } else {
        QMessageBox::warning(this, "Save Error", "Could not save library to " + filePath);
    }
}

void MainWindow::addMedia() {
    // Show dialog to select media type
    QStringList types;
    for (MediaFactory *factory : mediaFactories) {
        types << factory->getMediaType();
    }
    
    bool ok;
    QString type = QInputDialog::getItem(this, "Add Media", 
                                        "Select media type:", types, 0, false, &ok);
    if (!ok || type.isEmpty()) {
        return;
    }
    
    // Find the factory for the selected type
    MediaFactory *factory = nullptr;
    for (MediaFactory *f : mediaFactories) {
        if (f->getMediaType() == type) {
            factory = f;
            break;
        }
    }
    
    if (!factory) {
        return;
    }
    
    // Create the edit dialog
    AbstractMedia *newMedia = factory->createMedia();
    
    // Show edit dialog
    QDialog dialog(this);
    dialog.setWindowTitle("Add " + type);
    QVBoxLayout *layout = new QVBoxLayout(&dialog);
    
    QWidget *editWidget = factory->createEditDialog();
    layout->addWidget(editWidget);
    
    QPushButton *saveButton = new QPushButton("Save");
    saveButton->setObjectName("saveButton");
    QPushButton *cancelButton = new QPushButton("Cancel");
    cancelButton->setObjectName("cancelButton");
    
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(cancelButton);
    layout->addLayout(buttonLayout);
    
    connect(saveButton, &QPushButton::clicked, &dialog, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked, &dialog, &QDialog::reject);
    
    if (dialog.exec() == QDialog::Accepted) {
        // Generate new ID
        int maxId = 0;
        for (const AbstractMedia *media : mediaList) {
            if (media->getId() > maxId) {
                maxId = media->getId();
            }
        }
        
        // Update ID and add to library
        newMedia->setId(maxId + 1);
        mediaList.append(newMedia);
        listWidget->updateMediaList();
        
        statusBar()->showMessage(type + " added successfully", 3000);
    } else {
        delete newMedia;
    }
}

void MainWindow::editMedia(AbstractMedia *media) {
    if (!media) return;
    
    // Find the factory for this media type
    MediaFactory *factory = nullptr;
    for (MediaFactory *f : mediaFactories) {
        if (f->getMediaType() == media->getMediaType()) {
            factory = f;
            break;
        }
    }
    
    if (!factory) {
        return;
    }
    
    // Show edit dialog
    QDialog dialog(this);
    dialog.setWindowTitle("Edit " + media->getMediaType());
    QVBoxLayout *layout = new QVBoxLayout(&dialog);
    
    QWidget *editWidget = factory->createEditDialog();
    layout->addWidget(editWidget);
    
    QPushButton *saveButton = new QPushButton("Save");
    saveButton->setObjectName("saveButton");
    QPushButton *cancelButton = new QPushButton("Cancel");
    cancelButton->setObjectName("cancelButton");
    
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(cancelButton);
    layout->addLayout(buttonLayout);
    
    connect(saveButton, &QPushButton::clicked, &dialog, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked, &dialog, &QDialog::reject);
    
    if (dialog.exec() == QDialog::Accepted) {
        // Media has been updated
        listWidget->updateMediaList();
        if (centralStack->currentWidget() == detailWidget) {
            showMediaDetails(media);
        }
        
        statusBar()->showMessage(media->getMediaType() + " updated successfully", 3000);
    }
}

void MainWindow::removeMedia(AbstractMedia *media) {
    if (!media) return;
    
    QMessageBox::StandardButton reply = QMessageBox::question(this, 
        "Remove Media", "Are you sure you want to remove '" + media->getTitle() + "'?",
        QMessageBox::Yes | QMessageBox::No);
        
    if (reply == QMessageBox::No) {
        return;
    }
    
    // Remove from list
    int index = mediaList.indexOf(media);
    if (index != -1) {
        mediaList.removeAt(index);
        delete media;
        
        listWidget->updateMediaList();
        showMediaList();
        
        statusBar()->showMessage("Media removed successfully", 3000);
    }
}

void MainWindow::showMediaDetails(AbstractMedia *media) {
    if (!media) return;
    
    detailWidget->setMedia(media);
    centralStack->setCurrentWidget(detailWidget);
}

void MainWindow::showMediaList() {
    centralStack->setCurrentWidget(listWidget);
}

void MainWindow::search() {
    MediaSearchDialog dialog(mediaList, this);
    dialog.exec();
}

void MainWindow::about() {
    QMessageBox::about(this, "About Library Manager",
                      "Library Manager 1.0\n\n"
                      "A library management application for organizing various types of media.\n\n"
                      "Created for the Object-Oriented Programming course at University of Padova.");
}