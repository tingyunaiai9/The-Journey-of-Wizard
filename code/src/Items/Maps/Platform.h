#ifndef PLATFORM_H
#define PLATFORM_H

#include "Map.h"

class Platform: public Map
{
public:
    explicit Platform(QGraphicsItem *parent= nullptr, const QString &pixmapPath = "");

    qreal getFloorHeight() override;
};

#endif // PLATFORM_H
