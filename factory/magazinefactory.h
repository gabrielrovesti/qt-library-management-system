#ifndef MAGAZINEFACTORY_H
#define MAGAZINEFACTORY_H

#include "mediafactory.h"
#include "../model/magazine.h"
#include "../strategy/magazineviewstrategy.h"

class MagazineFactory : public MediaFactory {
private:
    MagazineViewStrategy viewStrategy;
    
public:
    AbstractMedia* createMedia() override;
    QWidget* createEditDialog() override;
    QString getMediaType() const override;
};

#endif // MAGAZINEFACTORY_H