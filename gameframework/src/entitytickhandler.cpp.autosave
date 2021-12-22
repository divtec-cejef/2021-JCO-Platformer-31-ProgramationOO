/**
  \file
  \brief    Définition de la classe EntityTickHandler.
  \author   LKU
  \date     decembre 2021
*/

#include <entitytickhandler.h>

class Entity;

//! Construit un gestionnaire de tick pour le Entity donné.
//! \param pParentSprite  Sprite qui sera géré par ce gestionnaire.
EntityTickHandler::EntityTickHandler(Entity* pParentEntity) {
    setParentEntity(pParentEntity);
}

//! Destructeur
EntityTickHandler::~EntityTickHandler() {

}

//! Indique quel entity sera géré par ce gestionnaire.
void EntityTickHandler::setParentEntity(Entity* pParentEntity) {
    m_pParentEntity = pParentEntity;
}
