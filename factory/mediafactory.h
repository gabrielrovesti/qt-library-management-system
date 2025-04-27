#ifndef MEDIAFACTORY_H
#define MEDIAFACTORY_H

#include "../model/abstractmedia.h"
#include <QWidget>

class MediaFactory {
public:
    virtual ~MediaFactory() = default;
    virtual AbstractMedia* createMedia() = 0;
    virtual QWidget* createEditDialog() = 0;
    virtual QString getMediaType() const = 0;
};

#endif // MEDIAFACTORY_H