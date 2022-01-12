#ifndef CAISSEAMOVTICKHANDLER_H
#define CAISSEAMOVTICKHANDLER_H

#include "caisseamovible.h"
#include "entitytickhandler.h"
#include <gamecore.h>
#include "gamescene.h"

class CaisseAmovTickHandler : public EntityTickHandler
{
public:    
    CaisseAmovTickHandler(Entity* pParentSprite = nullptr,GameCore* newGameCore = nullptr);

    bool m_isPlayer = false;

    void tick(long long elapsedTimeInMilliseconds);

    void currentCollision();
    void nextCollision();

    void setGameCore(GameCore* newGameCore);
private:
    GameCore* m_pGameCore = nullptr;
};

#endif // CAISSEAMOVTICKHANDLER_H
