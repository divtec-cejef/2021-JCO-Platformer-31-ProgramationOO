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
        iSprite = "MarcheGaucheV5.png";
        break;
    case DEPLA_DROITE:
        iSprite =  "MarcheDroiteV5.png";
        break;
    case SAUT:
        iSprite = "BasicPoseV5.png";
        break;
    case BASE:
        iSprite = "BasicPoseV1.png";
    }

    if(iSprite == "MarcheDroiteV4.png" || iSprite == "MarcheGaucheV4.png"){

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
        m_player->addAnimationFrame(GameFramework::imagesPath() + "BasicPoseV1.png");
        qDebug() << "BASE " << iSprite;

    }
    m_player->startAnimation(25);


    //pSprite->setAnimationSpeed(25);
    //}else{
    //pSprite = new Sprite(GameFramework::imagesPath() + "BasicPoseGauche.png");
    //}
}
