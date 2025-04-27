#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QToolBar>
#include <QAction>
#include <QVector>
#include <QMenu>
#include <QStatusBar>
#include <QLabel>

#include "../model/abstractmedia.h"
#include "../persistence/jsonpersistencemanager.h"

class MediaListWidget;
class MediaDetailWidget;

class MainWindow : public QMainWindow {
    Q_OBJECT
    
private:
    QStackedWidget *centralStack;
    QToolBar *toolbar;
    QVector<AbstractMedia*> mediaList;
    QVector<MediaFactory*> mediaFactories;
    JsonPersistenceManager persistenceManager;
    QString currentFilePath;
    
    MediaListWidget *listWidget;
    MediaDetailWidget *detailWidget;
    
    void setupUI();
    void setupMenus();
    void setupConnections();
    void updateWindowTitle();
    
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    
    QVector<AbstractMedia*>& getMediaList();
    
public slots:
    void newLibrary();
    void openLibrary();
    void saveLibrary();
    void saveLibraryAs();
    void addMedia();
    void editMedia(AbstractMedia *media);
    void removeMedia(AbstractMedia *media);
    void showMediaDetails(AbstractMedia *media);
    void showMediaList();
    void search();
    void about();
};

#endif // MAINWINDOW_H