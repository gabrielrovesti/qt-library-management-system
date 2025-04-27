#ifndef MEDIAVIEWSTRATEGY_H
#define MEDIAVIEWSTRATEGY_H

#include <QWidget>
#include "../model/abstractmedia.h"

class MediaViewStrategy {
public:
    virtual ~MediaViewStrategy() = default;
    virtual QWidget* createDetailView(AbstractMedia *media) = 0;
    virtual QWidget* createSummaryView(AbstractMedia *media) = 0;
    virtual QWidget* createEditView(AbstractMedia *media) = 0;
};

#endif // MEDIAVIEWSTRATEGY_H