/**
  Fichier qui contient toute la logique du jeu.

  @author   Léo Küttel
  @date     Novembre 2021
 */
#include "gamecore.h"

#include <cmath>

#include <QDebug>
#include <QSettings>

#include "gamescene.h"
#include "gamecanvas.h"
#include "resources.h"
#include "utilities.h"
#include "playertickhandler.h"
#include "sprite.h"
#include "time.h"
#include "QPainterPath"
#include <QGraphicsView>

//Ajoute Supp
#include <QString>
#include "ground.h"

//résolution de la fenetre
const int SCENE_WIDTH   = 6000;
const int SCENE_HEIGHT  = 4000;

const int PLAYER_SPEED  = 10 ;     // Vitesse de déplacement du joueur en pixels/s
const int PLAYER_JUMP   = -10 ;    // Vitesse du saute
const int PLAYER_STOP   = 0;       // Arrete le joueur

//dimenssion de découpage des spriteSheets du fantome.
const int FRAME_SIZE_GHOST   = 60;   //  Dimenssion de la frame
const int FRAME_COUNT_GHOST  = 7;    //  Nombres de frame à découper
const int COLUMN_COUNT_GHOST = 3;    //  Nombres de colonne


//Dimenssion de découpage des spriteSheets du sol.
const int FRAME_SIZE_GROUND   = 120;    //  Dimenssion de la frame
const int FRAME_COUNT_GROUND  = 9;      //  Nombres de frame à découper
const int COLUMN_COUNT_GROUND = 3;      //  Nombres de colonne


//Type de sol
enum orientation{
    GROUND_UP = 0,
    GROUND_DOWN = 1,
    GROUND_LEFT = 2,
    GROUND_RIGHT = 3,
    CORNER_UP_RIGHT = 4,
    CORNER_UP_LEFT = 5,
    CORNER_DOWN_RIGHT = 6,
    CORNER_DOWN_LEFT = 7,
    GROUND_OF_GROUND = 8

};

/**
 * Découpage des images pour les différentes orientations du sol.
 * @brief GameCore::setGroundImages
 */
void GameCore::setGroundImages(){
    QImage spriteSheet(GameFramework::imagesPath() +  "EveryGroundsV1.png");

    // Découpage de la spritesheet
    for (int frameIndex = 0; frameIndex <= FRAME_COUNT_GROUND; frameIndex++) {

        QImage CurrentGroundImage = spriteSheet.copy((frameIndex % COLUMN_COUNT_GROUND) * FRAME_SIZE_GROUND,
                                                     (frameIndex / COLUMN_COUNT_GROUND) * FRAME_SIZE_GROUND,
                                                     FRAME_SIZE_GROUND, FRAME_SIZE_GROUND);
        this->m_groundImagesList.append(CurrentGroundImage);
    }
}

