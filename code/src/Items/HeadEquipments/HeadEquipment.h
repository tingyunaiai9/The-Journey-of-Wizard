#ifndef QT_PROGRAMMING_2024_HEADEQUIPMENT_H
#define QT_PROGRAMMING_2024_HEADEQUIPMENT_H


#include "../Item.h"
#include "../Mountable.h"

class HeadEquipment: public Mountable
{
public:
    explicit HeadEquipment(QGraphicsItem *parent, const QString &pixmapPath);

    void mountToParent() override;

    void unmount() override;

    virtual void startHitting();
    virtual void stopHitting();

    virtual QPointF getCenterPos() override;
};


#endif //QT_PROGRAMMING_2024_HEADEQUIPMENT_H
