#include "entity.h"
#include "character.h"

#include <cmath>
#include <QDebug>
#include <QSettings>

#include "utilities.h"
#include "playertickhandler.h"
#include "sprite.h"
#include "time.h"

//Ajoute Supp
#include <QString>
#include "gamescene.h"
#include "gamecanvas.h"
#include "resources.h"

//!
//! \brief Entity::Entity
//! \param rPixmap
//! \param pParent
//!
Entity::Entity(const QPixmap& rPixmap, QGraphicsItem* pParent) : Sprite(rPixmap,pParent)
{

}

///!Permet de configurer l'animation d'une entité
//! \brief Entity::configureAnimation
//!
void Entity::configureAnimation(){

}

//! Permet de savoir si l'entité touche le sol
//! \brief Entity::getIsOnFloor
//! \return un booléane
//!
bool Entity::getIsOnFloor(){
    return this->m_isOnFloor;
}

//! Permet de définir si l'entité touche le sol ou non
//! \brief Entity::setIsOnFloor
//! \param _isOnFloor  la nouvelle valeur de m_isOnFloor
//!
void Entity::setIsOnFloor(bool _isOnFloor){
    this->m_isOnFloor = _isOnFloor;
}

//! Permet de s'avoir si l'entité est morte
//! \brief Entity::getIsDeath
//! \return un booléane
//!
bool Entity::getIsDeath(){
    return this->m_isDeath;
}

//! Permet de définir si l'entité doit périre ou non.
//! \brief Entity::setIsDeath
//! \param _isOnFloor la nouvelle valeur de m_isDeath.
//!
void Entity::setIsDeath(bool _isDeath){
    this->m_isDeath = _isDeath;
}

//! Permet de rendre les éléments de la liste unique
//! \brief uniqueSide
//! \param collidingSidesList liste à testé
//! \param appendToSide élément à apprendre
//!
void Entity::uniqueSide(QList<hitSide>* collidingSidesList, hitSide appendToSide){
    if (!collidingSidesList->contains(appendToSide)) {
            collidingSidesList->append(appendToSide);
        }
}

//!
//! \brief GameCore::gravityApplied
//! \param entity sprite au quel on applique la gravité
//! \param enti_velocity velocité du sprite
//! \param elapsedTime temps écoulé entre chaque tick.
//!@brief GameCore::gravityApplied
void Entity::gravityApplied(long long elapsedTime){
    this->setPos(this->pos() + this->m_velocity * (elapsedTime/100.0));
    this->m_velocity += m_gravity * (elapsedTime/100.0);
}

void Entity::setScene(GameScene* newScene){
    m_pScene = newScene;

}
