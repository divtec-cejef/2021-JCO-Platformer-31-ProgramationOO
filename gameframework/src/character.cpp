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

Character::Character(QGraphicsItem* pParent) : Sprite(GameFramework::imagesPath() + "BasicPoseV4.png", pParent)
{

}


QPointF Character::getVelocity(){
    return m_velocity;
};

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





