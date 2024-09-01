#include "Item.h"
#include "./Maps/Map.h"

#include <QDebug>

const QPointF Item::GRAVITY = (QPointF(0, 0.004));

Item::Item(QGraphicsItem *parent, const QString &pixmapPath) :
    QGraphicsItem(parent)
{
    if (pixmapPath != "") {
        pixmapItem = new QGraphicsPixmapItem(QPixmap(pixmapPath), this);
    }

    m_sceneRect = nullptr;
    m_scene = nullptr;

    m_velocity = QPointF(0,0);
    m_acceleration = QPointF(0,0);
}

Item::~Item()
{
    if ((m_scene) && (m_sceneRect))
    {
        m_scene->removeItem(m_sceneRect);
        delete m_sceneRect;
        m_sceneRect = nullptr;
    }
}

QRectF Item::getAreaRect()
{
    return sceneBoundingRect();
}

void Item::showAreaRect(Scene* scene, bool bDebug)
{
    m_scene = scene;
    if ((bDebug) && (m_sceneRect == nullptr))
    {
        QRectF itemRect = getAreaRect();
        m_sceneRect = new QGraphicsRectItem(itemRect);
        m_sceneRect->setPen(QPen(Qt::blue));
        m_sceneRect->setBrush(Qt::NoBrush);
        m_scene->addItem(m_sceneRect);

        qDebug() << getName() << itemRect;
    }

    if ((!bDebug) && (m_sceneRect))
    {
        m_scene->removeItem(m_sceneRect);
        delete m_sceneRect;
        m_sceneRect = nullptr;
    }
}

bool Item::isOnGround(QVector<Item*> &itemVec, bool bReload)
{
    if ((m_groundMap) && (!bReload))
    {
        return true;
    }

    QRectF itemRect = getAreaRect();

    for (Item *i : itemVec)
    {
        Map * map = dynamic_cast<Map*>(i);
    }

    return false;
}


const QPointF &Item::getVelocity() const {
    return m_velocity;
}

void Item::setVelocity(const QPointF &velocity) {
    m_velocity = velocity;
}

const QPointF &Item::getAcceleration() const {
    return m_acceleration;
}

void Item::setAcceleration(const QPointF &acceleration) {
    m_acceleration = acceleration;
}

void Item::move(qint64 deltaTime, QRectF maxRect)
{
    setPos(pos().x() + getVelocity().x() * (double) deltaTime,
                        fmin(480, pos().y() + getVelocity().y() * (double) deltaTime));
    setVelocity(getVelocity() + getAcceleration() * (double) deltaTime);
}
