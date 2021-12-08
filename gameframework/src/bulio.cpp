
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
//! @brief Bulio::getIsJump
//! @return si le joueur saute.
//!
bool Bulio::getIsJump(){
    return this->m_isJump;
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
