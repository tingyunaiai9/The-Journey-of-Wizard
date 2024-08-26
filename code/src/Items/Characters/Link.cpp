#include <memory>
#include "Link.h"
#include "../HeadEquipments/BlackHat.h"
#include "../HeadEquipments/FlamebreakerHat.h"
#include "../Armors/BlackWizardRobe.h"
#include "../LegEquipments/BlackShoes.h"

Link::Link(QGraphicsItem *parent) :
    Character(parent, ":/Items/Characters/character_body.png")
{
    headEquipment = new BlackHat(this);
    // headEquipment = new FlamebreakerHat(this);
    legEquipment = new BlackShoes(this);
    armor = new BlackWizardRobe(this);
    headEquipment->mountToParent();
    legEquipment->mountToParent();
    armor->mountToParent();
}
