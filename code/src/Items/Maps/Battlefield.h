#ifndef QT_PROGRAMMING_2024_BATTLEFIELD_H
#define QT_PROGRAMMING_2024_BATTLEFIELD_H


#include "Map.h"

class Battlefield: public Map
{
public:
    explicit Battlefield(QGraphicsItem *parent= nullptr);

    qreal getFloorHeight() override;

    virtual const QString getName() override {return "Battlefield";}
    // virtual QRectF getAreaRect() override;
};


#endif //QT_PROGRAMMING_2024_BATTLEFIELD_H
