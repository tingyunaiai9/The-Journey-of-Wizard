#ifndef QT_PROGRAMMING_2024_CITEMFACTORY_H
#define QT_PROGRAMMING_2024_CITEMFACTORY_H

#include "Item.h"
#include "Mountable.h"
#include "Weapon.h"

#include <QString>

class CItemFactory
{
public:
    static Item* NewItem(const QString& category, const QString& type, const QString& element);
};

class CEquipmentFactory
{
public:
    static Mountable* NewEquipment(const QString& type, const QString& element);
};

class CWeaponFactory
{
public:
    static Weapon* NewWeapon(const QString& type, const QString& element);
};

#endif //QT_PROGRAMMING_2024_CITEMFACTORY_H
