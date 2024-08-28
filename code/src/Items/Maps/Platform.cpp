#include "platform.h"

Platform::Platform(QGraphicsItem *parent, const QString &pixmapPath) :
    Map(parent, pixmapPath)
{
    setScale(4);
}

qreal Platform::getFloorHeight()
{
    auto sceneRect = sceneBoundingRect();
    return sceneRect.bottom() - sceneRect.height() * 1 - 160;
}