//! Initialise le contrôleur de jeu.
//! \param pGameCanvas  GameCanvas pour lequel cet objet travaille.
//! \param pParent      Pointeur sur le parent (afin d'obtenir une destruction automatique de cet objet).
GameCore::GameCore(GameCanvas* pGameCanvas, QObject* pParent) : QObject(pParent) {

    // Mémorise l'accès au canvas (qui gère le tick et l'affichage d'une scène)
    m_pGameCanvas = pGameCanvas;

    // Créé la scène de base et indique au canvas qu'il faut l'afficher.
    m_pScene = pGameCanvas->createScene(0, 0, SCENE_WIDTH, SCENE_HEIGHT / GameFramework::screenRatio());
    pGameCanvas->setCurrentScene(m_pScene);

    // Trace un rectangle blanc tout autour des limites de la scène.
    m_pScene->addRect(m_pScene->sceneRect(), QPen(Qt::white));

    //Initialisation de la liste groundImagesList
    setGroundImages();

    // Instancier et initialiser les sprite ici :

    ///////////////////////////
    ////        SOL        ////
    ///////////////////////////
    QPointF posSolGroup1_1erEtage(0,750);
    generatorGround(40,3,posSolGroup1_1erEtage);

    QPointF posSolGroup2_1erEtage(5280,750);
    generatorGround(6,3,posSolGroup2_1erEtage);

    QPointF posSolGroup1(0,1600);
    generatorGround(8,6,posSolGroup1);

    QPointF posSolGroup2(2200,1460);
    generatorGround(8,5,posSolGroup2);

    QPointF posSolGroup3(3960,1460);
    generatorGround(2,9,posSolGroup3);

    QPointF posSolGroup4(4460,1660);
    generatorGround(2,9,posSolGroup4);

    //////////////////////////////////
    ////        PLATEFORME        ////
    //////////////////////////////////
    Sprite* platM1 = new Sprite(GameFramework::imagesPath() + "PlatformeMoyenneV2.png");
    platM1->setData(1,"sol");
    platM1->setData(2,"plateforme");
    m_pScene->addSpriteToScene(platM1, 1200,1600);

    Sprite* platM2 = new Sprite(GameFramework::imagesPath() + "PlatformeMoyenneV2.png");
    platM2->setData(1,"sol");
    platM2->setData(2,"plateforme");
    m_pScene->addSpriteToScene(platM2, 1500,1730);

    Sprite* platM3 = new Sprite(GameFramework::imagesPath() + "PlatformeMoyenneV2.png");
    platM3->setData(1,"sol");
    platM3->setData(2,"plateforme");
    m_pScene->addSpriteToScene(platM3, 1800,1600);

    Sprite* platM4 = new Sprite(GameFramework::imagesPath() + "PlatformeMoyenneV2.png");
    platM4->setData(1,"sol");
    platM4->setData(2,"plateforme");
    m_pScene->addSpriteToScene(platM4, 3700,1320);

    Sprite* platM5 = new Sprite(GameFramework::imagesPath() + "PlatformeMoyenneV2.png");
    platM5->setData(1,"sol");
    platM5->setData(2,"plateforme");
    m_pScene->addSpriteToScene(platM5, 4800,1085);

    //////////////////////////////
    ////        CAISSE        ////
    //////////////////////////////
    Sprite* CaisseW1 = new Sprite(GameFramework::imagesPath() + "CaisseV2.png");
    CaisseW1->setData(1,"sol");
    CaisseW1->setData(2,"Wood_caisse");
    m_pScene->addSpriteToScene(CaisseW1, 500,1520);

    Sprite* CaisseW2 = new Sprite(GameFramework::imagesPath() + "CaisseV2.png");
    CaisseW2->setData(1,"sol");
    CaisseW2->setData(2,"Wood_caisse");
    m_pScene->addSpriteToScene(CaisseW2, 2900,1380);

    Sprite* caisseM1 = new Sprite(GameFramework::imagesPath() + "CaisseMetalV2.png");
    caisseM1->setData(1,"sol");
    caisseM1->setData(2,"Wood_caisse");
    m_pScene->addSpriteToScene(caisseM1, 700,1520);

    /////////////////////////////
    ////        PIEGE        ////
    /////////////////////////////
    Sprite* lanceF1 = new Sprite(GameFramework::imagesPath() + "lanceFlammeV3.png");
    lanceF1->setData(1,"Piege");
    lanceF1->setData(2,"Lance_flamme");
    m_pScene->addSpriteToScene(lanceF1, 800,1510);

    Sprite* lanceF2 = new Sprite(GameFramework::imagesPath() + "lanceFlammeV3.png");
    lanceF2->setData(1,"Piege");
    lanceF2->setData(2,"Lance_flamme");
    m_pScene->addSpriteToScene(lanceF2, 2400,1370);

    Sprite* lanceF3 = new Sprite(GameFramework::imagesPath() + "lanceFlammeV3.png");
    lanceF3->setData(1,"Piege");
    lanceF3->setData(2,"Lance_flamme");
    m_pScene->addSpriteToScene(lanceF3, 4580,1570);

    //Ajoute du joueur dans la scene
    m_pScene->addSpriteToScene(pCharacter, 300,1200);
    pCharacter->startAnimation(25);

    // ...
    // Démarre le tick pour que les animations qui en dépendent fonctionnent correctement.
    // Attention : il est important que l'enclenchement du tick soit fait vers la fin de cette fonction,
    // sinon le temps passé jusqu'au premier tick (ElapsedTime) peut être élevé et provoquer de gros
    // déplacements, surtout si le déboggueur est démarré.
    m_pGameCanvas->startTick();
}

