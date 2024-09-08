#ifndef WOODPLATFORM_H
#define WOODPLATFORM_H

#include "Platform.h"
#include "../IWood.h"

class WoodPlatform: public Platform, public CWood
{
public:
    explicit WoodPlatform(QGraphicsItem *parent= nullptr);
    ~WoodPlatform();

    virtual const QString getName() override {return "WoodPlatform";}

    virtual bool isBurn() override;
    virtual bool isOut() override;
    virtual void beHit(QString element) override;
    virtual void beTrans(QString element, Item* srcItem) override;
    virtual void e_startBurning() override;
};


#endif // WOODPLATFORM_H
