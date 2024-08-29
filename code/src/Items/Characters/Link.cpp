#include <memory>
#include "Link.h"
#include "../HeadEquipments/BlackHat.h"
#include "../HeadEquipments/FlamebreakerHat.h"
#include "../HeadEquipments/IcebreakerHat.h"
#include "../HeadEquipments/ElectrobreakerHat.h"

#include "../Armors/BlackWizardRobe.h"
#include "../Armors/FlamebreakerArmor.h"
#include "../Armors/IcebreakerArmor.h"
#include "../Armors/ElectrobreakerArmor.h"

#include "../LegEquipments/BlackShoes.h"
#include "../LegEquipments/FlamebreakerShoes.h"
#include "../LegEquipments/IcebreakerShoes.h"
#include "../LegEquipments/ElectrobreakerShoes.h"

#include "../MeleeWeapons/OneHandedSword.h"

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

    // m_meleeWeapon = new WoodenOneHandedSword(this);
    m_meleeWeapon = new MetalOneHandedSword(this);

    headEquipment->mountToParent();
    legEquipment->mountToParent();
    armor->mountToParent();

    m_meleeWeapon->equipToParent();
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
{}
void CPlayer1::key_release(QKeyEvent *event)
{}

void CPlayer2::key_press(QKeyEvent *event)
{}
void CPlayer2::key_release(QKeyEvent *event)
{}
