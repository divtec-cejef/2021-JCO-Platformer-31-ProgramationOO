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
#include "time.h"

//Ajoute Supp
#include <QString>

//Type d'animation du joueurs
enum ANIM_PLAYER{
    SAUT,
    DEPLA_GAUCHE,
    DEPLA_DROITE,
    ATTA_GAUCHE,
    ATTA_DROITE,
    BASE
};

//spriteSheet animation de marche à gauche
const int FRAME_WIDTH = 192;
const int FRAME_HEIGHT = 192;
const int FRAME_COUNT = 4;
const int COLUMN_COUNT = 2;

struct collisionDistance{
    double top;
    double down;
    double right;
    double left;

};

Character::Character(Sprite* _Player)
{
    m_player = _Player;
}


void Character::configureAnimation(ANIM_PLAYER animation) {

    m_player->clearAnimations();
    QString iSprite;

    switch (animation) {
    case DEPLA_GAUCHE:
        iSprite = "MarcheGaucheV7.png";
        break;
    case DEPLA_DROITE:
        iSprite =  "MarcheDroiteV7.png";
        break;
    case SAUT:
        iSprite = "SautDroiteV1.png";
        break;
    case BASE:
        iSprite = "BasicPoseV2.png";
    }

    if(iSprite == "MarcheDroiteV7.png" || iSprite == "MarcheGaucheV7.png"){

        QImage spriteSheet(GameFramework::imagesPath() + iSprite);

        // Découpage de la spritesheet
        for (int frameIndex = 0; frameIndex < FRAME_COUNT; frameIndex++) {
            QImage sprite = spriteSheet.copy((frameIndex % COLUMN_COUNT) * FRAME_WIDTH,
                                             (frameIndex / COLUMN_COUNT) * FRAME_HEIGHT,
                                             FRAME_WIDTH, FRAME_HEIGHT);

            m_player->addAnimationFrame(QPixmap::fromImage(sprite.scaled(FRAME_WIDTH * 1,
                                                                        FRAME_HEIGHT * 1,
                                                                        Qt::IgnoreAspectRatio,
                                                                        Qt::SmoothTransformation)));
        }

        // qDebug() << "MARCHE "<< iSprite;
    }else {
        //pSprite = new Sprite(GameFramework::imagesPath() + "BasicPoseV1.png");
        m_player->addAnimationFrame(GameFramework::imagesPath() + iSprite);
        //qDebug() << "BASE " << iSprite;

    }
    m_player->startAnimation(25);
}


