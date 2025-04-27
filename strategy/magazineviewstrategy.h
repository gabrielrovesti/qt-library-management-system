#ifndef MAGAZINEVIEWSTRATEGY_H
#define MAGAZINEVIEWSTRATEGY_H

#include "mediaviewstrategy.h"
#include "../model/magazine.h"

class MagazineViewStrategy : public MediaViewStrategy {
public:
    QWidget* createDetailView(AbstractMedia *media) override;
    QWidget* createSummaryView(AbstractMedia *media) override;
    QWidget* createEditView(AbstractMedia *media) override;
};

#endif // MAGAZINEVIEWSTRATEGY_H