//! Destructeur de GameCore : efface les scènes
GameCore::~GameCore() {
    delete m_pScene;
    m_pScene = nullptr;
}



//! Traite la pression d'une touche.
//! \param key Numéro de la touche (voir les constantes Qt)
//!
void GameCore::keyPressed(int key) {
    emit notifyKeyPressed(key);

    if(!pCharacter->getIsDeath()){
        Character::animation player;

        switch(key) {
        case Qt::Key_W:
            player = Character::SAUT;
            pCharacter->m_velocity.setY(PLAYER_JUMP);
            pCharacter->setIsJump(true);
            break;

        case Qt::Key_A:
            pCharacter->m_velocity.setX(-PLAYER_SPEED);
            player = Character::DEPLA_GAUCHE;
            break;

        case Qt::Key_D:
            pCharacter->m_velocity.setX(PLAYER_SPEED);
            player = Character::DEPLA_DROITE;
            break;

        case Qt::Key_Space:
            if(pCharacter->getIsOnFloor()){
                player = Character::SAUT;
                pCharacter->m_velocity.setY(PLAYER_JUMP);
                pCharacter->setIsJump(true);
                qDebug() << "isJump : " << pCharacter->getIsJump();
            }else{
                player = Character::BASE;
            }
            break;

        default:
            player = Character::BASE;
        }
        pCharacter->configureAnimation(player);
    }

    if(key == Qt::Key_Space && pCharacter->getIsDeath()){
        pCharacter->respawn();
        m_pScene->removeSpriteFromScene(pGhost);
        m_pScene->addSpriteToScene(pCharacter, 300,1200);
        pCharacter->startAnimation(25);
    }
}

//! Traite le relâchement d'une touche.
//! \param key Numéro de la touche (voir les constantes Qt)
void GameCore::keyReleased(int key) {
    emit notifyKeyReleased(key);
    if(!pCharacter->getIsDeath()){
        switch(key) {
        case Qt::Key_A:
            pCharacter->m_velocity.setX(PLAYER_STOP);
            pCharacter->m_lastVelocity.setX(-PLAYER_SPEED);
            break;

        case Qt::Key_D:
            pCharacter->m_velocity.setX(PLAYER_STOP);
            pCharacter->m_lastVelocity.setX(PLAYER_SPEED);
            break;

        case Qt::Key_Space:
            pCharacter->m_velocity.setY(PLAYER_STOP);
            pCharacter->setIsJump(false);
            break;
        }
        //if(!isOnFloor)
        //pCharacter->configureAnimation(Character::SAUT);
        //else {
        pCharacter->configureAnimation(Character::BASE);
        //}
    }
}

