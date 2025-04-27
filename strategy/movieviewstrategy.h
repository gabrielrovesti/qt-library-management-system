#ifndef MOVIEVIEWSTRATEGY_H
#define MOVIEVIEWSTRATEGY_H

#include "mediaviewstrategy.h"
#include "../model/movie.h"

class MovieViewStrategy : public MediaViewStrategy {
public:
    QWidget* createDetailView(AbstractMedia *media) override;
    QWidget* createSummaryView(AbstractMedia *media) override;
    QWidget* createEditView(AbstractMedia *media) override;
};

#endif // MOVIEVIEWSTRATEGY_H