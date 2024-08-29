#ifndef QT_PROGRAMMING_2024_MOUNTABLE_H
#define QT_PROGRAMMING_2024_MOUNTABLE_H

#include "Item.h"

class Mountable : public Item
{
public:
    Mountable(QGraphicsItem *parent, const QString &pixmapPath);

    virtual void mountToParent();

    virtual void unmount();

    [[nodiscard]] bool isMounted() const;

private:
    bool mounted{};
};


#endif //QT_PROGRAMMING_2024_MOUNTABLE_H
