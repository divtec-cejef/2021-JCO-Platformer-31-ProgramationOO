#include "character.h"

#include <cmath>
#include <QDebug>
#include <QSettings>

#include "utilities.h"
#include "playertickhandler.h"
#include "sprite.h"
#include "time.h"


#include "gamescene.h"
#include "gamecanvas.h"
#include "resources.h"
#include "utilities.h"
#include "playertickhandler.h"
#include "sprite.h"

//Ajoute Supp
#include <QString>

//Type d'animation du joueurs
enum animation{
    SAUT,
    DEPLA_GAUCHE,
    DEPLA_DROITE,
    ATTA_GAUCHE,
    ATTA_DROITE,
    BASE
};

//spriteSheet animation de marche à gauche
const int FRAME_WIDTH = 96;
const int FRAME_HEIGHT = 96;
const int FRAME_COUNT = 4;
const int COLUMN_COUNT = 2;

//Déplcament du joueur
const int PLAYER_SPEED = 10 ; // vitesse de déplacement du joueur en pixels/s
const int PLAYER_JUMP= -10 ; //Vitesse du saute
const int PLAYER_STOP = 0;

struct collisionDistance{
    double top;
    double down;
    double right;
    double left;

};

Character::Character(QGraphicsItem* pParent) : Sprite(GameFramework::imagesPath() + "BasicPoseV2.png", pParent)
{
    //m_keyUpPressed    = false;
    //m_keyDownPressed  = false;
    //m_keyLeftPressed  = false;
    //m_keyRightPressed = false;
    //m_playerm_velocity = QPointF(0,0);
}


QPointF Character::getVelocity(){
    return m_velocity;
};

void Character::configureAnimation(animation player) {

    clearAnimations();
    QString iSprite;

    switch (player) {
    case DEPLA_GAUCHE:
        iSprite = "MarcheGaucheV7.png";
        break;
    case DEPLA_DROITE:
        iSprite =  "MarcheDroiteV7.png";
        break;
    case SAUT:
        iSprite = "SautDroiteV1.png";
        break;
    default:
        iSprite = "BasicPoseV2.png";
        break;
    }

    if(iSprite == "MarcheDroiteV7.png" || iSprite == "MarcheGaucheV7.png"){

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


//! Traite la pression d'une touche.
//! \param key Numéro de la touche (voir les constantes Qt)
//!
void Character::onKeyPressed(int key) {
    //emit notifyKeyPressed(key);

    Character::animation player;

    switch(key) {
    case Qt::Key_Left:
        m_velocity.setX(-PLAYER_SPEED);
        player = DEPLA_GAUCHE;
        break;

    case Qt::Key_Right:
        m_velocity.setX(PLAYER_SPEED);
        player = DEPLA_DROITE;
        break;

    case Qt::Key_Up:
        if(isOnFloor){
            player = SAUT;
            m_velocity.setY(PLAYER_JUMP);
            isJump = true;
            qDebug() << "isJump : " << isJump;
        }else{
            player = BASE;
        }
        //qDebug() << "m_velocity y : " << m_velocity.y();
        break;

    case Qt::Key_A:
        m_velocity.setX(-PLAYER_SPEED);
        player = DEPLA_GAUCHE;
        break;

    case Qt::Key_D:
        m_velocity.setX(PLAYER_SPEED);
        player = DEPLA_DROITE;
        break;

    case Qt::Key_Space:
        //if(isOnFloor){
        player = SAUT;
        m_velocity.setY(PLAYER_JUMP);
        isJump = true;
        //qDebug() << "isJump : " << isJump;
        //}
        break;

    default:
        player = BASE;
    }
     //m_character(pCharacter).configureAnimation();
    configureAnimation(player);
}

//! Traite le relâchement d'une touche.
//! \param key Numéro de la touche (voir les constantes Qt)
void Character::onKeyReleased(int key) {
    //emit notifyKeyReleased(key);

    switch(key) {
    case Qt::Key_Left:
        m_velocity.setX(PLAYER_STOP);
        //distanceLeft = PLAYER_STOP;
        break;

    case Qt::Key_Right:
        m_velocity.setX(PLAYER_STOP);
        //distanceRight = PLAYER_STOP;
        break;
    case Qt::Key_Up:
        m_velocity.setY(PLAYER_STOP);
        //isJump = false;
        //qDebug() << "isJump : " << isJump;
        break;

    case Qt::Key_A:
        m_velocity.setX(PLAYER_STOP);
        break;

    case Qt::Key_D:
        m_velocity.setX(PLAYER_STOP);
        break;

    case Qt::Key_Space:
        m_velocity.setY(PLAYER_STOP);
        isJump = false;
        break;
    }
    //if(!isOnFloor)
        //pCharacter->configureAnimation(Character::SAUT);
    //else {
        configureAnimation(Character::BASE);
    //}
}
