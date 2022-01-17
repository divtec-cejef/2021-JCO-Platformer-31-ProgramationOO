/**
  \file
  \brief    Définition de la classe caisseAmovTickHandler.
  \author   LKU
  \date     janvier 2022
*/
#include "caisseamovtickhandler.h"

const int VITESSE = 5;

CaisseAmovTickHandler::CaisseAmovTickHandler(Entity* pParentEntity,GameCore* newGameCore) : EntityTickHandler(pParentEntity)
{
    setGameCore(newGameCore);
}

//! Cadence : détermine le mouvement que fait le sprite durant le temps écoulé,
//! vérifie si il doit rebondir et le positionne à son nouvel emplacement.
void CaisseAmovTickHandler::tick(long long elapsedTimeInMilliseconds) {

    m_canMove= true;
    m_isPlayer= false;

    //Attire la caisse vers le bas de l'écran
    m_pParentEntity->gravityApplied(elapsedTimeInMilliseconds);

    currentCollision();
    nextCollision();

    if(!m_isPlayer){
        m_pParentEntity->m_velocity.setX(0);
    }

    if(m_pParentEntity->getIsDeath()){
        //Retire la caisse de la scene
        m_pParentEntity->parentScene()->removeSpriteFromScene(m_pParentEntity);

        //Rajoute la caisse dans la scene
        m_pParentEntity->parentScene()->addSpriteToScene(
                    m_pParentEntity,m_pParentEntity->getSpawnPoint());
        m_pParentEntity->setIsDeath(false);
    }

    //Déplace la caisse
    m_pParentEntity->setPos(m_pParentEntity->pos()+ m_pParentEntity->m_velocity);
}

void CaisseAmovTickHandler::currentCollision(){
    //Actuel position de la caisse.
    QRectF CurrentSpriteRect =
            m_pParentEntity->globalBoundingBox().translated(m_pParentEntity->pos());

    // Récupère tous les sprites de la scène qui touche le joueur.
    auto currentCollisionL = m_pParentEntity->parentScene()->collidingSprites(m_pParentEntity);

    // Supprimer le sprite lui-même.
    currentCollisionL.removeAll(m_pParentEntity);

    //Récupère la valeur de liste (remplis/vide).
    bool currentCol  = !currentCollisionL.isEmpty();

    if(currentCol){

        //Cherche les collisions entre le bulio les autres sprites
        for (Sprite* CollisionDetected : currentCollisionL) {

            //Zone de collision entre les 2 sprites.
            QRectF intersected = CurrentSpriteRect.intersected(CollisionDetected->globalBoundingBox());

            //Liste des côtés touché.
            QList<Entity::hitSide> collidingSidesL = QList<Entity::hitSide>();
            //Remplissage de la liste.
            m_pParentEntity->getCollisionLocate(collidingSidesL,CurrentSpriteRect,intersected);

            if (CollisionDetected->data(1) == "joueur") {
                m_isPlayer = true;
                for (int i =0;i < collidingSidesL.count();i++) {
                    switch (collidingSidesL.at(i)) {
                    case Entity::hitSide::UP:
                        break;
                    case Entity::hitSide::DOWN :
                        m_pGameCore->setupCharacterDeath();
                        break;
                    case Entity::hitSide::RIGHT :
                        if(m_canMove)
                            m_pParentEntity->m_velocity.setX(-VITESSE);
                        break;
                    case Entity::hitSide::LEFT :
                        if(m_canMove)
                            m_pParentEntity->m_velocity.setX(VITESSE);
                        break;
                    }
                }
            }
        }
    }
}

void CaisseAmovTickHandler::nextCollision(){
    //Prochaine position de la caisse.
    QRectF nextSpriteRect =
            m_pParentEntity->globalBoundingBox().translated(m_pParentEntity->m_velocity);



    // Récupère tous les sprites de la scène qui touche le joueur.
    auto nextCollisionL = m_pParentEntity->parentScene()->collidingSprites(m_pParentEntity);

    // Supprimer le sprite lui-même.
    nextCollisionL.removeAll(m_pParentEntity);

    //Récupère la valeur de liste (remplis/vide).
    bool nextCollision  = !nextCollisionL.isEmpty();

    if(nextCollision){

        //Cherche les collisions entre le bulio les autres sprites
        for (Sprite* CollisionDetected : nextCollisionL) {

            //Zone de collision entre les 2 sprites.
            QRectF intersected = nextSpriteRect.intersected(CollisionDetected->globalBoundingBox());

            //Liste des côtés touché.
            QList<Entity::hitSide> collidingSidesL = QList<Entity::hitSide>();
            //Remplissage de la liste.
            m_pParentEntity->getCollisionLocate(collidingSidesL,nextSpriteRect,intersected);


            m_pParentEntity->m_velocity.setX(0);
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
                    m_canMove = false;
                    m_pParentEntity->m_velocity.setX(0);
                    m_pParentEntity->setX((CollisionDetected->left()- m_pParentEntity->width()));
                    break;
                case Entity::hitSide::LEFT:
                    m_canMove = false;
                    m_pParentEntity->m_velocity.setX(0);
                    m_pParentEntity->setX(CollisionDetected->right());
                    break;
                }
            }

        }

    }else {
        m_pParentEntity->setIsOnFloor(false);
    }

    if(!m_pParentEntity->parentScene()->isInsideScene(nextSpriteRect)){
        qDebug() << "la caisse a quitté ce monde ;-;";
        m_pParentEntity->setIsDeath(true);
    }
}



void CaisseAmovTickHandler::setGameCore(GameCore* newGameCore){
    m_pGameCore = newGameCore;
}
