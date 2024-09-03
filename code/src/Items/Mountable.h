#ifndef QT_PROGRAMMING_2024_MOUNTABLE_H
#define QT_PROGRAMMING_2024_MOUNTABLE_H

#include "Item.h"

#include <QPointF>

class Mountable : public Item
{
private:
    bool mounted{};

public:
    explicit Mountable(QGraphicsItem *parent, const QString &pixmapPath);

    virtual void mountToParent();

    virtual void unmount();

    [[nodiscard]] bool isMounted() const;

    [[nodiscard]] virtual QString getElement() const {return "";} // element
};


#endif //QT_PROGRAMMING_2024_MOUNTABLE_H
