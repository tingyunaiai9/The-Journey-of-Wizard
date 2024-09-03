#ifndef QT_PROGRAMMING_2024_FLAMEBREAKERARMOR_H
#define QT_PROGRAMMING_2024_FLAMEBREAKERARMOR_H

#include "Armor.h"

class FlamebreakerArmor : public Armor {
public:
    explicit FlamebreakerArmor(QGraphicsItem *parent = nullptr);

    [[nodiscard]] virtual QString getElement() const override { return "Flame"; }
};

#endif //QT_PROGRAMMING_2024_FLAMEBREAKERARMOR_H
