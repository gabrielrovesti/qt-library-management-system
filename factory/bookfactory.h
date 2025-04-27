#ifndef BOOKFACTORY_H
#define BOOKFACTORY_H

#include "mediafactory.h"
#include "../model/book.h"
#include "../strategy/bookviewstrategy.h"

class BookFactory : public MediaFactory {
private:
    BookViewStrategy viewStrategy;

public:
    AbstractMedia* createMedia() override;
    QWidget* createEditDialog() override;
    QString getMediaType() const override;
};

#endif // BOOKFACTORY_H