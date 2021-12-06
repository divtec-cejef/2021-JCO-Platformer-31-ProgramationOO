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

//Type d'animation du joueurs
enum animation{
    SAUT,
    DEPLA_GAUCHE,
    DEPLA_DROITE,
    ATTA_GAUCHE,
    ATTA_DROITE,
    BASE
};

//spriteSheet animation de marche à gauche/droite
const int FRAME_WIDTH = 60;
const int FRAME_HEIGHT = 60;
const int FRAME_COUNT = 4;
const int COLUMN_COUNT = 2;

struct collisionDistance{
    double top;
    double down;
    double right;
    double left;

};

/**
 * Construit le character du joueur et l'initialise.
 * @brief Character::Character
 * @param   pParent Pointeur sur le parent (afin d'obtenir une destruction automatique de cet objet).
 */
Character::Character(QGraphicsItem* pParent) : Sprite(GameFramework::imagesPath() + "BasicPoseV4.png", pParent)
{

}

/**
 * @brief Character::getIsJump
 * @return si le joueur saute.
 */
bool Character::getIsJump(){
    return this->isJump;
}

/**
 * Permet de définir si le joueur est entrains de sauter ou non.
 * @brief Character::setIsJump
 * @param _isJump nouvelle état du joueur.
 */
void Character::setIsJump(bool _isJump){
    this->isJump = _isJump;
}

/**
 * @brief Character::getIsOnFloor
 * @return si le joueur est sur le sol.
 */
bool Character::getIsOnFloor(){
    return this->isOnFloor;
}

/**
 * Permet de définir si le joueur est sur le sol ou non.
 * @brief Character::setIsOnFloor
 * @param _isOnFloor nouvelle état du joueur.
 */
void Character::setIsOnFloor(bool _isOnFloor){
    this->isOnFloor = _isOnFloor;
}

/**
 * @brief Character::getIsDeath
 * @return si le joueur est mort.
 */
bool Character::getIsDeath(){
    return this->isDeath;
}

/**
 * Permet de définir si le joueur doit être en vie ou non.
 * @brief Character::setIsDeath
 * @param _isDeath nouvelle état du joueur.
 */
void Character::setIsDeath(bool _isDeath){
    this->isDeath = _isDeath;
}

/**
 * @brief Character::getVelocity
 * @return la velocité actuel du joueur
 */
QPointF Character::getVelocity(){
    return m_velocity;
};

/**
 *
 * @brief Character::configureAnimation
 * @param player animation du joueur paramétrer
 */
void Character::configureAnimation(animation player) {

    clearAnimations();
    QString iSprite;

    switch (player) {
    case DEPLA_GAUCHE:
        iSprite = "MarcheGaucheV9.png";
        break;
    case DEPLA_DROITE:
        iSprite =  "MarcheDroiteV9.png";
        break;
    case SAUT:
        iSprite = "SautDroiteV7.png";
        break;
    default:
        iSprite = "BasicPoseV4.png";
        break;
    }

    if(iSprite == "MarcheDroiteV9.png" || iSprite == "MarcheGaucheV9.png"){

        QImage spriteSheet(GameFramework::imagesPath() + iSprite);

        // Découpage de la spritesheet
        for (int frameIndex = 0; frameIndex < FRAME_COUNT; frameIndex++) {
            QImage sprite = spriteSheet.copy((frameIndex % COLUMN_COUNT) * FRAME_WIDTH,
                                             (frameIndex / COLUMN_COUNT) * FRAME_HEIGHT,
                                             FRAME_WIDTH, FRAME_HEIGHT);

            addAnimationFrame(QPixmap::fromImage(sprite.scaled(FRAME_WIDTH * 1,
                                                                        FRAME_HEIGHT * 1,
                                                                        Qt::IgnoreAspectRatio,
                                                                        Qt::SmoothTransformation)));
        }

        // qDebug() << "MARCHE "<< iSprite;
    }else {
        //pSprite = new Sprite(GameFramework::imagesPath() + "BasicPoseV1.png");
        addAnimationFrame(GameFramework::imagesPath() + iSprite);
        //qDebug() << "BASE " << iSprite;

    }
    startAnimation(25);
}

/**
 * Reste tout les valeurs du joueur comme elles étaient à leur inisialisation.
 * @brief Character::respawn
 */
void Character::respawn(){

    this->setIsJump(false);
    this->setIsOnFloor(false);
    this->setIsDeath(false);

    QPointF velocityReste = QPointF(0,0);
    this->m_velocity = velocityReste;
}

void Character::setAnimationDeplacementList(){
/*
    QString iSprite;

    switch (iSprite) {
    case DEPLA_GAUCHE:
        iSprite = "MarcheGaucheV9.png";
        break;
    case DEPLA_DROITE:
        iSprite =  "MarcheDroiteV9.png";
        break;
    case SAUT:
        iSprite = "SautDroiteV7.png";
        break;
    default:
        iSprite = "BasicPoseV4.png";
        break;
    }

    if(iSprite == "MarcheDroiteV9.png" || iSprite == "MarcheGaucheV9.png"){

        QImage spriteSheet(GameFramework::imagesPath() + iSprite);

        // Découpage de la spritesheet
        for (int frameIndex = 0; frameIndex < FRAME_COUNT; frameIndex++) {
            QImage sprite = spriteSheet.copy((frameIndex % COLUMN_COUNT) * FRAME_WIDTH,
                                             (frameIndex / COLUMN_COUNT) * FRAME_HEIGHT,
                                             FRAME_WIDTH, FRAME_HEIGHT);

            QImage CurrentAnimImage(QPixmap::fromImage(sprite.scaled(FRAME_WIDTH * 1,
                                                                        FRAME_HEIGHT * 1,
                                                                        Qt::IgnoreAspectRatio,
            m_AnimationDeplacementList.append(CurrentAnimImage);                                                         Qt::SmoothTransformation)));
        }
*/
}




