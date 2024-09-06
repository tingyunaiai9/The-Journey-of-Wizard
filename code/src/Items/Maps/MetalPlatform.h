#ifndef METALPLATFORM_H
#define METALPLATFORM_H

#include "Platform.h"
#include "../IMetal.h"

class MetalPlatform: public Platform, public CMetal
{
public:
    explicit MetalPlatform(QGraphicsItem *parent= nullptr);
    ~MetalPlatform();

    virtual void beHit(QString element) override; // from map
    virtual void e_startShocking() override; // from IMetal
};

#endif // METALPLATFORM_H
