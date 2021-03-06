/**
  \file
  \brief    Déclaration de la classe EntityTickHandler.
  \author   LKU
  \date     decembre 2021
*/
#ifndef ENTITYTICKHANDLER_H
#define ENTITYTICKHANDLER_H
#include <gamecore.h>
class Entity;


//! \brief Classe abstraite qui représente un gestionnaire de tick pour une entité.
//!
//! Cette classe a pour but d'être spécialisée afin de donner à un sprite un comportement
//! à effectuer lors de chaque tick émis par la cadence.
//!
//! Lorsqu'un gestionnaire est affecté à une entité (Entity::setTickHandler), la
//! fonction init() du gestionnaire est appelée une unique fois, puis, lorsque
//! la cadence démarre, la fonction tick() du gestionnaire est automatiquement appelée.
//!
//! Depuis le gestionnaire, il est possible d'accéder au Sprite en question avec
//! l'attribut m_pParentEntity.
//!

class EntityTickHandler
{
public:
    EntityTickHandler(Entity* pParentEntity = nullptr);
    virtual ~EntityTickHandler();

public:
    virtual void setParentEntity(Entity* pParentEntity);

    virtual void init() {}
    virtual void tick(long long elapsedTimeInMilliseconds) = 0;

    virtual void currentCollision();
    virtual void nextCollision();
    void setGameCore(GameCore* newGameCore);

protected:
    Entity* m_pParentEntity;
    GameCore* m_pGameCore = nullptr;
};

#endif // ENTITYTICKHANDLER_H