//! Cadence.
//! éplace le joueur en fonction de la touche préssé.
//! \param elapsedTimeInMilliseconds  Temps écoulé depuis le dernier appel.
void GameCore::tick(long long elapsedTimeInMilliseconds) {

    if(!pCharacter->getIsDeath()){
        pCharacter->setPos(pCharacter->pos()+ pCharacter->m_velocity);
        //Suite les déplacement du joueur dans la scene
        m_pGameCanvas->getView()->centerOn(m_pScene->sprites().takeAt(0)->pos());
    }else {
        pGhost->setY(pGhost->y() -5);
    }

    // Récupère tous les sprites de la scène qui touche le joueur
    auto listeCurrentCollision = pCharacter->parentScene()->collidingSprites(pCharacter);
    // Supprimer le sprite lui-même
    listeCurrentCollision.removeAll(pCharacter);

    //récupère la valeur de liste (remplis/vide)
    bool currentCollision  = !listeCurrentCollision.isEmpty();

    if(currentCollision){
        //Cherche les collisions entre le joueurs les autres sprites
        for (Sprite* CollisionDetected : listeCurrentCollision) {

            if(CollisionDetected->data(2) == "Wood_caisse"){

                //Zone de collision entre le joueur et la caisse en bois
                QRectF zoneDeCollision = pCharacter->boundingRect().intersected(CollisionDetected->boundingRect());
                qDebug() << "height collision :" << zoneDeCollision.height();
                qDebug() << "width collision :" << zoneDeCollision.width();


                if(zoneDeCollision.height() > zoneDeCollision.width()){

                    qDebug() << "height collision :" << CollisionDetected->boundingRect().intersected(pCharacter->boundingRect()).height();
                    qDebug() << "width collision :" << CollisionDetected->boundingRect().intersected(pCharacter->boundingRect()).width();

                    CollisionDetected->setX(CollisionDetected->x() + pCharacter->m_velocity.x());
                    pCharacter->m_velocity.setX(!pCharacter->m_velocity.x());
                    qDebug() << "POUSSE";
                }

            }
        }
    }

    // Détermine la prochaine position du sprite selon sa velwocité
    QRectF nextSpriteRect = pCharacter->globalBoundingBox().translated(pCharacter->m_velocity);

    // Récupère tous les sprites de la scène que toucherait ce sprite à sa prochaine position
    auto listeFuturCollision = pCharacter->parentScene()->collidingSprites(nextSpriteRect);
    // Supprime le sprite lui-même, qui collisionne toujours awdvec sa boundingbox
    listeFuturCollision.removeAll(pCharacter);

    //récupère la valeur de liste (remplis/vide)
    bool futurCollision = !listeFuturCollision.isEmpty();

    if(futurCollision){
        //Cherche de potentielle futur collisions entre le joueur et les autres sprites
        for (Sprite* CollisionDetected : listeFuturCollision) {
            if (CollisionDetected->data(1) == "sol") {

                if(!pCharacter->getIsJump())
                    pCharacter->setIsOnFloor(true);

                pCharacter->m_velocity.setY(0.0);
                pCharacter->setIsJump(false);
            }else{
                pCharacter->setIsOnFloor(false);
            }

            if (CollisionDetected->data(1) == "Piege") {

                if(!pCharacter->getIsDeath()){
                    //qDebug() << "HO NON UN PIEGE AHHHH";
                    m_pGameCanvas->getView()->centerOn(CollisionDetected->pos());
                    setupCharacterDeath();
                }
                pCharacter->setIsDeath(true);
            }
        }
    }else {
        pCharacter->setIsOnFloor(false);
    }

    //Si le joueur ne touche pas le sol alors il est attiré vers le bas
    if (!pCharacter->getIsOnFloor()){
        //qDebug() << "PAS SUR LE SOL";

        pCharacter->setPos(pCharacter->pos() + pCharacter->m_velocity * (elapsedTimeInMilliseconds/100.0));
        pCharacter->m_velocity+= gravity * (elapsedTimeInMilliseconds/100.0);

        /*
        for (int i;i <= m_pScene->sprites().count();i++) {
            m_pScene->sprites().takeAt(i)->pos();
            if(){
                m_pScene->sprites().takeAt(i)->setPos(m_pScene->sprites().takeAt(i)->pos() + m_pScene->sprites().takeAt(i)-> * (elapsedTimeInMilliseconds/100.0));
                        pCharacter->m_velocity+= gravity * (elapsedTimeInMilliseconds/100.0);
            }
        }

        */

    }

    if((pCharacter->x() >= m_pScene->width() /*|| pCharacter->x() <= m_pScene->width()*/
        || pCharacter->y() >= m_pScene->height() /*|| pCharacter->y() <= m_pScene->height()*/) && !pCharacter->getIsDeath()){
     setupCharacterDeath();
    }
}

