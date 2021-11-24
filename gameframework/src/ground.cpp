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
    CORNER_DOWN_LEFT,
    GROUND_OF_GROUND

};

//spriteSheet animation de marche à gauche
const int FRAME_WIDTH = 120;
const int FRAME_HEIGHT = 120;
const int FRAME_COUNT = 9;
const int COLUMN_COUNT = 3;

Ground::Ground(QGraphicsItem* pParent) : Sprite(GameFramework::imagesPath() + "EveryGroundsV1.png", pParent)
{

}



void Ground::configureOrientation(orientation ground) {
    int sheetID = 0;
    switch (ground) {
    case GROUND_UP:
        sheetID = 0;
        break;
    case GROUND_DOWN:
        sheetID = 1;
        break;
    case GROUND_LEFT:
        sheetID = 2;
        break;
    case GROUND_RIGHT:
        sheetID = 3;
        break;
    case CORNER_UP_RIGHT:
        sheetID = 4;
        break;
    case CORNER_UP_LEFT:
        sheetID = 5;
        break;
    case CORNER_DOWN_RIGHT:
        sheetID = 6;
        break;
    case CORNER_DOWN_LEFT:
        sheetID = 7;
        break;
    case GROUND_OF_GROUND:
        sheetID = 8;
        break;
    default:
        sheetID = 0;
        break;
    }


    qDebug() << "sheetID : " << sheetID;
    QImage spriteSheet(GameFramework::imagesPath() +  "EveryGroundsV1.png");

    // Découpage de la spritesheet
    for (int frameIndex = 0; frameIndex <= FRAME_COUNT; frameIndex++) {

        if(frameIndex == sheetID ){
            QImage sprite = spriteSheet.copy((frameIndex % COLUMN_COUNT) * FRAME_WIDTH,
                                             (frameIndex / COLUMN_COUNT) * FRAME_HEIGHT,
                                             FRAME_WIDTH, FRAME_HEIGHT);

            addAnimationFrame(QPixmap::fromImage(sprite.scaled(FRAME_WIDTH * 1,
                                                               FRAME_HEIGHT * 1,
                                                               Qt::IgnoreAspectRatio,
                                                               Qt::SmoothTransformation)));

        }

    }
    startAnimation(1000);
    setActiveAnimation(0);

}

