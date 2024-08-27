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

Link::Link(QGraphicsItem *parent) :
    Character(parent, ":/Items/Characters/character_body.png")
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

    headEquipment->mountToParent();
    legEquipment->mountToParent();
    armor->mountToParent();
}
