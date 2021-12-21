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
    // m_pScene->addSpriteToScene(enemie1, 2500,1410);
    m_pScene->addSpriteToScene(enemie1, 500,1200);

    //Ajoute du joueur dans la scene
    pCharacter->setData(1,"joueur");
    m_pScene->addSpriteToScene(pCharacter, 300,1200);
    pCharacter->startAnimation(25);

    m_pBulioList.append(enemie1);

    // ...
    // Démarre le tick pour que les animations qui en dépendent fonctionnent correctement.
    // Attention : il est important que l'enclenchement du tick soit fait vers la fin de cette fonction,
    // sinon le temps passé jusqu'au premier tick (ElapsedTime) peut être élevé et provoquer de gros
    // déplacements, surtout si le déboggueur est démarré.
    m_pGameCanvas->startTick(10);
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
        m_pGameCanvas->getView()->centerOn(m_pScene->sprites().at(0)->pos());

        QRectF nextSpriteRect = pCharacter->globalBoundingBox().translated(pCharacter->m_velocity);
        QList<Entity::hitSide> collidingSides = QList<Entity::hitSide>();

        // Récupère tous les sprites de la scène qui touche le joueur
        auto listeCurrentCollisionCharacter = pCharacter->parentScene()->collidingSprites(pCharacter);
        // Supprimer le sprite lui-même
        listeCurrentCollisionCharacter.removeAll(pCharacter);

        //récupère la valeur de liste (remplis/vide)
        bool currentCollision  = !listeCurrentCollisionCharacter.isEmpty();

        if(currentCollision){
            //Cherche les collisions entre le joueurs les autres sprites
            for (Sprite* CollisionDetected : listeCurrentCollisionCharacter) {
                QRectF intersected = nextSpriteRect.intersected(CollisionDetected->globalBoundingBox());

                getCollisionLocate(collidingSides,nextSpriteRect,intersected);

                if (CollisionDetected->data(1) == "sol") {

                    for (int i =0;i < collidingSides.count();i++) {
                        switch (collidingSides.at(i)) {
                        case Entity::hitSide::DOWN:
                            pCharacter->m_velocity.setY(0.0);
                            if(!pCharacter->getIsJump())
                                pCharacter->setIsOnFloor(true);

                            pCharacter->m_velocity.setY(0.0);
                            pCharacter->setIsJump(false);
                            //this->setIsJump(false);
                            break;
                        case  Entity::hitSide::UP:
                            pCharacter->m_velocity.setY(2);
                            break;
                        case Entity::hitSide::RIGHT :
                            pCharacter->m_velocity.setX(0);
                            break;
                        case Entity::hitSide::LEFT :
                            pCharacter->m_velocity.setX(0);
                            break;
                        }
                    }
                }
                if (CollisionDetected->data(1) == "enemie") {

                    for (int i =0;i < collidingSides.count();i++) {

                        switch (collidingSides.at(i)) {
                        case Entity::hitSide::DOWN:
                            m_pScene->removeSpriteFromScene(CollisionDetected);
                            //this->setIsJump(false);
                            break;
                        case  Entity::hitSide::UP:
                            setupCharacterDeath();
                            break;
                        case Entity::hitSide::RIGHT :
                            setupCharacterDeath();
                            break;
                        case Entity::hitSide::LEFT :
                            setupCharacterDeath();
                            break;
                        }
                    }
                }
                if (CollisionDetected->data(1) == "Piege") {

                    if(!pCharacter->getIsDeath()){
                        //qDebug() << "HO NON UN PIEGE AHHHH";
                        m_pGameCanvas->getView()->centerOn(CollisionDetected->pos());
                    }
                    setupCharacterDeath();
                }

                if (CollisionDetected->data(1) == "Wood_caisse") {

                    for (int i =0;i < collidingSides.length();i++) {

                        switch (collidingSides.at(i)) {
                        case Entity::hitSide::DOWN:
                            pCharacter->m_velocity.setY(0.0);
                            if(!pCharacter->getIsJump())
                                pCharacter->setIsOnFloor(true);

                            pCharacter->setIsJump(false);
                            //this->setIsJump(false);
                            break;
                        case  Entity::hitSide::UP:
                            pCharacter->m_velocity.setY(0.0);
                            break;
                        case Entity::hitSide::RIGHT :

                            CollisionDetected->setX(CollisionDetected->x() + pCharacter->m_velocity.x());
                            pCharacter->m_velocity.setX(5);
                            break;
                        case Entity::hitSide::LEFT :

                            CollisionDetected->setX(CollisionDetected->x() + pCharacter->m_velocity.x());
                            pCharacter->m_velocity.setX(-5);
                            break;
                        }
                    }
                }
            }
        }else {
            pCharacter->setIsOnFloor(false);
        }
        if(!pCharacter->parentScene()->isInsideScene(nextSpriteRect)){
            qDebug() << "Le joueur est sortit de la scene";
            setupCharacterDeath();
        }
    }else {
        pGhost->setY(pGhost->y() -5);
    }

    for (int i = 0;i < m_pBulioList.length();i++) {
        //qDebug() << "Bulio" << i;
        //Bulio* CurrentBulio = m_pBulioList.takeAt(i);
        // qDebug() << "Current Bulio : " << i;
        // qDebug() << "Nbr de Bulio : " << m_pBulioList.count();
        QRectF nextSpriteRect = m_pBulioList.at(i)->globalBoundingBox().translated(m_pBulioList.at(i)->pos());
        QList<Entity::hitSide> collidingSides = QList<Entity::hitSide>();

        // Récupère tous les sprites de la scène qui touche le joueur
        auto listeCurrentCollisionBulio = m_pBulioList.at(i)->parentScene()->collidingSprites(m_pBulioList.at(i));
        //pCharacter->parentScene()->collidingSprites(pCharacter)
        //qDebug() << "listeCurrentCollisionBulio ajouté";

        // Supprimer le sprite lui-même
        listeCurrentCollisionBulio.removeAll(m_pBulioList.at(i));

        //récupère la valeur de liste (remplis/vide)
        bool currentCollision  = !listeCurrentCollisionBulio.isEmpty();
        qDebug() << "currentCollision" << currentCollision;
        if(currentCollision){
            //Cherche les collisions entre le joueurs les autres sprites

            for (Sprite* CollisionDetected : listeCurrentCollisionBulio) {

                QRectF intersected = nextSpriteRect.intersected(CollisionDetected->globalBoundingBox());
                getCollisionLocate(collidingSides,nextSpriteRect,intersected);

                if (CollisionDetected->data(1) == "sol") {
                    for (int i =0;i < collidingSides.length();i++) {
                        switch (collidingSides.at(i)) {
                        case Entity::hitSide::DOWN:
                            m_pBulioList.at(i)->m_velocity.setY(0.0);
                            m_pBulioList.at(i)->setIsOnFloor(true);

                            m_pBulioList.at(i)->m_velocity.setY(0.0);
                            qDebug() << "touche le sool";

                            break;
                        case  Entity::hitSide::UP:
                            m_pBulioList.at(i)->m_velocity.setY(0.0);
                            break;
                        case Entity::hitSide::RIGHT :
                            m_pBulioList.at(i)->m_velocity.setX(-5);
                            break;
                        case Entity::hitSide::LEFT :
                            m_pBulioList.at(i)->m_velocity.setX(5);
                            break;
                        }
                    }
                }
            }
            //m_pBulioList.at(i)->setY(0);
            //m_pBulioList.at(i)->setIsOnFloor(true);

        }else {
            m_pBulioList.at(i)->setIsOnFloor(false);
        }

        //Attire le bulio vers le bas de l'écran
        gravityApplied(m_pBulioList.at(i),m_pBulioList.at(i)->m_velocity,elapsedTimeInMilliseconds);
        //Déplace le bulio
        m_pBulioList.at(i)->setPos(m_pBulioList.at(i)->pos()+ m_pBulioList.at(i)->m_velocity);

        //}
    }
    //Attire le joueur vers le bas de l'écran
    gravityApplied(pCharacter,pCharacter->m_velocity,elapsedTimeInMilliseconds);
}

