/**
  \file
  \brief    Définition de la classe Character.
  @author   LKU
  @date     Decembre 2021
 */
#include "character.h"

#include <cmath>
#include <QDebug>
#include <QSettings>

#include "utilities.h"
#include "sprite.h"
#include "time.h"

#include <QString>
#include "gamescene.h"
#include "gamecanvas.h"
#include "resources.h"


//! spriteSheet animation de marche à gauche/droite
const int FRAME_WIDTH = 60;
const int FRAME_HEIGHT = 60;
const int FRAME_COUNT = 4;
const int COLUMN_COUNT = 2;

//!
//! Construit le character du joueur et l'initialise.
//! @param   pParent Pointeur sur le parent (afin d'obtenir une destruction automatique de cet objet).
//!
Character::Character(QGraphicsItem* pParent) : Entity(GameFramework::imagesPath() + "BasicPoseV4.png", pParent)
{

}

//! Permet de récupéré l'etat du joueur (si il saute ou non)
//! @return si le joueur saute.
bool Character::getIsJump(){
    return this->m_isJump;
}

//!
//! Permet de définir si le joueur est entrains de sauter ou non.
//! @param _isJump nouvelle état du joueur.
//!
void Character::setIsJump(bool _isJump){
    this->m_isJump = _isJump;
}

//!
//! Permet de définir si le joueur est sur le sol ou non.
//! @param _isOnFloor nouvelle état du joueur.
//!
void Character::setIsOnFloor(bool _isOnFloor){
    this->m_isOnFloor = _isOnFloor;
}

//!
//! Permet de définir si le joueur doit être en vie ou non.
//! @brief Character::setIsDeath
//! @param _isDeath nouvelle état du joueur.
//!
void Character::setIsDeath(bool _isDeath){
    this->m_isDeath = _isDeath;
}

//! Permet de savoir le nombre de mort du joueur.
//! \return retour le nombre de mort du joueur.
//!
int Character::getDeathCount(){
    return this->m_deathCount;
}

//! Augemente le compteur de mort
void Character::incrementDeathCount(){
    this->m_deathCount++;
    qDebug() << "Nombre de mort(s) : " << this->m_deathCount;
}


//!
//! Définit l'animation dans la quel le sprite du joueur doit être.
//! @brief Character::configureAnimation
//! @param player animation du joueur paramétrer
//!
void Character::configureAnimation(animation player) {

    if(player != m_lastAnim){
        clearAnimations();
        QString iSprite;

        switch (player) {
        case DEPLACEMENT:
            iSprite = "MarcheDroiteV9.png";
            break;
        case SAUT:
            iSprite = "SautDroiteV7.png";
            break;
        default:
            iSprite = "BasicPoseV4.png";
            break;
        }

        QImage directionFrame(GameFramework::imagesPath() + iSprite);
        if(iSprite == "MarcheDroiteV9.png"){

            QImage spriteSheet(GameFramework::imagesPath() + iSprite);

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
                //ajoute la frame à l'animation.
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
        m_lastAnim = player;
    }
}

//!
//! Reste tout les valeurs du joueur comme elles étaient à leur inisialisation.
//! @brief Character::respawn
//!
void Character::respawn(){

    this->setIsJump(false);
    this->setIsOnFloor(false);
    this->setIsDeath(false);

    QPointF velocityReste = QPointF(0,0);
    this->m_velocity = velocityReste;
}
