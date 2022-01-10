#include "entity.h"
#include "character.h"


//Ajoute Supp
#include <cmath>
#include <QDebug>

#include "sprite.h"
#include "gamescene.h"
#include "gamecanvas.h"
#include "resources.h"

//!
//! \param rPixmap
//! \param pParent
//!
Entity::Entity(const QPixmap& rPixmap, QGraphicsItem* pParent) : Sprite(rPixmap,pParent)
{

}

///!Permet de configurer l'animation d'une entité
//!
void Entity::configureAnimation(){

}

//! Permet de savoir si l'entité touche le sol
//! \return un booléane
//!
bool Entity::getIsOnFloor(){
    return this->m_isOnFloor;
}

//! Permet de définir si l'entité touche le sol ou non
//! \param _isOnFloor  la nouvelle valeur de m_isOnFloor
//!
void Entity::setIsOnFloor(bool _isOnFloor){
    this->m_isOnFloor = _isOnFloor;
}

//! Permet de s'avoir si l'entité est morte
//! \return un booléane
//!
bool Entity::getIsDeath(){
    return this->m_isDeath;
}

//! Permet de définir si l'entité doit périre ou non.
//! \param _isDeath la nouvelle valeur de m_isDeath.
//!
void Entity::setIsDeath(bool _isDeath){
    this->m_isDeath = _isDeath;
}

//! Ajoute à une liste la localisation des collision entre l'entité et un sprite.
//! \param collisionLocateList
//! \param posSprite Position du Sprite principal.
//! \param intersected zone de collision entre les deux sprites.
//!
void Entity::getCollisionLocate(QList<Entity::hitSide>&collisionLocateL,
                                  QRectF posSprite,QRectF intersected){

    //Si l'intersected est plus large la collision est vertical.
    if (intersected.width() > intersected.height() && intersected.width() > 10) {
        if (intersected.center().y() < posSprite.center().y())
            //Détermine le haut
            Entity::uniqueSide(&collisionLocateL, Entity::hitSide::UP);
        else
            //Détermine le bas
            Entity::uniqueSide(&collisionLocateL, Entity::hitSide::DOWN);

      //Sinon si la collision est plus haut que large est horizontal.
    } else if (intersected.width() < intersected.height() && intersected.height() > 10){
        if (intersected.center().x() < posSprite.center().x())
            //Détermine la gauche
            Entity::uniqueSide(&collisionLocateL, Entity::hitSide::LEFT);
        else
            //Détermine la droite
            Entity::uniqueSide(&collisionLocateL, Entity::hitSide::RIGHT);
    }
}

//! Permet de rendre les éléments de la liste unique
//! \param collidingSidesList liste à testé
//! \param appendToSide élément à apprendre
//!
void Entity::uniqueSide(QList<hitSide>* collidingSidesList, hitSide appendToSide){
    if (!collidingSidesList->contains(appendToSide)) {
            collidingSidesList->append(appendToSide);
        }
}

//! Applique la gravité à l'entité.
//! \param entity sprite au quel on applique la gravité
//! \param enti_velocity velocité du sprite
//! \param elapsedTime temps écoulé entre chaque tick.
void Entity::gravityApplied(long long elapsedTime){

    if (!this->getIsOnFloor()){
    this->setPos(this->pos() + this->m_velocity * (elapsedTime/100.0));
    this->m_velocity += m_gravity * (elapsedTime/100.0);
    }
}

//! Définit la scene sur la quel l'entité est liée.
//! \brief Entity::setScene
//! \param newScene
//!
void Entity::setScene(GameScene* newScene){
    m_pScene = newScene;

}
