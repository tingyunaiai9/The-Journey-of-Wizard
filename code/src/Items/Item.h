#ifndef QT_PROGRAMMING_2024_ITEM_H
#define QT_PROGRAMMING_2024_ITEM_H

#include "../Scenes/Scene.h"

#include <QGraphicsItem>
#include <QPainter>
#include <QString>

class Item : public QGraphicsItem
{
public:
    static const QPointF GRAVITY;

protected:
    QGraphicsPixmapItem *pixmapItem{};

public:
    explicit Item(QGraphicsItem *parent, const QString &pixmapPath);
    ~Item();

    [[nodiscard]] QRectF boundingRect() const override {
        if (pixmapItem != nullptr) {
            return this->pixmapItem->boundingRect();
        }
        // Empty rectangle makes the empty item not selectable and not collider
        return {};
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override {
        // Draw nothing as it is an empty item
        // Its pixmapItem is automatically handled by children's paint()
    }

    QGraphicsPixmapItem* getPixmapItem() const { return pixmapItem;}
    int type() const override { return QGraphicsItem::UserType + 1;}

private:
    QGraphicsRectItem* m_sceneRect;
    QGraphicsEllipseItem* m_posPoint;
    Scene* m_scene;

    Item* m_groundMap = nullptr;

protected:
    QPointF m_velocity;
    QPointF m_acceleration;

public:
    virtual const QString getName() {return "base item";}

    virtual QRectF getAreaRect();
    virtual void showAreaRect(Scene* scene, bool bDebug);

    virtual QPointF getCenterPos() {return pos();}

    virtual void beHit(QString element) {};

    virtual bool isBurn() {return false;}
    virtual bool isShock() {return false;}

public:
    [[nodiscard]] const QPointF &getVelocity() const;
    void setVelocity(const QPointF &velocity);
    [[nodiscard]] const QPointF &getAcceleration() const;
    void setAcceleration(const QPointF &acceleration);
    virtual void move(qint64 deltaTime, QRectF maxRect = QRectF(0, 0, 1280, 480));

    // direction
    [[nodiscard]] bool isFacingRight() const;
};

#endif //QT_PROGRAMMING_2024_ITEM_H
