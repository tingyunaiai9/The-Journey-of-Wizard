#ifndef WOODPLATFORM_H
#define WOODPLATFORM_H

#include "Platform.h"
#include "../IWood.h"

class WoodPlatform: public Platform, public CWood
{
public:
    explicit WoodPlatform(QGraphicsItem *parent= nullptr);
    ~WoodPlatform();

    virtual const QString getName() {return "WoodPlatform";}
    virtual void beHit(QString element) override;
    virtual void e_startBurning() override;
    virtual void e_stopBurning() override;
};


#endif // WOODPLATFORM_H
