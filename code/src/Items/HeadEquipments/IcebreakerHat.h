#ifndef ICEBREAKERHAT_H
#define ICEBREAKERHAT_H

#include "HeadEquipment.h"

class IcebreakerHat: public HeadEquipment {
public:
    explicit IcebreakerHat(QGraphicsItem *parent = nullptr);

    [[nodiscard]] virtual QString getElement() const override { return "Ice"; }
};

#endif // ICEBREAKERHAT_H
