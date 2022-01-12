/**
  \file
  \brief    Définition de la classe BulioTickHandler.
  \author   LKU
  \date     decembre 2021
*/
#include "buliotickhandler.h"


BulioTickHandler::BulioTickHandler(Entity* pParentEntity,GameCore* newGameCore) : EntityTickHandler (pParentEntity)
{
    setGameCore(newGameCore);
}

//! Cadence : détermine le mouvement que fait le sprite durant le temps écoulé,
//! vérifie si il doit rebondir et le positionne à son nouvel emplacement.
void BulioTickHandler::tick(long long elapsedTimeInMilliseconds) {


    //Déplace le bulio.
    m_pParentEntity->setPos(m_pParentEntity->pos()+ m_pParentEntity->m_velocity);

    //Attire le bulio vers le bas de l'écran
    m_pParentEntity->gravityApplied(elapsedTimeInMilliseconds);

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
                    switch (collidingSidesL.at(i)) {
                    case Entity::hitSide::DOWN:
                        break;
                    case  Entity::hitSide::UP:
                        m_pParentEntity->setIsDeath(true);
                        break;
                    case Entity::hitSide::RIGHT :

                        break;
                    case Entity::hitSide::LEFT :
                        break;
                    }
                }
            }else {
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
                        m_pParentEntity->m_velocity.setX(-5);
                        break;
                    case Entity::hitSide::LEFT:
                        m_pParentEntity->setX(CollisionDetected->right());
                        m_pParentEntity->m_velocity.setX(5);
                        break;
                    }
                }
                collidingSidesL.clear();
            }
        }
    }else {
        m_pParentEntity->setIsOnFloor(false);
    }

    if(!m_pParentEntity->parentScene()->isInsideScene(nextSpriteRect)){
        qDebug() << "Bulio a quitté se monde ;-;";
        m_pParentEntity->setIsDeath(true);
    }

    if(m_pParentEntity->getIsDeath()){
        //Retire l'ennemie de la scene
        m_pParentEntity->parentScene()->removeSpriteFromScene(m_pParentEntity);
    }
}

void BulioTickHandler::currentCollision(){

}

void BulioTickHandler::nextCollision(){}

void BulioTickHandler::setGameCore(GameCore* newGameCore){
    m_pGameCore = newGameCore;
}
