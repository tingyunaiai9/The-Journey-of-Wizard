#ifndef METALPLATFORM_H
#define METALPLATFORM_H

#include "Platform.h"

class MetalPlatform: public Platform
{
public:
    explicit MetalPlatform(QGraphicsItem *parent= nullptr);
};

#endif // METALPLATFORM_H
