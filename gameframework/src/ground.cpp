#include "ground.h"

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

//Type de murs
enum orientation{
    GROUND_UP,
    GROUND_DOWN,
    GROUND_LEFT,
    GROUND_RIGHT,
    CORNER_UP_RIGHT,
    CORNER_UP_LEFT,
    CORNER_DOWN_RIGHT,
    CORNER_DOWN_LEFT

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

ground::ground(QGraphicsItem* pParent) : Sprite(GameFramework::imagesPath() + "BasicPoseV4.png", pParent)
{

}



void ground::configureOrientation(orientation ground) {

    clearAnimations();
    int idSprite1 = 0;
    switch (ground) {
    case GROUND_UP:
        idSprite1 = 0;
        break;
    case GROUND_DOWN:
        idSprite1 = 2;
        break;
    case GROUND_LEFT:
        idSprite1 = 3;
        break;
    case GROUND_RIGHT:
        idSprite1 = 3;
        break;
    case CORNER_UP_RIGHT:
        idSprite1 = 3;
        break;
    case CORNER_UP_RIGHT:
        idSprite1 = 3;
        break;
    case CORNER_UP_RIGHT:
        idSprite1 = 3;
        break;
    default:
        idSprite1 = 4;
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




}
