
#include "bulio.h"
#include "utilities.h"
#include "playertickhandler.h"
#include "sprite.h"
#include "time.h"

//Ajoute Supp
#include <QString>
#include "gamescene.h"
#include "gamecanvas.h"
#include "resources.h"

// Vitesse des bulio
const int VITESSE_DEPLACEMENT = 5;

//Type d'animation du joueurs
const int NBR_ANIMATION = 2;

//! spriteSheet animation de marche à gauche/droite
const int FRAME_WIDTH = 38;
const int FRAME_HEIGHT = 48;
const int FRAME_COUNT = 2;
const int COLUMN_COUNT = 1;

Bulio::Bulio(QGraphicsItem* pParent) : Entity(GameFramework::imagesPath() + "bastienbulioBaseV1.png", pParent)
{

}


//!
//! @brief Bulio::getIsOnFloor
//! @return si le joueur est sur le sol.
//!
bool Bulio::getIsOnFloor(){
    return this->m_isOnFloor;
}

//!
//! Permet de définir si le joueur est sur le sol ou non.
//! @brief Bulio::setIsOnFloor
//! @param _isOnFloor nouvelle état du joueur.
//!
void Bulio::setIsOnFloor(bool _isOnFloor){
    this->m_isOnFloor = _isOnFloor;
}

//!
//! @brief Bulio::getIsDeath
//! @return si le joueur est mort.
//!
bool Bulio::getIsDeath(){
    return this->m_isDeath;
}

//!
//! Permet de définir si le joueur doit être en vie ou non.
//! @brief Bulio::setIsDeath
//! @param _isDeath nouvelle état du joueur.
//!
void Bulio::setIsDeath(bool _isDeath){
    this->m_isDeath = _isDeath;
}

//!
//! @brief Character::getVelocity
//! @return la velocité actuel du joueur
//!
QPointF Bulio::getVelocity(){
    return m_velocity;
};

//!
//! Définit l'animation dans la quel le sprite du joueur doit être.
//! @brief Character::configureAnimation
//! @param player animation du joueur paramétrer
//!
void Bulio::configureAnimation(animation bulio) {

    clearAnimations();
    QString iSprite;

    switch (bulio) {
    case DEPLACEMENT:
        iSprite = "bastienbulioDeplacementV1.png";
        break;
    default:
        iSprite = "bastienbulioBaseV1.png";
        break;
    }

    QImage directionFrame(GameFramework::imagesPath() + iSprite);
    if(iSprite == "bastienbulioV1.png"){

        QImage spriteSheet(GameFramework::imagesPath() + iSprite);

        //QList<QImage> listFrame;
        // Découpage de la spritesheet
        for (int frameIndex = 0; frameIndex < FRAME_COUNT; frameIndex++) {
            QImage frameSheet = spriteSheet.copy((frameIndex % COLUMN_COUNT) * FRAME_WIDTH,
                                                 (frameIndex / COLUMN_COUNT) * FRAME_HEIGHT,
                                                 FRAME_WIDTH, FRAME_HEIGHT);

            //Oriente l'animation selon la velocité du joueur
            if(m_velocity.x() < 0)
                directionFrame = frameSheet.mirrored(true,false);
            else
                directionFrame = frameSheet;

            addAnimationFrame(QPixmap::fromImage(directionFrame.scaled(FRAME_WIDTH * 1,
                                                                       FRAME_HEIGHT * 1,
                                                                       Qt::IgnoreAspectRatio,
                                                                       Qt::SmoothTransformation)));
        }

    }else {
        //Oriente l'animation selon l'actuel ou l'ancienne velocité du joueur
        if(m_velocity.x() < 0 || m_lastVelocity.x() < 0)
            directionFrame = directionFrame.mirrored(true,false);

        addAnimationFrame(QPixmap::fromImage(directionFrame.scaled(FRAME_WIDTH * 1,
                                                                   FRAME_HEIGHT * 1,
                                                                   Qt::IgnoreAspectRatio,
                                                                   Qt::SmoothTransformation)));
    }
    startAnimation(25);

}

///!
//! \brief Bulio::collisionDetection
//! \param rect position de l'entité dans l'espace.
//!
void Bulio::collisionDetection(QRectF rect){

    // ////////////////// //
    // CURRENT COLLISION  //
    // ////////////////// //

    QList<hitSide> collidingSides = QList<hitSide>();

    // Récupère tous les sprites de la scène qui touche le joueur
    auto listeCurrentCollisionEnnemie = this->parentScene()->collidingSprites(this);
    // Supprimer le sprite lui-même
    listeCurrentCollisionEnnemie.removeAll(this);

    //récupère la valeur de liste (remplis/vide)
    bool currentCollision  = !listeCurrentCollisionEnnemie.isEmpty();

    if(currentCollision){
        //Cherche les collisions entre le joueurs les autres sprites
        for (Sprite* CollisionDetected : listeCurrentCollisionEnnemie) {

            QRectF intersected = rect.intersected(CollisionDetected->globalBoundingBox());

            if (intersected.width() > intersected.height() && intersected.width() > 10) {
                if (intersected.center().y() < rect.center().y())
                    uniqueSide(&collidingSides, hitSide::UP);
                else
                    uniqueSide(&collidingSides, hitSide::DOWN);
            } else if (intersected.width() < intersected.height() && intersected.height() > 10){
                if (intersected.center().x() < rect.center().x())
                    uniqueSide(&collidingSides, hitSide::LEFT);
                else
                    uniqueSide(&collidingSides, hitSide::RIGHT);
            }

            if (CollisionDetected->data(1) == "sol") {
                for (hitSide CurrentSide : collidingSides) {

                    switch (collidingSides.takeAt(CurrentSide)) {
                    case hitSide::DOWN:
                        this->m_velocity.setY(0.0);
                        //this->setIsJump(false);
                        break;
                    case  hitSide::UP:
                        this->m_velocity.setY(0.0);
                        break;
                    case hitSide::RIGHT :
                        this->m_velocity.setX(-VITESSE_DEPLACEMENT);
                        break;
                    case hitSide::LEFT :
                        this->m_velocity.setX(VITESSE_DEPLACEMENT);
                        break;
                    }
               }
            }else if (CollisionDetected->data(1) == "joueur") {
                qDebug()<<"NON PAS LUI";
                for (hitSide CurrentSide : collidingSides) {

                    if(CurrentSide == hitSide::UP){
                        setIsDeath(true);
                        m_pScene->removeSpriteFromScene(this);
                    }
               }
            }
        }
    }else {
        this->setIsOnFloor(false);
    }
}


void Bulio::move(long long elapsedTimeInMilliseconds){

     this->setPos(this->pos()+ this->m_velocity);

    if (!this->getIsOnFloor()){
        //Attire le joueur vers le bas de l'écran
        gravityApplied(elapsedTimeInMilliseconds);
    }
    collisionDetection(globalBoundingBox().translated(m_velocity));
}


