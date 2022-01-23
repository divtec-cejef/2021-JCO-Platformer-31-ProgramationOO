/**
  \file
  \brief    Définition de la classe EntityTickHandler.
  \author   LKU
  \date     decembre 2021
*/

#include <entitytickhandler.h>

class Entity;

//! Construit un gestionnaire de tick pour le Entity donné.
//! \param pParentEntity Entity qui sera géré par ce gestionnaire.
EntityTickHandler::EntityTickHandler(Entity* pParentEntity) {
    setParentEntity(pParentEntity);
}

//! Destructeur
EntityTickHandler::~EntityTickHandler() {

}

//! Définit la procédure à executé pour les collisions qui touche l'entité.
void EntityTickHandler::currentCollision(){}

//! Définit la procédure à executé pour les collisions qui vont touché l'entité.
void EntityTickHandler::nextCollision(){}

//! Indique quel entity sera géré par ce gestionnaire.
void EntityTickHandler::setParentEntity(Entity* pParentEntity) {
    m_pParentEntity = pParentEntity;
}

void EntityTickHandler::setGameCore(GameCore *newGameCore){
    m_pGameCore = newGameCore;
}

