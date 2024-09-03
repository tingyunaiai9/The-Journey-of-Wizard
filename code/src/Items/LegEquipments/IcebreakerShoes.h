#ifndef ICEBREAKERSHOES_H
#define ICEBREAKERSHOES_H

#include "LegEquipment.h"

class IcebreakerShoes : public LegEquipment {
public:
    explicit IcebreakerShoes(QGraphicsItem *parent = nullptr);

    [[nodiscard]] virtual QString getElement() const override { return "Ice"; }
};

#endif // ICEBREAKERSHOES_H
