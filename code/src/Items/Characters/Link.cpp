#include "Link.h"
#include "../HeadEquipments/BlackHat.h"

#include "../Armors/BlackWizardRobe.h"

#include "../LegEquipments/BlackShoes.h"

#include "../MeleeWeapons/OneHandedSword.h"
#include "../MeleeWeapons/TwoHandedSword.h"
#include "../MeleeWeapons/Spear.h"
#include "../RangedWeapons/PrimaryBow.h"

#include <QKeyEvent>

Link::Link(QGraphicsItem *parent, const QString &pixmapPath) :
    Character(parent, pixmapPath)
{
    headEquipment = new BlackHat(this);
    // headEquipment = new FlamebreakerHat(this);
    // headEquipment = new IcebreakerHat(this);
    // headEquipment = new ElectrobreakerHat(this);

    legEquipment = new BlackShoes(this);
    // legEquipment = new FlamebreakerShoes(this);
    // legEquipment = new IcebreakerShoes(this);
    // legEquipment = new ElectrobreakerShoes(this);

    armor = new BlackWizardRobe(this);
    // armor = new FlamebreakerArmor(this);
    // armor = new IcebreakerArmor(this);
    // armor = new ElectrobreakerArmor(this);

    // m_meleeWeapon = new ElectroMetalSpear(this);
    // m_holdingWeapon = m_meleeWeapon;
    m_bow = new WoodenPrimaryBow(this);
    m_holdingWeapon = m_bow;

    headEquipment->mountToParent();
    legEquipment->mountToParent();
    armor->mountToParent();

    m_holdingWeapon->equipToParent();
}

CPlayer1::CPlayer1(QGraphicsItem *parent) :
    Link(parent, ":/Items/Characters/character_body.png")
{
}

CPlayer2::CPlayer2(QGraphicsItem *parent) :
    Link(parent, ":/Items/Characters/character_body.png")
{
    setTransform(QTransform().scale(-1, 1));
}

void CPlayer1::key_press(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_A:
            setLeftDown(true);
            break;
        case Qt::Key_D:
            setRightDown(true);
            break;
        case Qt::Key_W:
            setJumpDown(true);
            break;
        case Qt::Key_J:
            setPickDown(true);
            break;
        case Qt::Key_K: // attack
            setAttackDown(true);
            break;
        case Qt::Key_L: // shoot
            setShootDown(true);
            break;
        default:
            break;
    }
}

void CPlayer1::key_release(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_A:
            setLeftDown(false);
            break;
        case Qt::Key_D:
            setRightDown(false);
            break;
        case Qt::Key_W:
            setJumpDown(false);
            break;
        case Qt::Key_J:
            setPickDown(false);
            break;
        case Qt::Key_K: // release attack
            setAttackDown(false);
            break;
        case Qt::Key_L: // release shoot
            setShootDown(false);
            break;
        default:
            break;
    }
}

void CPlayer2::key_press(QKeyEvent *event)
{    switch (event->key()) {
        case Qt::Key_Left:
            setLeftDown(true);
            break;
        case Qt::Key_Right:
            setRightDown(true);
            break;
        case Qt::Key_Up:
            setJumpDown(true);
            break;
        case Qt::Key_Comma:
            setPickDown(true);
            break;
        case Qt::Key_Period:
            setAttackDown(true);
            break;
        default:
            break;
    }
}

void CPlayer2::key_release(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_Left:
            setLeftDown(false);
            break;
        case Qt::Key_Right:
            setRightDown(false);
            break;
        case Qt::Key_Up:
            setJumpDown(false);
            break;
        case Qt::Key_Comma:
            setPickDown(false);
            break;
        case Qt::Key_Period: // release attack
            setAttackDown(false);
            break;
        default:
            break;
    }
}
