cmake_minimum_required(VERSION 3.28)
project(qt_programming_2024)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(qt_programming_2024 src/main.cpp
        src/MyGame.cpp
        src/MyGame.h

        assets/assets.qrc

        src/Items/Item.cpp
        src/Items/Item.h
        src/Items/CItemFactory.cpp
        src/Items/CItemFactory.h
        src/Items/Mountable.cpp
        src/Items/Mountable.h
        src/Items/Weapon.cpp
        src/Items/Weapon.h
        src/Items/IWood.h
        src/Items/IWood.cpp
        src/Items/IMetal.h
        src/Items/IMetal.cpp

        src/Items/MeleeWeapons/MeleeWeapon.cpp
        src/Items/MeleeWeapons/MeleeWeapon.h
        src/Items/MeleeWeapons/OneHandedSword.cpp
        src/Items/MeleeWeapons/OneHandedSword.h
        src/Items/MeleeWeapons/TwoHandedSword.cpp
        src/Items/MeleeWeapons/TwoHandedSword.h
        src/Items/MeleeWeapons/Spear.cpp
        src/Items/MeleeWeapons/Spear.h

        src/Items/RangedWeapons/RangedWeapon.cpp
        src/Items/RangedWeapons/RangedWeapon.h
        src/Items/RangedWeapons/Bow.cpp
        src/Items/RangedWeapons/Bow.h
        src/Items/RangedWeapons/Arrow.cpp
        src/Items/RangedWeapons/Arrow.h
        src/Items/RangedWeapons/PrimaryBow.cpp
        src/Items/RangedWeapons/PrimaryBow.h
        src/Items/RangedWeapons/ComboBow.cpp
        src/Items/RangedWeapons/ComboBow.h
        src/Items/RangedWeapons/AOEBow.cpp
        src/Items/RangedWeapons/AOEBow.h

        src/Items/Characters/Character.cpp
        src/Items/Characters/Character.h
        src/Items/Characters/IHero.cpp
        src/Items/Characters/IHero.h
        src/Items/Characters/Link.cpp
        src/Items/Characters/Link.h

        src/Items/Armors/Armor.cpp
        src/Items/Armors/Armor.h
        src/Items/HeadEquipments/HeadEquipment.cpp
        src/Items/HeadEquipments/HeadEquipment.h
        src/Items/LegEquipments/LegEquipment.cpp
        src/Items/LegEquipments/LegEquipment.h

        src/Items/Armors/BlackWizardRobe.cpp
        src/Items/Armors/BlackWizardRobe.h
        src/Items/Armors/FlamebreakerArmor.cpp
        src/Items/Armors/FlamebreakerArmor.h
        src/Items/Armors/IcebreakerArmor.cpp
        src/Items/Armors/IcebreakerArmor.h
        src/Items/Armors/ElectrobreakerArmor.cpp
        src/Items/Armors/ElectrobreakerArmor.h

        src/Items/HeadEquipments/BlackHat.cpp
        src/Items/HeadEquipments/BlackHat.h
        src/Items/HeadEquipments/FlamebreakerHat.cpp
        src/Items/HeadEquipments/FlamebreakerHat.h
        src/Items/HeadEquipments/IcebreakerHat.cpp
        src/Items/HeadEquipments/IcebreakerHat.h
        src/Items/HeadEquipments/ElectrobreakerHat.cpp
        src/Items/HeadEquipments/ElectrobreakerHat.h

        src/Items/LegEquipments/BlackShoes.cpp
        src/Items/LegEquipments/BlackShoes.h
        src/Items/LegEquipments/FlamebreakerShoes.cpp
        src/Items/LegEquipments/FlamebreakerShoes.h
        src/Items/LegEquipments/IcebreakerShoes.cpp
        src/Items/LegEquipments/IcebreakerShoes.h
        src/Items/LegEquipments/ElectrobreakerShoes.cpp
        src/Items/LegEquipments/ElectrobreakerShoes.h

        src/Items/Maps/Map.cpp
        src/Items/Maps/Map.h
        src/Items/Maps/Battlefield.cpp
        src/Items/Maps/Battlefield.h

        src/Items/Maps/Platform.h
        src/Items/Maps/Platform.cpp
        src/Items/Maps/WoodPlatform.cpp
        src/Items/Maps/WoodPlatform.h
        src/Items/Maps/RockPlatform.cpp
        src/Items/Maps/RockPlatform.h
        src/Items/Maps/MetalPlatform.cpp
        src/Items/Maps/MetalPlatform.h

        src/Scenes/Scene.cpp
        src/Scenes/Scene.h
        src/Scenes/BattleScene.cpp
        src/Scenes/BattleScene.h
        src/Scenes/StartScene.cpp
        src/Scenes/StartScene.h
        src/Scenes/GameOverScene.cpp
        src/Scenes/GameOverScene.h)
target_link_libraries(qt_programming_2024
        Qt::Core
        Qt::Gui
        Qt::Widgets
)
