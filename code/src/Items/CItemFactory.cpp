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

#include "./MeleeWeapons/Spear.h"


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

Item* CItemFactory::NewItem(const QString& itemCode)
{
    // S - Spear
    // 1 - Wooden
    // I - Ice,

    QString item_code = itemCode.toUpper();
    if (item_code == "I1S")
    {
        return new IceWoodenSpear();
    }
    else
    {
        return nullptr;
    }
    return nullptr;
}

Mountable* CEquipmentFactory::NewEquipment(const QString& type, const QString& element)
{
    if (type == "Armor")
    {
        if (element == "Flame")
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
        else if (element == "Normal")
        {
            return new BlackWizardRobe();
        }
    }
    else if (type == "HeadEquipment")
    {
        if (element == "Flame")
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
        else if (element == "Normal")
        {
            return new BlackHat();
        }
    }
    else if (type == "LegEquipment")
    {
        if (element == "Flame")
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
        else if (element == "Normal")
        {
            return new BlackShoes();
        }
    }

    return nullptr;
}

// TODO
Weapon* CWeaponFactory::NewWeapon(const QString& type, const QString& element)
{
    return nullptr;
}
