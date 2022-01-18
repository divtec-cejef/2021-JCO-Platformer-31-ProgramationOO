/**
  \file
  \brief    Définition de la classe Bulio.
  @author   LKU
  @date     Decembre 2021
 */
#include "bulio.h"

#include <QString>

#include "resources.h"
#include "utilities.h"
#include "sprite.h"
#include "gamescene.h"
#include "gamecanvas.h"




//Vitesse d'animation
const int VITESSE_ANIM = 100;

//! spriteSheet animation de marche à gauche/droite
const int FRAME_WIDTH = 76;
const int FRAME_HEIGHT = 48;
const int FRAME_COUNT = 2;
const int COLUMN_COUNT = 1;

Bulio::Bulio(QGraphicsItem* pParent) : Entity(GameFramework::imagesPath() + "bulioBaseV1.png", pParent)
{
    configureAnimation(DEPLACEMENT);
}

//!
//! Permet de définir si le bulio est sur le sol ou non.
//! @param _isOnFloor nouvelle état du bulio.
//!
void Bulio::setIsOnFloor(bool _isOnFloor){
    this->m_isOnFloor = _isOnFloor;
}


//!
//! Permet de définir si le bulio doit être en vie ou non.
//! @brief Bulio::setIsDeath
//! @param _isDeath nouvelle état du bulio.
//!
void Bulio::setIsDeath(bool _isDeath){
    this->m_isDeath = _isDeath;
}

//!
//! Définit l'animation dans la quel le sprite du bulio doit être.
//! @brief Character::configureAnimation
//! @param player animation du bulio paramétrer
//!
void Bulio::configureAnimation(animation bulio) {

    clearAnimations();
    QString iSprite;

    switch (bulio) {
    case DEPLACEMENT:
        iSprite = "bulioDeplacementV3.png";
        break;
    default:
        iSprite = "bulioBaseV1.png";
        break;
    }

    /*
    if(m_velocity.x() != 0){
        iSprite = "bastienbulioDeplacementV3.png";
    }else {
        iSprite = "bastienbulioBaseV1.png";
    }
    */

    QImage directionFrame(GameFramework::imagesPath() + iSprite);
    if(iSprite == "bulioDeplacementV3.png"){

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
    startAnimation(VITESSE_ANIM);

}
