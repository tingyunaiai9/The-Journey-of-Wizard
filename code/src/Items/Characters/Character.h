#ifndef QT_PROGRAMMING_2024_CHARACTER_H
#define QT_PROGRAMMING_2024_CHARACTER_H

#include <QGraphicsEllipseItem>
#include "../Weapon.h"
#include "../HeadEquipments/HeadEquipment.h"
#include "../Armors/Armor.h"
#include "../LegEquipments/LegEquipment.h"
#include "../MeleeWeapons/MeleeWeapon.h"
#include "IHero.h"

class Character : public Item, public IHero
{
private:
    bool m_leftDown{}, m_rightDown{};
    bool m_jumpDown{};
    qreal m_floorHeight{};
    bool m_onGround = false;

    bool m_pickDown{};
    bool m_lastPickDown{};
    bool m_picking{};

    bool m_attackDown{};
    bool m_lastAttackDown{};

protected:
    HeadEquipment *headEquipment{};
    LegEquipment *legEquipment{};
    Armor *armor{};

    MeleeWeapon *m_meleeWeapon{};
    Weapon *m_holdingWeapon{}; // the weapon character holding

    QPointF m_velocity{};
    QPointF m_acceleration{};

    int m_hp = 100;

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

    bool isOnGround() const;
    void setOnGround(bool isOnGround);

    [[nodiscard]] bool isPickDown() const;
    void setPickDown(bool pickDown);

    [[nodiscard]] bool isPicking() const;

    Armor* pickupArmor(Armor* newArmor);
    HeadEquipment* pickupHeadEquipment(HeadEquipment* newHeadEquipment);
    LegEquipment* pickupLegEquipment(LegEquipment* newLegEquipment);

    // attack
    void setAttackDown(bool attackDown);
    void setAttack();
    [[nodiscard]] bool isAttacking();
    virtual void h_startAttack() override; // from IHero
    virtual void h_stopAttack() override;

    void processInput();

    void beHit(int damage, QString element);

    virtual void h_reduceHp(int damage) override;
    int getHp() const;

public:
    virtual void key_press(QKeyEvent *event);
    virtual void key_release(QKeyEvent *event);
    void processFps(qint64 deltaTime);
};


#endif //QT_PROGRAMMING_2024_CHARACTER_H
