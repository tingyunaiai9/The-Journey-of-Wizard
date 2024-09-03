#ifndef ELECTROBREAKERHAT_H
#define ELECTROBREAKERHAT_H

#include "HeadEquipment.h"

class ElectrobreakerHat: public HeadEquipment {
public:
    explicit ElectrobreakerHat(QGraphicsItem *parent = nullptr);

    [[nodiscard]] virtual QString getElement() const override { return "Electro"; }
};

#endif // ELECTROBREAKERHAT_H
