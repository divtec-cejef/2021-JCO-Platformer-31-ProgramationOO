#ifndef BULIOTICKHANDLER_H
#define BULIOTICKHANDLER_H

#include <bulio.h>
#include "entitytickhandler.h"
#include <gamecore.h>
#include "gamescene.h"

class BulioTickHandler : public EntityTickHandler
{
public:
    BulioTickHandler(Entity* pParentSprite = nullptr,GameCore* newGameCore = nullptr);

    void tick(long long elapsedTimeInMilliseconds);

    void setGameCore(GameCore* newGameCore);
private:
    GameCore* m_pGameCore = nullptr;
};

#endif // BULIOTICKHANDLER_H
