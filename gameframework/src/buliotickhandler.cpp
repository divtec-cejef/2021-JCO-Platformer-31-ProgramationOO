/**
  \file
  \brief    Définition de la classe BulioTickHandler.
  \author   LKU
  \date     decembre 2021
*/
#include "buliotickhandler.h"

// Vitesse des bulio
const int SPEED = 10;

BulioTickHandler::BulioTickHandler(Entity* pParentEntity,GameCore* newGameCore) : EntityTickHandler (pParentEntity)
{
    setGameCore(newGameCore);
}

//! Cadence : détermine le mouvement que fait le sprite durant le temps écoulé,
//! vérifie si il doit rebondir et le positionne à son nouvel demplacement.
void BulioTickHandler::tick(long long elapsedTimeInMilliseconds) {
    //Déplace le bulio.
    m_pParentEntity->setPos(m_pParentEntity->pos()+ m_pParentEntity->m_velocity * elapsedTimeInMilliseconds/15.0);

    nextCollision();

    //Attire le bulio vers le bas de l'écran
    m_pParentEntity->gravityApplied(elapsedTimeInMilliseconds);

    if(m_pParentEntity->getIsDeath()){
        //Retire l'ennemie de la scene
        m_pParentEntity->parentScene()->removeSpriteFromScene(m_pParentEntity);
    }
}

//! Vérifie sa collision actuelle
//! se qu'il doit faire.
//! \brief BulioTickHandler::currentCollision
//!
void BulioTickHandler::currentCollision(){

}
//! Vérifie son prochain déplacement et définit
//! se qu'il doit faire
//! \brief BulioTickHandler::nextCollision
//!
void BulioTickHandler::nextCollision(){


    //Prochaine position du bulio.
    QRectF nextSpriteRect =
            m_pParentEntity->globalBoundingBox().translated(m_pParentEntity->m_velocity);

    // Récupère tous les sprites de la scène qui touche le joueur.
    auto listeCurrentCollisionBulio = m_pParentEntity->parentScene()->collidingSprites(m_pParentEntity);

    // Supprimer le sprite lui-même.
    listeCurrentCollisionBulio.removeAll(m_pParentEntity);

    //Récupère la valeur de liste (remplis/vide).
    bool currentCollision  = !listeCurrentCollisionBulio.isEmpty();

    if(currentCollision){
        //Cherche les collisions entre le bulio les autres sprites
        for (Sprite* CollisionDetected : listeCurrentCollisionBulio) {

            //Zone de collision entre les 2 sprites.
            QRectF intersected = nextSpriteRect.intersected(CollisionDetected->globalBoundingBox());

            //Liste des côtés touché.
            QList<Entity::hitSide> collidingSidesL = QList<Entity::hitSide>();
            //Remplissage de la liste.
            m_pParentEntity->getCollisionLocate(collidingSidesL,nextSpriteRect,intersected);

            if (CollisionDetected->data(1) == "joueur") {
                for (int i =0;i < collidingSidesL.count();i++) {
                    if(collidingSidesL.at(i) == Entity::hitSide::UP){
                        //le joueur es entrains de sauté sur le bulio se qui le tue.
                        m_pParentEntity->setIsDeath(true);
                    }
                }
            }else {
                //Si elle n'est pas en collision avec le fantôme alors le sprite collisioné est considéré comme un sol.
                if (CollisionDetected->data(1) != "Ghost") {
                    for (int i =0;i < collidingSidesL.count();i++) {
                        switch (collidingSidesL.at(i)) {
                        case Entity::hitSide::DOWN:
                            m_pParentEntity->setY((CollisionDetected->top()-m_pParentEntity->height()));
                            m_pParentEntity->setIsOnFloor(true);
                            break;
                        case  Entity::hitSide::UP:
                            m_pParentEntity->m_velocity.setY(0);
                            m_pParentEntity->setY((CollisionDetected->bottom()+1));
                            break;
                        case Entity::hitSide::RIGHT:
                            m_pParentEntity->setX((CollisionDetected->left()- m_pParentEntity->width()));
                            m_pParentEntity->m_velocity.setX(-SPEED);
                            break;
                        case Entity::hitSide::LEFT:
                            m_pParentEntity->setX(CollisionDetected->right());
                            m_pParentEntity->m_velocity.setX(SPEED);
                            break;
                        }
                    }
                    collidingSidesL.clear();
                }
            }
        }
    }else {
        m_pParentEntity->setIsOnFloor(false);
    }


    if(!m_pParentEntity->parentScene()->isInsideScene(nextSpriteRect)){
        qDebug() << "Le bulio a quitté ce monde.";
        m_pParentEntity->setIsDeath(true);
    }
}

void BulioTickHandler::setGameCore(GameCore* newGameCore){
    m_pGameCore = newGameCore;
}
