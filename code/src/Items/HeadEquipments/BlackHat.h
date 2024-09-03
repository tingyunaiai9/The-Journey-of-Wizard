#ifndef BLACKHAT_H
#define BLACKHAT_H

#include "HeadEquipment.h"

class BlackHat: public HeadEquipment {
public:
    explicit BlackHat(QGraphicsItem *parent = nullptr);

    [[nodiscard]] virtual QString getElement() const override { return "Normal"; }
};

#endif // BLACKHAT_H
