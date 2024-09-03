#ifndef FLAMEBREAKERSHOES_H
#define FLAMEBREAKERSHOES_H

#include "LegEquipment.h"

class FlamebreakerShoes : public LegEquipment {
public:
    explicit FlamebreakerShoes(QGraphicsItem *parent = nullptr);

    [[nodiscard]] virtual QString getElement() const override { return "Flame"; }
};

#endif // FLAMEBREAKERSHOES_H
