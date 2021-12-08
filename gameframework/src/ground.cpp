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

//Dimenssion de découpage des spriteSheets du sol.
const int FRAME_SIZE_GROUND   = 120;    //  Dimenssion de la frame
const int FRAME_COUNT_GROUND  = 9;      //  Nombres de frame à découper
const int COLUMN_COUNT_GROUND = 3;      //  Nombres de colonne

//!
//! Découpage des images pour les différentes orientations du sol.
//! @brief GameCore::setGroundImages
//!
void Ground::setGroundImages(){
    QImage spriteSheet(GameFramework::imagesPath() +  "EveryGroundsV1.png");

    // Découpage de la spritesheet
    for (int frameIndex = 0; frameIndex <= FRAME_COUNT_GROUND; frameIndex++) {

        QImage CurrentGroundImage = spriteSheet.copy((frameIndex % COLUMN_COUNT_GROUND) * FRAME_SIZE_GROUND,
                                                     (frameIndex / COLUMN_COUNT_GROUND) * FRAME_SIZE_GROUND,
                                                     FRAME_SIZE_GROUND, FRAME_SIZE_GROUND);
        this->m_groundImagesList.append(CurrentGroundImage);
    }
}

Ground::Ground(QGraphicsItem* pParent) : Sprite(GameFramework::imagesPath() + "EveryGroundsV1.png", pParent)
{

}
/*
//!
//! @brief GameCore::configureOrientation
//! @param orientation du sol à selectionnée dans la liste
//! @param ground sprite à appliqué la texture
//!
void Ground::configureOrientation(orientation orientation, Sprite* &ground) {
    //Selectionne le sol demandé
    ground = new Sprite(QPixmap::fromImage(m_groundImagesList.at(orientation).scaled(FRAME_SIZE_GROUND * 1,
                                                                                     FRAME_SIZE_GROUND * 1,
                                                                                     Qt::IgnoreAspectRatio,
                                                                                     Qt::SmoothTransformation)));
}

//!
//! @brief GameCore::generatorGround génére un groupe de sol sur la map d'un niveau
//! @param colonne nbr de colonne dans le bloque de de sol
//! @param ligne nbr de colonne dans le bloque de de sol
//! @param max nbr max de sol à généré
//!
void Ground::generatorGround(int colonneMax,int ligneMax,QPointF posGroupe){

    QPointF posCurrentGround = posGroupe;

    for(int currentLigne = 1; currentLigne <= ligneMax; currentLigne++ ) {
        qDebug() <<" ligne actu " << currentLigne;

        for(int currentColonne = 1; currentColonne <= colonneMax; currentColonne++){
            orientation orientGround = GROUND_OF_GROUND;

            Sprite* pCurrentGround = new Sprite();

            //Définit l'orientation du morceau de sol
            if(currentLigne == 1){
                orientGround = GROUND_UP;

                if(currentColonne == 1){
                    //Definit le coin du haut à gauche
                    orientGround = CORNER_UP_LEFT;
                }else if (currentColonne == colonneMax) {
                    //Definit le coin du haut à droite
                    orientGround = CORNER_UP_RIGHT;
                }
            }else if(currentLigne == ligneMax){
                orientGround = GROUND_DOWN;

                if(currentColonne == 1){
                    //Definit le coin du bas à gauche
                    orientGround = CORNER_DOWN_LEFT;
                }else if (currentColonne == colonneMax) {
                    //Definit le coin du bas à droite
                    orientGround = CORNER_DOWN_RIGHT;
                }
            }else {
                if(currentColonne == 1){
                    //Définit le côté gauche de la ligne
                    orientGround = GROUND_LEFT;
                }else if (currentColonne == colonneMax) {
                    //Définit le côté gauche de la ligne
                    orientGround = GROUND_RIGHT;
                }
            }

            //Mise en place du sol dans la scène
            configureOrientation(orientGround,pCurrentGround);
            pCurrentGround->setPos(posCurrentGround);
            pCurrentGround->setData(1,"sol");
            pCurrentGround->setData(2,"soltest");
            m_pScene->addSpriteToScene(pCurrentGround);

            //Changement de colonne
            posCurrentGround.setX(posCurrentGround.x() + FRAME_SIZE_GROUND);
        }
        //Change de ligne
        posCurrentGround.setX(posGroupe.x());
        posCurrentGround.setY(posCurrentGround.y()+FRAME_SIZE_GROUND);
    }
}
}*/

