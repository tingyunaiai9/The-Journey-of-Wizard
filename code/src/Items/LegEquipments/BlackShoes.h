#ifndef BLACKSHOES_H
#define BLACKSHOES_H

#include "LegEquipment.h"

class BlackShoes : public LegEquipment {
public:
    explicit BlackShoes(QGraphicsItem *parent = nullptr);

    [[nodiscard]] virtual QString getElement() const override { return "Normal"; }
};

#endif // BLACKSHOES_H
