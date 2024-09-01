#include "Battlefield.h"

Battlefield::Battlefield(QGraphicsItem *parent) :
    Map(parent, ":/Items/Maps/Battlefield/forest.png")
{
}

qreal Battlefield::getFloorHeight()
{
    auto sceneRect = sceneBoundingRect();
    qreal floorHeight = (sceneRect.top() + sceneRect.bottom()) * 0.666;
    return floorHeight;
}

// QRectF Battlefield::getAreaRect()
// {
//     QRectF itemRect = sceneBoundingRect();
//     qreal y = getFloorHeight();
//     itemRect.setY(y);

//     return itemRect;
// }
