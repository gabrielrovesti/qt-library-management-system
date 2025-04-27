#ifndef BOOKVIEWSTRATEGY_H
#define BOOKVIEWSTRATEGY_H

#include "mediaviewstrategy.h"
#include "../model/book.h"

class BookViewStrategy : public MediaViewStrategy {
public:
    QWidget* createDetailView(AbstractMedia *media) override;
    QWidget* createSummaryView(AbstractMedia *media) override;
    QWidget* createEditView(AbstractMedia *media) override;
};

#endif // BOOKVIEWSTRATEGY_H