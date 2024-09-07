#ifndef METALPLATFORM_H
#define METALPLATFORM_H

#include "Platform.h"
#include "../IMetal.h"

class MetalPlatform: public Platform, public CMetal
{
public:
    explicit MetalPlatform(QGraphicsItem *parent= nullptr);
    ~MetalPlatform();

    virtual const QString getName() {return "MetalPlatform";}

    virtual bool isShock() override;
    virtual void beHit(QString element) override;
    virtual void beTrans(QString element, Item* srcItem) override;
    virtual void e_startShocking() override; // from IMetal
};

#endif // METALPLATFORM_H
