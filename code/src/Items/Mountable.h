#ifndef QT_PROGRAMMING_2024_MOUNTABLE_H
#define QT_PROGRAMMING_2024_MOUNTABLE_H

#include "Item.h"

#include <QPointF>

class Mountable : public Item
{
private:
    bool mounted{};
    QPointF m_velocity{};
    QPointF m_acceleration{};

public:
    explicit Mountable(QGraphicsItem *parent, const QString &pixmapPath);

    virtual void mountToParent();

    virtual void unmount();

    [[nodiscard]] bool isMounted() const;

    [[nodiscard]] const QPointF &getVelocity() const;
    void setVelocity(const QPointF &velocity);

    [[nodiscard]] const QPointF &getAcceleration() const;
    void setAcceleration(const QPointF &acceleration);
};


#endif //QT_PROGRAMMING_2024_MOUNTABLE_H
