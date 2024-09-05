#ifndef WOODPLATFORM_H
#define WOODPLATFORM_H

#include "Platform.h"
#include "../IWood.h"

class WoodPlatform: public Platform, public IWood
{
public:
    explicit WoodPlatform(QGraphicsItem *parent= nullptr);
    ~WoodPlatform();

    virtual void beHit(QString element) override;
    virtual void e_startBurning() override;
    virtual void e_stopBurning() override;

public slots:
    void onTimeOut() override;

private:
    QGraphicsPixmapItem* m_burningPicture = nullptr; // the picture be burning

    CWoodNormal* m_woodNormal = nullptr;
    CWoodBurned* m_woodBurned = nullptr;
    CWoodBurning* m_woodBurning = nullptr;
};


#endif // WOODPLATFORM_H
