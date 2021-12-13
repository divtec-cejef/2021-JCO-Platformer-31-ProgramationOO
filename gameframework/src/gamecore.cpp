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
#include "bulio.h"

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

    // Inistilisation de la scene dans m_Grounds.
    m_Grounds->setScene(m_pScene);

    // Instancier et initialiser les sprite ici :

    ///////////////////////////
    ////        SOL        ////
    ///////////////////////////
    QPointF posSolGroup1_1erEtage(0,750);
    m_Grounds->generated(40,3,posSolGroup1_1erEtage);

    QPointF posSolGroup2_1erEtage(5280,750);
    m_Grounds->generated(6,3,posSolGroup2_1erEtage);

    QPointF posSolGroup1(0,1600);
    m_Grounds->generated(8,6,posSolGroup1);

    QPointF posSolGroup2(2200,1460);
    m_Grounds->generated(8,5,posSolGroup2);

    QPointF posSolGroup3(3960,1460);
    m_Grounds->generated(2,9,posSolGroup3);

    QPointF posSolGroup4(4460,1660);
    m_Grounds->generated(2,9,posSolGroup4);

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


    //////////////////////////////
    ////        ENEMIE        ////
    //////////////////////////////
    Bulio* enemie1 = new Bulio();
    enemie1->setData(1,"enemie");
    enemie1->setData(2,"bulio");
    m_pScene->addSpriteToScene(enemie1, 2500,1410);

    //Ajoute du joueur dans la scene
    pCharacter->setData(1,"joueur");
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
            player = Character::DEPLACEMENT;
            break;

        case Qt::Key_D:
            pCharacter->m_velocity.setX(PLAYER_SPEED);
            player = Character::DEPLACEMENT;
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
//! Déplace le joueur en fonction de la touche préssé.
//! \param elapsedTimeInMilliseconds  Temps écoulé depuis le dernier appel.
void GameCore::tick(long long elapsedTimeInMilliseconds) {

    if(!pCharacter->getIsDeath()){
        pCharacter->setPos(pCharacter->pos()+ pCharacter->m_velocity);
        //Suite les déplacement du joueur dans la scene
        m_pGameCanvas->getView()->centerOn(m_pScene->sprites().takeAt(0)->pos());

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
                    //pCharacter->boundingRect().intersected(CollisionDetected->boundingRect());
                    QRectF zoneDeCollision = pCharacter->boundingRect().intersected(CollisionDetected->boundingRect());
                    //qDebug() << "Y collision :" << zoneDeCollision.y();
                    //qDebug() << "X collision :" << zoneDeCollision.x();


                    if(zoneDeCollision.height() > zoneDeCollision.width()){

                        CollisionDetected->setX(CollisionDetected->x() + pCharacter->m_velocity.x());
                        //pCharacter->m_velocity.setX(!pCharacter->m_velocity.x());
                        qDebug() << "POUSSE";
                    }
                }
            }
        }

        // Détermine la prochaine position du sprite selon sa velwocité
        QRectF nextSpriteRect = pCharacter->globalBoundingBox().translated(pCharacter->m_velocity);

        if(!pCharacter->parentScene()->isInsideScene(nextSpriteRect)){
            qDebug() << "Le joueur est sortit de la scene";
            setupCharacterDeath();
        }

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

                    QRectF zoneDeCollision = pCharacter->boundingRect().intersected(CollisionDetected->boundingRect());
                    qDebug() << "Y collision :" << zoneDeCollision.y();
                    qDebug() << "X collision :" << zoneDeCollision.x();

                    if(zoneDeCollision.height() < zoneDeCollision.width()){
                        qDebug() << "Collision de haut/bas";
                    }else if(zoneDeCollision.height() > zoneDeCollision.width()){
                        qDebug() << "Collision de côté";
                    }
                }

                if (CollisionDetected->data(1) == "Piege") {

                    if(!pCharacter->getIsDeath()){
                        //qDebug() << "HO NON UN PIEGE AHHHH";
                        m_pGameCanvas->getView()->centerOn(CollisionDetected->pos());
                    }
                    setupCharacterDeath();
                }
            }
        }else {
            pCharacter->setIsOnFloor(false);
        }
        //Si le joueur ne touche pas le sol alors il est attiré vers le bas
        if (!pCharacter->getIsOnFloor()){
            //Attire le joueur vers le bas de l'écran
            gravityApplied(pCharacter,pCharacter->m_velocity,elapsedTimeInMilliseconds);
        }
    }else {
        pGhost->setY(pGhost->y() -5);
    }


}


//!
//! \brief GameCore::gravityApplied
//! \param entity sprite au quel on applique la gravité
//! \param enti_velocity velocité du sprite
//! \param elapsedTime temps écoulé entre chaque tick.
//!@brief GameCore::gravityApplied
void GameCore::gravityApplied(Entity* entity,QPointF &enti_velocity,long long elapsedTime){
    entity->setPos(entity->pos() + enti_velocity * (elapsedTime/100.0));
    enti_velocity += m_gravity * (elapsedTime/100.0);
}


//!
//! Créé un sprite pour symbolisé la mort du joueur.
//! @brief GameCore::setAnimationDeath
//!
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

//!
//! Mets en place tout les éléments symbolisant la mort du joueur.
//! @brief GameCore::setupCharacterDeath
//!
void GameCore::setupCharacterDeath(){
    //Le joueur est considéré comme mort.
    pCharacter->setIsDeath(true);
    //Créé le fantôme dans la scene.
    setAnimationDeath();
    //Positionne le fantôme à la place du joueur
    pGhost->setPos(pCharacter->pos());
    //Supprime le joueur de la scene.
    m_pScene->removeSpriteFromScene(pCharacter);
    //Ajoute du fantome à la scene.
    m_pScene->addSpriteToScene(pGhost);
    //Ajoute d'une mort au compteur.
    pCharacter->incrementDeathCount();
}


//!
//! \brief GameCore::currentCollision
//! \param entity entité dont on veut savoir avec quoi elle rentre en collision.
//! \param enti_velocity velocité de l'entité.
//!
void GameCore::currentCollision(Entity* entity){

}

void GameCore::futureCollision(Entity* entity){



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




