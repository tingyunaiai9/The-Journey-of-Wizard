#ifndef QT_PROGRAMMING_2024_ARMOR_H
#define QT_PROGRAMMING_2024_ARMOR_H

#include "../Mountable.h"

class Armor : public Mountable
{
public:
    explicit Armor(QGraphicsItem *parent, const QString &pixmapPath);

    void mountToParent() override;

    void unmount() override;
};


#endif //QT_PROGRAMMING_2024_ARMOR_H
