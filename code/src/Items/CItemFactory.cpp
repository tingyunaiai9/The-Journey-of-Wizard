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

#include "./MeleeWeapons/OneHandedSword.h"
#include "./MeleeWeapons/TwoHandedSword.h"
#include "./MeleeWeapons/Spear.h"
#include "./RangedWeapons/PrimaryBow.h"
#include "./RangedWeapons/ComboBow.h"
#include "./RangedWeapons/AOEBow.h"
#include "./RangedWeapons/Arrow.h"



Item* CItemFactory::NewItem(const QString& category, const QString& type, const QString& element, const QString& material)
{
    if (category == "Equipment")
    {
        return CEquipmentFactory::NewEquipment(type, element);
    }
    else if (category == "Weapon" )
    {
        return CWeaponFactory::NewWeapon(type, element, material);
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
    else if (item_code == "I11")
    {
        return new IceWoodenOneHandedSword();
    }
    else if (item_code == "I12")
    {
        return new IceWoodenTwoHandedSword();
    }
    else if (item_code == "EA")
    {
        return new ElectrobreakerArmor();
    }
    else if (item_code == "FA")
    {
        return new FlamebreakerArmor();
    }
    else if (item_code == "IA")
    {
        return new IcebreakerArmor();
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
Weapon* CWeaponFactory::NewWeapon(const QString& type, const QString& element, const QString& material)
{
    if (type == "OneHandedSword")
    {
        if (element == "Flame")
        {
            if (material == "Wooden")
            {
                return new FlameWoodenOneHandedSword();
            }
            else if (material == "Metal")
            {
                return new FlameMetalOneHandedSword();
            }
        }
        else if (element == "Ice")
        {
            if (material == "Wooden")
            {
                return new IceWoodenOneHandedSword();
            }
            else if (material == "Metal")
            {
                return new IceMetalOneHandedSword();
            }
        }
        else if (element == "Electro")
        {
            if (material == "Wooden")
            {
                return new ElectroWoodenOneHandedSword();
            }
            else if (material == "Metal")
            {
                return new ElectroMetalOneHandedSword();
            }
        }
        else if (element == "Normal")
        {
            if (material == "Wooden")
            {
                return new NormalWoodenOneHandedSword();
            }
            else if (material == "Metal")
            {
                return new NormalMetalOneHandedSword();
            }
        }
    }
    else if (type == "TwoHandedSword")
    {
        if (element == "Flame")
        {
            if (material == "Wooden")
            {
                return new FlameWoodenTwoHandedSword();
            }
            else if (material == "Metal")
            {
                return new FlameMetalTwoHandedSword();
            }
        }
        else if (element == "Ice")
        {
            if (material == "Wooden")
            {
                return new IceWoodenTwoHandedSword();
            }
            else if (material == "Metal")
            {
                return new IceMetalTwoHandedSword();
            }
        }
        else if (element == "Electro")
        {
            if (material == "Wooden")
            {
                return new ElectroWoodenTwoHandedSword();
            }
            else if (material == "Metal")
            {
                return new ElectroMetalTwoHandedSword();
            }
        }
        else if (element == "Normal")
        {
            if (material == "Wooden")
            {
                return new NormalWoodenTwoHandedSword();
            }
            else if (material == "Metal")
            {
                return new NormalMetalTwoHandedSword();
            }
        }
    }
    else if (type == "Spear")
    {
        if (element == "Flame")
        {
            if (material == "Wooden")
            {
                return new FlameWoodenSpear();
            }
            else if (material == "Metal")
            {
                return new FlameMetalSpear();
            }
        }
        else if (element == "Ice")
        {
            if (material == "Wooden")
            {
                return new IceWoodenSpear();
            }
            else if (material == "Metal")
            {
                return new IceMetalSpear();
            }
        }
        else if (element == "Electro")
        {
            if (material == "Wooden")
            {
                return new ElectroWoodenSpear();
            }
            else if (material == "Metal")
            {
                return new ElectroMetalSpear();
            }
        }
        else if (element == "Normal")
        {
            if (material == "Wooden")
            {
                return new NormalWoodenSpear();
            }
            else if (material == "Metal")
            {
                return new NormalMetalSpear();
            }
        }
    }
    else if (type == "PrimaryBow")
    {
        if (material == "Wooden")
        {
            return new WoodenPrimaryBow();
        }
        else if (material == "Metal")
        {
            return new MetalPrimaryBow();
        }
    }
    else if (type == "ComboBow")
    {
        if (material == "Wooden")
        {
            return new WoodenComboBow();
        }
        else if (material == "Metal")
        {
            return new MetalComboBow();
        }
    }
    else if (type == "AOEBow")
    {
        if (material == "Wooden")
        {
            return new WoodenAOEBow();
        }
        else if (material == "Metal")
        {
            return new MetalAOEBow();
        }
    }
    else if (type == "Arrow")
    {
        if (element == "Flame")
        {
            return new FlameArrow();
        }
        else if (element == "Ice")
        {
            return new IceArrow();
        }
        else if (element == "Electro")
        {
            return new ElectroArrow();
        }
        else if (element == "Normal")
        {
            return new NormalArrow();
        }
    }
    return nullptr;
}