//! Ajoute à une liste la localisation des collision entre deux sprite.
//! \brief GameCore::getCollisonLocate
//! \param collisionLocateList
//! \param posSprite Position du Sprite principal.
//! \param intersected zone de collision entre les deux sprites.
//!
void GameCore::getCollisionLocate(QList<Entity::hitSide>&collisionLocateList,
                                  QRectF posSprite,QRectF intersected){

    //Si l'intersected est plus large la collision est vertical.
    if (intersected.width() > intersected.height() && intersected.width() > 10) {
        if (intersected.center().y() < posSprite.center().y())
            //Détermine le haut
            Entity::uniqueSide(&collisionLocateList, Entity::hitSide::UP);
        else
            //Détermine le bas
            Entity::uniqueSide(&collisionLocateList, Entity::hitSide::DOWN);

        //Sinon si la collision est plus haut que large est horizontal.
    } else if (intersected.width() < intersected.height() && intersected.height() > 10){
        if (intersected.center().x() < posSprite.center().x())
            //Détermine la gauche
            Entity::uniqueSide(&collisionLocateList, Entity::hitSide::LEFT);
        else
            //Détermine la droite
            Entity::uniqueSide(&collisionLocateList, Entity::hitSide::RIGHT);
    }

}

//!
//! \brief GameCore::gravityApplied
//! \param entity sprite au quel on applique la gravité
//! \param enti_velocity velocité du sprite
//! \param elapsedTime temps écoulé entre chaque tick.
//!@brief GameCore::gravityApplied
void GameCore::gravityApplied(Entity* entity,QPointF &enti_velocity,long long elapsedTime){

    if (!entity->getIsOnFloor()){
        //Attire le joueur vers le bas de l'écran
        entity->setPos(entity->pos() + enti_velocity * (elapsedTime/100.0));
        enti_velocity += m_gravity * (elapsedTime/100.0);
    }
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




