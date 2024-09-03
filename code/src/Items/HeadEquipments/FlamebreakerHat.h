#ifndef FLAMEBREAKERHAT_H
#define FLAMEBREAKERHAT_H

#include "HeadEquipment.h"

class FlamebreakerHat: public HeadEquipment {
public:
    explicit FlamebreakerHat(QGraphicsItem *parent = nullptr);

    [[nodiscard]] virtual QString getElement() const override { return "Flame"; }
};

#endif // FLAMEBREAKERHAT_H
