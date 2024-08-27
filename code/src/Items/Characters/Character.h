//
// Created by gerw on 8/20/24.
//

#ifndef QT_PROGRAMMING_2024_CHARACTER_H
#define QT_PROGRAMMING_2024_CHARACTER_H

#include <QGraphicsEllipseItem>
#include "../HeadEquipments/HeadEquipment.h"
#include "../Armors/Armor.h"
#include "../LegEquipments/LegEquipment.h"

class Character : public Item
{
private:
    bool m_leftDown{}, m_rightDown{};
    bool m_jumpDown{};
    qreal m_floorHeight{};

    bool m_pickDown{};
    bool m_lastPickDown{};
    bool m_picking{};

public:
    explicit Character(QGraphicsItem *parent, const QString &pixmapPath);

    [[nodiscard]] bool isLeftDown() const;
    void setLeftDown(bool leftDown);

    [[nodiscard]] bool isRightDown() const;
    void setRightDown(bool rightDown);

    [[nodiscard]] bool isJumpDown() const;
    void setJumpDown(bool jumpDown);

    [[nodiscard]] const QPointF &getVelocity() const;
    void setVelocity(const QPointF &velocity);

    [[nodiscard]] const QPointF &getAcceleration() const;
    void setAcceleration(const QPointF &acceleration);

    void setFloorHeight(qreal floorHeight);
    bool isOnGround() const;

    [[nodiscard]] bool isPickDown() const;
    void setPickDown(bool pickDown);

    [[nodiscard]] bool isPicking() const;

    void processInput();

    Armor* pickupArmor(Armor* newArmor);
    HeadEquipment* pickupHeadEquipment(HeadEquipment* newHeadEquipment);
    LegEquipment* pickupLegEquipment(LegEquipment* newLegEquipment);

protected:
    HeadEquipment *headEquipment{};
    LegEquipment *legEquipment{};
    Armor *armor{};
    QPointF velocity{};
    QPointF m_acceleration{};
//    QGraphicsEllipseItem *ellipseItem; // for debugging
};


#endif //QT_PROGRAMMING_2024_CHARACTER_H
