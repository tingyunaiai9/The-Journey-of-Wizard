#ifndef ICEBREAKERARMOR_H
#define ICEBREAKERARMOR_H

#include "Armor.h"

class IcebreakerArmor : public Armor {
public:
    explicit IcebreakerArmor(QGraphicsItem *parent = nullptr);

    [[nodiscard]] virtual QString getElement() const override { return "Ice"; }
};

#endif // ICEBREAKERARMOR_H
