#ifndef METALPLATFORM_H
#define METALPLATFORM_H

#include "Platform.h"
#include "../IMetal.h"

class MetalPlatform: public Platform, public IMetal
{
public:
    explicit MetalPlatform(QGraphicsItem *parent= nullptr);
    ~MetalPlatform();

    virtual void beHit(QString element) override;
    virtual void e_startShocking() override;
    virtual void e_stopShocking() override;

public slots:
    void onTimeOut() override;

private:
    QGraphicsPixmapItem* m_shockingPicture = nullptr; // the picture be shocking

    CMetalNormal* m_metalNormal = nullptr;
    CMetalShocking* m_metalShocking = nullptr;
};

#endif // METALPLATFORM_H
