#ifndef ELECTROBREAKERARMOR_H
#define ELECTROBREAKERARMOR_H

#include "Armor.h"

class ElectrobreakerArmor : public Armor {
public:
    explicit ElectrobreakerArmor(QGraphicsItem *parent = nullptr);

    [[nodiscard]] virtual QString getElement() const override { return "Electro"; }
};

#endif // ELECTROBREAKERARMOR_H
