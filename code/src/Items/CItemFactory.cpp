#include "CItemFactory.h"

#include "./Armors/BlackWizardRobe.h"
#include "./Armors/FlamebreakerArmor.h"
#include "./Armors/IcebreakerArmor.h"
#include "./Armors/ElectrobreakerArmor.h"

#include "./HeadEquipments/BlackHat.h"
#include "./HeadEquipments/FlamebreakerHat.h"
#include "./HeadEquipments/IcebreakerHat.h"
#include "./HeadEquipments/ElectrobreakerHat.h"

#include "./LegEquipments/BlackShoes.h"
#include "./LegEquipments/FlamebreakerShoes.h"
#include "./LegEquipments/IcebreakerShoes.h"
#include "./LegEquipments/ElectrobreakerShoes.h"



Item* CItemFactory::NewItem(const QString& category, const QString& type, const QString& element)
{
    if (category == "Equipment")
    {
        return CEquipmentFactory::NewEquipment(type, element);
    }
    else if (category == "Weapon" )
    {
        return CWeaponFactory::NewWeapon(type, element);
    }
    else
    {
        return nullptr;
    }
}

Item* CEquipmentFactory::NewEquipment(const QString& type, const QString& element)
{
    if (type == "Armor")
    {
        if (element == "Black")
        {
            return new BlackWizardRobe();
        }
        else if (element == "Flame")
        {
            return new FlamebreakerArmor();
        }
        else if (element == "Ice")
        {
            return new IcebreakerArmor();
        }
        else if (element == "Electro")
        {
            return new ElectrobreakerArmor();
        }
    }
    else if (type == "HeadEquipment")
    {
        if (element == "Black")
        {
            return new BlackHat();
        }
        else if (element == "Flame")
        {
            return new FlamebreakerHat();
        }
        else if (element == "Ice")
        {
            return new IcebreakerHat();
        }
        else if (element == "Electro")
        {
            return new ElectrobreakerHat();
        }
    }
    else if (type == "LegEquipment")
    {
        if (element == "Black")
        {
            return new BlackShoes();
        }
        else if (element == "Flame")
        {
            return new FlamebreakerShoes();
        }
        else if (element == "Ice")
        {
            return new IcebreakerShoes();
        }
        else if (element == "Electro")
        {
            return new ElectrobreakerShoes();
        }
    }

    return nullptr;
}

// TODO
Item* CWeaponFactory::NewWeapon(const QString& type, const QString& element)
{
    return nullptr;
}
