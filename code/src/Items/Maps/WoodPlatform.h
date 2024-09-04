#ifndef WOODPLATFORM_H
#define WOODPLATFORM_H

#include "Platform.h"

class WoodPlatform: public Platform
{
public:
    explicit WoodPlatform(QGraphicsItem *parent= nullptr);

    void startBurning();
    void stopBurning();

private:
    QGraphicsPixmapItem* m_burningPicture = nullptr; // the picture be burning
};


#endif // WOODPLATFORM_H
