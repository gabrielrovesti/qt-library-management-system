#ifndef MEDIARENDERERVISITOR_H
#define MEDIARENDERERVISITOR_H

#include "mediavisitor.h"
#include <QWidget>
#include <QString>

class MediaRendererVisitor : public MediaVisitor {
private:
    QWidget *resultWidget;
    QString renderMode; // "detail", "summary", "list"
    
public:
    MediaRendererVisitor(const QString &mode = "detail");
    ~MediaRendererVisitor();
    
    void visit(Book &book) override;
    void visit(Movie &movie) override;
    void visit(Magazine &magazine) override;
    void visit(EBook &ebook) override;
    
    QWidget* getWidget() const;
    void setRenderMode(const QString &mode);
};

#endif // MEDIARENDERERVISITOR_H