/**
 * @brief GameCore::configureOrientation
 * @param orientation du sol à selectionnée dans la liste
 * @param ground sprite à appliqué la texture
 */
void GameCore::configureOrientation(orientation orientation, Sprite* &ground) {
    //Selectionne le sol demandé
    ground = new Sprite(QPixmap::fromImage(m_groundImagesList.at(orientation).scaled(FRAME_SIZE_GROUND * 1,
                                                                                     FRAME_SIZE_GROUND * 1,
                                                                                     Qt::IgnoreAspectRatio,
                                                                                     Qt::SmoothTransformation)));
}

/**
 * @brief GameCore::generatorGround génére un groupe de sol sur la map d'un niveau
 * @param colonne nbr de colonne dans le bloque de de sol
 * @param ligne nbr de colonne dans le bloque de de sol
 * @param max nbr max de sol à généré
 */
void GameCore::generatorGround(int colonneMax,int ligneMax,QPointF posGroupe){

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
void GameCore::setAnimationDeath()
{
    QImage spriteSheet(GameFramework::imagesPath() +  "deathAnimationV1.png");

    QList<QImage> deathFrameList;
    // Découpage de la spritesheet
    for (int frameIndex = 0; frameIndex <= FRAME_COUNT_GHOST; frameIndex++) {

        QImage CurrentFrameImage = spriteSheet.copy((frameIndex % COLUMN_COUNT_GHOST) * FRAME_SIZE_GHOST,
                                                    (frameIndex / COLUMN_COUNT_GHOST) * FRAME_SIZE_GHOST,
                                                    FRAME_SIZE_GHOST, FRAME_SIZE_GHOST);
        if(frameIndex == 0){
            pGhost = new Sprite(QPixmap::fromImage(CurrentFrameImage.scaled(FRAME_SIZE_GHOST * 1.5,
                                                                            FRAME_SIZE_GHOST * 1.5,
                                                                            Qt::IgnoreAspectRatio,
                                                                            Qt::SmoothTransformation)));
        }else{
            pGhost->addAnimationFrame(QPixmap::fromImage(CurrentFrameImage.scaled(FRAME_SIZE_GHOST * 1.5,
                                                                                  FRAME_SIZE_GHOST * 1.5,
                                                                                  Qt::IgnoreAspectRatio,
                                                                                  Qt::SmoothTransformation)));
        }
    }
    pGhost->startAnimation(50);
}

void GameCore::setupCharacterDeath(){

    setAnimationDeath();
    pGhost->setPos(pCharacter->pos());

    m_pScene->addSpriteToScene(pGhost);
    m_pScene->removeSpriteFromScene(pCharacter);

    m_deathCount += 1;
    qDebug() << "Nbr de mort(s) : " << m_deathCount;

}

//! La souris a été déplacée.
//! Pour que cet événement soit pris en compte, la propriété MouseTracking de GameView
//! doit être enclenchée avec GameCanvas::startMouseTracking().
void GameCore::mouseMoved(QPointF newMousePosition) {
    emit notifyMouseMoved(newMousePosition);
}

//! Traite l'appui sur un bouton de la souris.
void GameCore::mouseButtonPressed(QPointF mousePosition, Qt::MouseButtons buttons) {
    emit notifyMouseButtonPressed(mousePosition, buttons);
}

//! Traite le relâchement d'un bouton de la souris.
void GameCore::mouseButtonReleased(QPointF mousePosition, Qt::MouseButtons buttons) {
    emit notifyMouseButtonReleased(mousePosition, buttons);
}




