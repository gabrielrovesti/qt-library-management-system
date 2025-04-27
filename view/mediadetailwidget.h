#ifndef MEDIADETAILWIDGET_H
#define MEDIADETAILWIDGET_H

#include <QWidget>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>

#include "../model/abstractmedia.h"
#include "../visitor/mediarenderervisitor.h"

class MediaDetailWidget : public QWidget {
    Q_OBJECT
    
private:
    QScrollArea *scrollArea;
    QWidget *contentWidget;
    QLabel *titleLabel;
    QPushButton *backButton;
    QPushButton *editButton;
    QPushButton *exportButton;
    
    AbstractMedia *currentMedia;
    MediaRendererVisitor rendererVisitor;
    
    void setupUI();
    void setupConnections();
    void updateContent();
    
public:
    MediaDetailWidget(QWidget *parent = nullptr);
    
    void setMedia(AbstractMedia *media);
    
private slots:
    void handleExport();
    
signals:
    void backRequested();
    void editRequested(AbstractMedia *media);
};

#endif // MEDIADETAILWIDGET_H