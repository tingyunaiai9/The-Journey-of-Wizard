#include "Mountable.h"

Mountable::Mountable(QGraphicsItem *parent, const QString &pixmapPath) :
    Item(parent, pixmapPath)
{
}

void Mountable::unmount() {
    mounted = false;
}

bool Mountable::isMounted() const {
    return mounted;
}

void Mountable::mountToParent() {
    mounted = true;
}

const QPointF &Mountable::getVelocity() const {
    return m_velocity;
}

void Mountable::setVelocity(const QPointF &velocity) {
    m_velocity = velocity;
}

const QPointF &Mountable::getAcceleration() const {
    return m_acceleration;
}

void Mountable::setAcceleration(const QPointF &acceleration) {
    m_acceleration = acceleration;
}
