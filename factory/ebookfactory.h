#ifndef EBOOKFACTORY_H
#define EBOOKFACTORY_H

#include "mediafactory.h"
#include "../model/ebook.h"
#include "../strategy/ebookviewstrategy.h"

class EBookFactory : public MediaFactory {
private:
    EBookViewStrategy viewStrategy;
    
public:
    AbstractMedia* createMedia() override;
    QWidget* createEditDialog() override;
    QString getMediaType() const override;
};

#endif // EBOOKFACTORY_H