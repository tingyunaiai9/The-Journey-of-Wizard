#ifndef BLACKWIZARDROBE_H
#define BLACKWIZARDROBE_H

#include "Armor.h"

class BlackWizardRobe : public Armor {
public:
    explicit BlackWizardRobe(QGraphicsItem *parent = nullptr);

    [[nodiscard]] virtual QString getElement() const override { return "Normal"; }
};

#endif // BLACKWIZARDROBE_H
