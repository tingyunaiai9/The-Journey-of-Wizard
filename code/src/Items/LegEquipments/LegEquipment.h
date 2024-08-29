#ifndef QT_PROGRAMMING_2024_LEGEQUIPMENT_H
#define QT_PROGRAMMING_2024_LEGEQUIPMENT_H


#include "../Item.h"
#include "../Mountable.h"

class LegEquipment: public Mountable
{
public:
    explicit LegEquipment(QGraphicsItem *parent, const QString &pixmapPath);

    void mountToParent() override;

    void unmount() override;
};


#endif //QT_PROGRAMMING_2024_LEGEQUIPMENT_H
