//
// Created by gerw on 8/20/24.
//

#include <memory>
#include "Link.h"
#include "../HeadEquipments/BlackHat.h"
#include "../Armors/BlackWizardRobe.h"
#include "../LegEquipments/BlackShoes.h"

Link::Link(QGraphicsItem *parent) :
    Character(parent, ":/Items/Characters/character_body.png")
{
    headEquipment = new BlackHat(this);
    legEquipment = new BlackShoes(this);
    armor = new BlackWizardRobe(this);
    headEquipment->mountToParent();
    legEquipment->mountToParent();
    armor->mountToParent();
}
