#ifndef ELECTROBREAKERSHOES_H
#define ELECTROBREAKERSHOES_H

#include "LegEquipment.h"

class ElectrobreakerShoes : public LegEquipment {
public:
    explicit ElectrobreakerShoes(QGraphicsItem *parent = nullptr);

    [[nodiscard]] virtual QString getElement() const override { return "Electro"; }
};

#endif // ELECTROBREAKERSHOES_H
