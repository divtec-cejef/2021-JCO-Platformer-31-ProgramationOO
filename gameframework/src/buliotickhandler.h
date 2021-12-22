#ifndef BULIOTICKHANDLER_H
#define BULIOTICKHANDLER_H

#include <QPointF>
#include <bulio.h>
#include "entitytickhandler.h"


class BulioTickHandler : public EntityTickHandler
{
public:
    BulioTickHandler(Entity* pParentSprite = nullptr);

    void tick(long long elapsedTimeInMilliseconds);
};

#endif // BULIOTICKHANDLER_H
