#ifndef MOVIEFACTORY_H
#define MOVIEFACTORY_H

#include "mediafactory.h"
#include "../model/movie.h"
#include "../strategy/movieviewstrategy.h"

class MovieFactory : public MediaFactory {
private:
    MovieViewStrategy viewStrategy;
    
public:
    AbstractMedia* createMedia() override;
    QWidget* createEditDialog() override;
    QString getMediaType() const override;
};

#endif // MOVIEFACTORY_H