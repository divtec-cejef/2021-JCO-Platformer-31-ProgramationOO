#include "buliotickhandler.h"

BulioTickHandler::BulioTickHandler(Entity* pParentSprite) : SpriteTickHandler (pParentSprite)
{

}

//! Cadence : détermine le mouvement que fait le sprite durant le temps écoulé,
//! vérifie si il doit rebondir et le positionne à son nouvel emplacement.
void BulioTickHandler::tick(long long elapsedTimeInMilliseconds) {
/*ç
    //Déplace le bulio.
    m_pParentSprite->setPos(m_pParentSprite->pos()+ m_pParentSprite->m_velocity);

    if(i == 2){
         qDebug() << "le bulio " << i << " touche le sol : " << m_pBulioL.at(i)->getIsOnFloor();
    }

    //Attire le bulio vers le bas de l'écran
    gravityApplied(m_pBulioL.at(i),elapsedTimeInMilliseconds);

    //Prochaine position du bulio.
    QRectF nextSpriteRect =
            m_pBulioL.at(i)->globalBoundingBox().translated(m_pBulioL.at(i)->m_velocity);

    // Récupère tous les sprites de la scène qui touche le joueur.
    auto listeCurrentCollisionBulio = m_pBulioL.at(i)->parentScene()->collidingSprites(m_pBulioL.at(i));

    // Supprimer le sprite lui-même.
    listeCurrentCollisionBulio.removeAll(m_pBulioL.at(i));

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
            getCollisionLocate(collidingSidesL,nextSpriteRect,intersected);

            for (int i =0;i < collidingSidesL.count();i++) {
                switch (collidingSidesL.at(i)) {
                case Entity::hitSide::DOWN:
                    m_pBulioL.at(i)->m_velocity.setY(0.0);
                    m_pBulioL.at(i)->setIsOnFloor(true);
                    //qDebug() << "touche les pied";
                    break;
                case  Entity::hitSide::UP:
                    //m_pBulioL.at(i)->m_velocity.setY(0.0);
                    qDebug() << "touche la tete";
                    break;
                case Entity::hitSide::RIGHT:
                    m_pBulioL.at(i)->m_velocity.setX(-5);
                    qDebug() << "touche coté droit";
                    break;
                case Entity::hitSide::LEFT:
                    m_pBulioL.at(i)->m_velocity.setX(5);
                    qDebug() << "touche coté gauche";
                    break;
                }
            }

            if (CollisionDetected->data(1) == "joueur") {

                for (int i =0;i < collidingSidesL.count();i++) {
                    switch (collidingSidesL.at(i)) {
                    case Entity::hitSide::DOWN:
                        setupCharacterDeath();;
                        break;
                    case  Entity::hitSide::UP:
                        m_pBulioL.at(i)->setIsDeath(true);
                        pCharacter->m_velocity.setY(-7);
                        pCharacter->setIsJump(true);
                        break;
                    case Entity::hitSide::RIGHT :
                        setupCharacterDeath();
                        break;
                    case Entity::hitSide::LEFT :
                        setupCharacterDeath();
                        break;
                    }
                }
            }
            //m_pBulioL.at(i)->setIsOnFloor(true);
            //m_pBulioL.at(i)->m_velocity.setY(0.0);
            collidingSidesL.clear();
        }
    }else {
        m_pBulioL.at(i)->setIsOnFloor(false);
    }

    if(!m_pBulioL.at(i)->parentScene()->isInsideScene(nextSpriteRect)){
        qDebug() << "Bulio " << i << "a quitté se monde ;-;";
        m_pBulioL.at(i)->setIsDeath(true);
    }



    if(m_pBulioL.at(i)->getIsDeath()){
        //Retire l'ennemie de la scene
        m_pScene->removeSpriteFromScene(m_pBulioL.at(i));
        //Retire l'ennemie de la liste
        m_pBulioL.removeAt(i);
        bulioCount--;
    }
}
//Attire le joueur vers le bas de l'écran
gravityApplied(pCharacter,elapsedTimeInMilliseconds);
*/
}
