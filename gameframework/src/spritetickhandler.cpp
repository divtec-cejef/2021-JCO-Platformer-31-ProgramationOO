/**
  \file
  \brief    Définition de la classe SpriteTickHandler.
  \author   JCO
  \date     septembre 2018
*/
#include "spritetickhandler.h"
#include <entity.h>

class Sprite;

//! Construit un gestionnaire de tick pour le Sprite donné.
//! \param pParentSprite  Sprite qui sera géré par ce gestionnaire.
SpriteTickHandler::SpriteTickHandler(Sprite* pParentSprite) {
    setParentSprite(pParentSprite);
}

//! Construit un gestionnaire de tick pour le Entity donné.
//! \param pParentSprite  Sprite qui sera géré par ce gestionnaire.
SpriteTickHandler::SpriteTickHandler(Entity* pParentEntity) {
    setParentSprite(pParentEntity);
}

//! Destructeur
SpriteTickHandler::~SpriteTickHandler() {

}

//! Indique quel sprite sera géré par ce gestionnaire.
void SpriteTickHandler::setParentSprite(Sprite* pParentSprite) {
    m_pParentSprite = pParentSprite;
}

//! Indique quel entity sera géré par ce gestionnaire.
void SpriteTickHandler::setParentSprite(Entity* pParentEntity) {
    m_pParentSprite = pParentEntity;
}
