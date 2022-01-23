#ifndef CAISSEAMOVTICKHANDLER_H
#define CAISSEAMOVTICKHANDLER_H

#include "caisseamovible.h"
#include "entitytickhandler.h"
#include <gamecore.h>
#include "gamescene.h"

//!
//! \brief The CaisseAmovTickHandler class
//! Cette classe permet de géré des entités et de leur donnée le comportement d'une caisse amovible.
//! Cette classe à pour bute de géré une enité provenant de la classe \ref CaisseAmovible. Mais elle peut
//! très bien appliqué ce comportement à d'autre entité.
class CaisseAmovTickHandler : public EntityTickHandler
{
public:    
    CaisseAmovTickHandler(Entity* pParentSprite = nullptr,GameCore* newGameCore = nullptr);

    bool m_isPlayer = false;
    bool m_canMove = false;

    void tick(long long elapsedTimeInMilliseconds);

    void currentCollision();
    void nextCollision();

    void setGameCore(GameCore* newGameCore);
private:
    GameCore* m_pGameCore = nullptr;
};

#endif // CAISSEAMOVTICKHANDLER_H
