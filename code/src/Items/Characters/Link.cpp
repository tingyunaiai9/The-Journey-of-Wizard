#include "Link.h"

#include "../HeadEquipments/BlackHat.h"
#include "../Armors/BlackWizardRobe.h"
#include "../LegEquipments/BlackShoes.h"

#include <QKeyEvent>

Link::Link(QGraphicsItem *parent, const QString &pixmapPath) :
    Character(parent, pixmapPath)
{
    headEquipment = new BlackHat(this);
    legEquipment = new BlackShoes(this);
    armor = new BlackWizardRobe(this);

    headEquipment->mountToParent();
    legEquipment->mountToParent();
    armor->mountToParent();
}

CPlayer1::CPlayer1(QGraphicsItem *parent) :
    Link(parent, ":/Items/Characters/character_body.png")
{
}

CPlayer2::CPlayer2(QGraphicsItem *parent) :
    Link(parent, ":/Items/Characters/character_body.png")
{
    turnLeft();
}

void CPlayer1::h_keyPress(QKeyEvent *event)
{
    switch (event->key())
    {
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
        case Qt::Key_I: // switch weapon
            setSwitchDown(true);
            break;
        default:
            break;
    }
}

void CPlayer1::h_keyRelease(QKeyEvent *event)
{
    switch (event->key())
    {
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
        case Qt::Key_I: // release switch weapon
            setSwitchDown(false);
            break;
        default:
            break;
    }
}

void CPlayer2::h_keyPress(QKeyEvent *event)
{
    switch (event->key())
    {
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
        case Qt::Key_Slash: // shoot
            setShootDown(true);
            break;
        case Qt::Key_Shift: // switch weapon
            setSwitchDown(true);
            break;
        default:
            break;
    }
}

void CPlayer2::h_keyRelease(QKeyEvent *event)
{
    switch (event->key())
    {
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
        case Qt::Key_Slash: // release shoot
            setShootDown(false);
            break;
        case Qt::Key_Shift: // release switch weapon
            setSwitchDown(false);
            break;
        default:
            break;
    }
}
