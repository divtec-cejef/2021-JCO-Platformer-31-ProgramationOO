#ifndef BULIOTICKHANDLER_H
#define BULIOTICKHANDLER_H

#include <QPointF>
#include <bulio.h>
#include "spritetickhandler.h"


class BulioTickHandler : public SpriteTickHandler
{
public:
    BulioTickHandler(Entity* pParentSprite = nullptr);

    void tick(long long elapsedTimeInMilliseconds);
};

#endif // BULIOTICKHANDLER_H
