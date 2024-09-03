#ifndef QT_PROGRAMMING_2024_CITEMFACTORY_H
#define QT_PROGRAMMING_2024_CITEMFACTORY_H

#include "Item.h"
#include "Mountable.h"
#include "Weapon.h"

#include <QString>

class CItemFactory
{
public:
    static Item* NewItem(const QString& category, const QString& type, const QString& element = "", const QString& material = "");
    static Item* NewItem(const QString& itemCode);
};

class CEquipmentFactory
{
public:
    static Mountable* NewEquipment(const QString& type, const QString& element);

    static Mountable* getNewRandomEquipment();
};

class CWeaponFactory
{
public:
    static Weapon* NewWeapon(const QString& type, const QString& element = "", const QString& material = "");

    static Weapon* getNewRandomWeapon();
    static Weapon* getNewRandomArrow();
};

#endif //QT_PROGRAMMING_2024_CITEMFACTORY_H
