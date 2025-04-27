#ifndef EBOOKVIEWSTRATEGY_H
#define EBOOKVIEWSTRATEGY_H

#include "mediaviewstrategy.h"
#include "../model/ebook.h"

class EBookViewStrategy : public MediaViewStrategy {
public:
    QWidget* createDetailView(AbstractMedia *media) override;
    QWidget* createSummaryView(AbstractMedia *media) override;
    QWidget* createEditView(AbstractMedia *media) override;
};

#endif // EBOOKVIEWSTRATEGY_H