#ifndef MEDIALISTWIDGET_H
#define MEDIALISTWIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QComboBox>

#include "../model/abstractmedia.h"

class MainWindow;

class MediaListWidget : public QWidget {
    Q_OBJECT
    
private:
    MainWindow *mainWindow;
    QTableWidget *tableWidget;
    QComboBox *viewModeCombo;
    QComboBox *filterTypeCombo;
    QPushButton *addButton;
    
    void setupUI();
    void setupConnections();
    void setupTableHeaders();
    
public:
    MediaListWidget(MainWindow *mainWindow);
    void updateMediaList();
    
private slots:
    void handleSelection();
    void handleCellDoubleClick(int row, int column);
    void changeViewMode(int index);
    void filterByType(int index);
    
signals:
    void mediaSelected(AbstractMedia *media);
    void editRequested(AbstractMedia *media);
    void removeRequested(AbstractMedia *media);
};

#endif // MEDIALISTWIDGET_H