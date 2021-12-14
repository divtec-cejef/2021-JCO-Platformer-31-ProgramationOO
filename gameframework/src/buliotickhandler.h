#ifndef BULIOTICKHANDLER_H
#define BULIOTICKHANDLER_H

#include<QPointF>
#include"spritetickhandler.h"

class BulioTickHandler : public SpriteTickHandler
{
public:
    BulioTickHandler(Sprite*pParentSprite);
    virtual void init();
    virtual void tick(long long elapsedTimeInMilliseconds);
};

#endif // BULIOTICKHANDLER_H
