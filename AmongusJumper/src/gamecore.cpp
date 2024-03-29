﻿/**
  Fichier qui contient toute la logique du jeu.

  @author   Léo Küttel
  @date     Janvier 2022
 */
#include "gamecore.h"

#include <cmath>

#include <QDebug>
#include <QSettings>
#include "QPainterPath"
#include <QGraphicsView>
#include <QRadialGradient>

#include "gamescene.h"
#include "gamecanvas.h"
#include "resources.h"
#include "utilities.h"

#include "sprite.h"

#include "ground.h"
#include <string>
#include "bulio.h"
#include <buliotickhandler.h>

#include "caisseamovible.h"
#include "caisseamovtickhandler.h"

/// résolution de la fenetre
///  \ref SCENE_WIDTH largeur
///  \ref SCENE_HEIGHT longueur
const int SCENE_WIDTH   = 8000;
const int SCENE_HEIGHT  = 4000;


const int PLAYER_SPEED  = 9 ;     // Vitesse de déplacement du joueur en pixels/s
const int PLAYER_JUMP   = -9 ;    // Vitesse du saute
const int PLAYER_STOP   = 0;      // Arrete le joueur

const int GHOST_SPEED  = -10 ;      //Vitesse de vol

//dimenssion de découpage des spriteSheets du fantome.
const int FRAME_SIZE_GHOST   = 60;   //  Dimenssion de la frame
const int FRAME_COUNT_GHOST  = 7;    //  Nombres de frame à découper
const int COLUMN_COUNT_GHOST = 3;    //  Nombres de colonne

//dimenssion de découpage des spriteSheets du bouton.
const int FRAME_ENDING_BUTON_WIDTH   = 176;  //  Largeur de la frame
const int FRAME_ENDING_BUTON_HEIGHT   = 192; //  Hauteur de la frame
const int FRAME_COUNT_ENDING_BUTON = 1;     //  Nombres de frame à découper
const int COLUMN_COUNT_ENDING_BUTON = 1;    //  Nombres de colonne

//dimenssion de découpage des spriteSheets du bouton quand le joueur le touche.
const int FRAME_ENDING_BUTON_ACTIVE_WIDTH   = 88;  //  Largeur de la frame
const int FRAME_ENDING_BUTON_ACTIVE_HEIGT   = 192; //  Hauteur de la frame
const int FRAME_COUNT_ENDING_BUTON_ACTIVE = 10;     //  Nombres de frame à découper
const int COLUMN_COUNT_ENDING_BUTON_ACTIVE = 1;    //  Nombres de colonne

const int FIRST_LIGNE = 40; // premier plan de la scene.



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

    // Paramètrage de du niveau de test.
    loadTestLevel();

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

//! Génère le niveau de démo du jeu.
void GameCore::loadTestLevel(){

    //Création du filtre du premier plan
    QLinearGradient lGradient(QPointF(0,SCENE_HEIGHT / GameFramework::screenRatio()), QPointF(0,0));
    lGradient.setColorAt(0.0,  QColor(255,0,0,200));
    lGradient.setColorAt(0.3, Qt::transparent);
    lGradient.setColorAt(0.6, QColor(0,0,0,200));
    m_pScene->setForegroundBrush(lGradient);

    m_pScene->setBackgroundColor(QColor(5,38,64));

    // Instancier et initialiser les élément de l'interface :
    pDeathCount->setZValue(FIRST_LIGNE);
    pDeathCount = m_pScene->createText(QPointF(50,1200),"Nombre de mort : " + QString::number(pCharacter->getDeathCount()), 40, Qt::white);

    //Message aidant le joueur durant sont parcourt.
    QGraphicsSimpleTextItem* tips = new QGraphicsSimpleTextItem();
    tips->setZValue(FIRST_LIGNE);
    tips =  m_pScene->createText(QPointF(50,1450),
                                 "Touche de saut / réapparition : < Espace > \n"
                                 "Touche pour avancer à droite : < D > \n"
                                 "Touche pour avancer à gauche : < A > \n", 20, Qt::white);
    tips =  m_pScene->createText(QPointF(2500,1200),
                                 "Vous pouvez sauté sur l'ennemie pour le tuer.", 20, Qt::white);
    tips =  m_pScene->createText(QPointF(3010,1400),
                                 " Vous pouvez pousser la caisse pour atteindre \n la plate forme en face.", 12, Qt::white);

    // Instancier et initialiser les sprite ici :

    ///////////////////////////
    ////        SOL        ////
    ///////////////////////////
    QPointF posSol1_Platfond(0,750);
    m_Grounds->generated(40,3,posSol1_Platfond);

    QPointF posSol2_Platfond(5280,750);
    m_Grounds->generated(6,3,posSol2_Platfond);

    QPointF posSol1(0,1600);
    m_Grounds->generated(8,6,posSol1);

    QPointF posSol2(2200,1460);
    m_Grounds->generated(8,5,posSol2);

    QPointF posSol3(3960,1460);
    m_Grounds->generated(2,9,posSol3);

    QPointF posSol4(4460,1660);
    m_Grounds->generated(2,9,posSol4);

    QPointF posSol5(4900,1660);
    m_Grounds->generated(2,9,posSol5);

    QPointF posSol6(5300,1660);
    m_Grounds->generated(10,7,posSol6);

    QPointF posSol7(6800,1380);
    m_Grounds->generated(2,2,posSol7);

    QPointF posSol8(6800,1760);
    m_Grounds->generated(6,2,posSol8);


    //////////////////////////////////
    ////        PLATEFORME        ////
    //////////////////////////////////
    Sprite* plateformeMoyenne1 = new Sprite(GameFramework::imagesPath() + "PlatformeMoyenneV2.png");
    plateformeMoyenne1->setData(1,"sol");
    plateformeMoyenne1->setData(2,"plateforme");
    m_pScene->addSpriteToScene(plateformeMoyenne1, 1200,1600);

    Sprite* plateformeMoyenne2 = new Sprite(GameFramework::imagesPath() + "PlatformeMoyenneV2.png");
    plateformeMoyenne2->setData(1,"sol");
    plateformeMoyenne2->setData(2,"plateforme");
    m_pScene->addSpriteToScene(plateformeMoyenne2, 1500,1730);

    Sprite* plateformeMoyenne3 = new Sprite(GameFramework::imagesPath() + "PlatformeMoyenneV2.png");
    plateformeMoyenne3->setData(1,"sol");
    plateformeMoyenne3->setData(2,"plateforme");
    m_pScene->addSpriteToScene(plateformeMoyenne3, 1800,1600);

    Sprite* plateformeMoyenne4 = new Sprite(GameFramework::imagesPath() + "PlatformeMoyenneV2.png");
    plateformeMoyenne4->setData(1,"sol");
    plateformeMoyenne4->setData(2,"plateforme");
    m_pScene->addSpriteToScene(plateformeMoyenne4, 3680,1320);

    //Pile de caisse en métal.
    stackMetal(QPointF(5401,1580));
    stackMetal(QPointF(6201,1580));

    //////////////////////////////////
    //// Bouton de fin de niveau  ////
    //////////////////////////////////

    Sprite* pBoutonDeFin = new Sprite();
    pBoutonDeFin->setData(1,"FinDuNiveau");
    m_pScene->addSpriteToScene(pBoutonDeFin, 7080,1568);
    setAnimationEndingButon(pBoutonDeFin);

    /////////////////////////////
    ////        PIEGE        ////
    /////////////////////////////

    Sprite* lanceFlamme1 = new Sprite(GameFramework::imagesPath() + "lanceFlammeV3.png");
    lanceFlamme1->setData(1,"Piege");
    lanceFlamme1->setData(2,"Lance_flamme");
    m_pScene->addSpriteToScene(lanceFlamme1, 2400,1370);

    Sprite* lanceFlamme2 = new Sprite(GameFramework::imagesPath() + "lanceFlammeV3.png");
    lanceFlamme2->setData(1,"Piege");
    lanceFlamme2->setData(2,"Lance_flamme");
    m_pScene->addSpriteToScene(lanceFlamme2, 4580,1570);


    //////////////////////////////
    ////        CAISSE        ////
    //////////////////////////////

    CaisseAmovible* caisseBois1 = new CaisseAmovible;
    caisseBois1->setData(1,"Wood_caisse");
    caisseBois1->setSpawnPoint(QPoint(2900,1500));
    m_pScene->addSpriteToScene(caisseBois1, caisseBois1->getSpawnPoint());

    CaisseAmovible* caisseBois2 = new CaisseAmovible;
    caisseBois2->setData(1,"Wood_caisse");
    caisseBois2->setSpawnPoint(QPoint(4800,600));
    m_pScene->addSpriteToScene(caisseBois2,caisseBois2->getSpawnPoint());

    CaisseAmovible* caisseBois3 = new CaisseAmovible;
    caisseBois3->setData(1,"Wood_caisse");
    caisseBois3->setSpawnPoint(QPoint(5160,785));
    m_pScene->addSpriteToScene(caisseBois3, caisseBois3->getSpawnPoint());

    CaisseAmovible* caisseBois4 = new CaisseAmovible;
    caisseBois4->setData(1,"Wood_caisse");
    caisseBois4->setSpawnPoint(QPoint(6850,1360));
    m_pScene->addSpriteToScene(caisseBois4, caisseBois4->getSpawnPoint());

    Sprite* caisseMental1 = new Sprite(GameFramework::imagesPath() + "CaisseMetalV2.png");
    caisseMental1->setData(1,"sol");
    m_pScene->addSpriteToScene(caisseMental1, 700,1520);



    //////////////////////////////
    ////        ENEMIE        ////
    //////////////////////////////
    Bulio* enemie1 = new Bulio();
    enemie1->setData(1,"ennemie");
    enemie1->setData(2,"bulio");
    //m_pScene->addSpriteToScene(enemie1, 2500,1410);
    m_pScene->addSpriteToScene(enemie1, 5380,1430);

    Bulio* enemie2 = new Bulio();
    enemie2->setData(1,"ennemie");
    enemie2->setData(2,"bulio");
    m_pScene->addSpriteToScene(enemie2, 2500,1410);

    Bulio* enemie3 = new Bulio();
    enemie3->setData(1,"ennemie");
    enemie3->setData(2,"bulio");
    m_pScene->addSpriteToScene(enemie3, 5380,1410);

    Bulio* enemie4 = new Bulio();
    enemie4->setData(1,"ennemie");
    enemie4->setData(2,"bulio");
    m_pScene->addSpriteToScene(enemie4, 5380,1430);

    //Ajout des entités du jeu dans la liste.
    m_pEntityL.append(caisseBois1);
    m_pEntityL.append(caisseBois2);
    m_pEntityL.append(caisseBois3);
    m_pEntityL.append(caisseBois4);
    m_pEntityL.append(enemie1);
    m_pEntityL.append(enemie2);
    m_pEntityL.append(enemie3);
    m_pEntityL.append(enemie4);

    m_pBulioL.append(enemie1);
    m_pBulioL.append(enemie2);
    m_pBulioL.append(enemie3);
    m_pBulioL.append(enemie4);

    //Ajout du joueur dans la scene
    pCharacter->setData(1,"joueur");
    pCharacter->setSpawnPoint(QPoint(300,1200));
    m_pScene->addSpriteToScene(pCharacter,pCharacter->getSpawnPoint());
    pCharacter->startAnimation(25);
}
//! Refait apparaitre tout les ennemis de la scene.
void GameCore::reloadEnnemi(){

    //Retire tout les Bulios.
    for (int i = 0;i <= m_pScene->sprites().count();i++) {
        if(m_pScene->sprites().at(i)->data(2) == "bulio"){
            m_pScene->removeSpriteFromScene(m_pScene->sprites().at(i));
        }
    }

    //Réinitialise tout les Bulios
    for (int i = 0;i <= m_pEntityL.count();i++) {
        if(m_pEntityL.at(i)->data(2) == "bulio"){
            m_pEntityL.at(i)->setIsDeath(false);
            m_pScene->addSpriteToScene(m_pEntityL.at(i));
        }
    }
}

//! Génère une pile de caisse en métal.
//! \param firstCase position de la première caisse de la pile.
void GameCore::stackMetal(QPointF firstCase){

    //Caisse actuel
    QPointF CurrentPosCase = firstCase;
    for (int i = 1; i <= 5;i++) {

        if(i > 1 && i <= 3)
            CurrentPosCase.setX(CurrentPosCase.x() + 81);
        else if (i >= 4){
            if(i == 4){
                CurrentPosCase = firstCase;
                CurrentPosCase.setY(CurrentPosCase.y() - 78);
                CurrentPosCase.setX(CurrentPosCase.x() + 40);
            }else {
                CurrentPosCase.setX(CurrentPosCase.x() + 81);
            }

        }
        Sprite* caisseMCurrent = new Sprite(GameFramework::imagesPath() + "CaisseMetalV2.png");
        caisseMCurrent->setData(1,"sol");
        m_pScene->addSpriteToScene(caisseMCurrent,CurrentPosCase);

    }
}

//! Traite la pression d'une touche.
//! \param key Numéro de la touche (voir les constantes Qt)
//!
void GameCore::keyPressed(int key) {
    emit notifyKeyPressed(key);

    if(!pCharacter->getIsDeath() && !isFinished){
        switch(key) {
        case Qt::Key_W:
            if(pCharacter->getIsOnFloor()){
                pCharacter->m_velocity.setY(PLAYER_JUMP);
                pCharacter->setIsJump(true);
            }
            break;

        case Qt::Key_A:
            pCharacter->m_velocity.setX(-PLAYER_SPEED);
            break;

        case Qt::Key_D:
            pCharacter->m_velocity.setX(PLAYER_SPEED);
            break;

        case Qt::Key_Space:
            if(pCharacter->getIsOnFloor()){
                pCharacter->m_velocity.setY(PLAYER_JUMP);
                pCharacter->setIsJump(true);
            }
            break;
        }
    }
    if(key == Qt::Key_Space && pCharacter->getIsDeath()){
        pCharacter->respawn();
        m_pScene->removeSpriteFromScene(pGhost);
        m_pScene->addSpriteToScene(pCharacter, pCharacter->getSpawnPoint());
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
    }
}

//! Cadence.
//! Déplace le joueur en fonction de la touche préssé.
//! \param elapsedTimeInMilliseconds  Temps écoulé depuis le dernier appel.
void GameCore::tick(long long elapsedTimeInMilliseconds) {

    //Parcourt la liste des entités de la scene.
    for (int i = 0;i < m_pEntityL.count();i++) {
        if(!m_pEntityL.at(i)->getIsDeath()){
            if(m_pEntityL.at(i)->data(2) == "bulio"){

                BulioTickHandler* bTick = new BulioTickHandler(m_pEntityL.at(i),this);
                bTick->tick(elapsedTimeInMilliseconds);

            }else if (m_pEntityL.at(i)->data(1) == "Wood_caisse") {

                CaisseAmovTickHandler* cTick = new CaisseAmovTickHandler(m_pEntityL.at(i),this);
                cTick->tick(elapsedTimeInMilliseconds);
            }
        }
    }

    if(!pCharacter->getIsDeath()){

        //Animation du joueur
        Character::animation animation = Character::BASE;;

        if(pCharacter->getIsOnFloor() == false){
            animation = Character::SAUT;
        }else if(pCharacter->m_velocity.x() > 0.5 || pCharacter->m_velocity.x() < -0.5){
            animation =  Character::DEPLACEMENT;
        }
        pCharacter->configureAnimation(animation);

        //Déplace le joueur
        pCharacter->setPos(pCharacter->pos()+ pCharacter->m_velocity * elapsedTimeInMilliseconds/15.0);

        for (int i = m_pScene->sprites().count();i >= 0;i--) {
            if(m_pScene->sprites().at(i)->data(1) == "joueur"){
                //Suite les déplacement du joueur dans la scene
                m_pGameCanvas->getView()->centerOn(m_pScene->sprites().at(i)->pos().x(), 1450);
            }
        }

        //Prochaine position du joueur
        QRectF nextSpriteRect =
                pCharacter->globalBoundingBox().translated(pCharacter->m_velocity);

        // Récupère tous les sprites de la scène qui touche le joueur
        auto listeCurrentCollisionCharacter = pCharacter->parentScene()->collidingSprites(pCharacter);
        // Supprimer le sprite lui-même
        listeCurrentCollisionCharacter.removeAll(pCharacter);

        //récupère la valeur de liste (remplis/vide)
        bool currentCollision  = !listeCurrentCollisionCharacter.isEmpty();

        if(currentCollision){
            //Cherche les collisions entre le joueurs les autres sprites
            for (Sprite* CollisionDetected : listeCurrentCollisionCharacter) {

                //intersected entre ls prochaine position du joueur et le sprite touché.
                QRectF intersected = nextSpriteRect.intersected(CollisionDetected->globalBoundingBox());

                //List des coté touché
                QList<Entity::hitSide> collidingSidesL = QList<Entity::hitSide>();
                pCharacter->getCollisionLocate(collidingSidesL,nextSpriteRect,intersected);

                if (CollisionDetected->data(1) == "Piege") {

                    if(!pCharacter->getIsDeath()){
                        m_pGameCanvas->getView()->centerOn(CollisionDetected->pos());
                    }
                    setupCharacterDeath();

                }else if (CollisionDetected->data(1) == "ennemie") {

                    for (int i =0;i < collidingSidesL.count();i++) {
                        switch (collidingSidesL.at(i)) {
                        case Entity::hitSide::DOWN:
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
                }else if (CollisionDetected->data(1) == "Wood_caisse") {
                    for (int i =0;i < collidingSidesL.count();i++) {
                        switch (collidingSidesL.at(i)) {
                        case Entity::hitSide::DOWN:
                            //Truc de doryan bizarre
                            pCharacter->setY((CollisionDetected->top()-pCharacter->height()));
                            if(!pCharacter->getIsJump())
                                pCharacter->setIsOnFloor(true);
                            pCharacter->setIsJump(false);
                            pCharacter->m_velocity.setY(0);
                            break;
                        case  Entity::hitSide::UP:
                            setupCharacterDeath();
                            break;
                        case Entity::hitSide::RIGHT :
                            pCharacter->setX((CollisionDetected->left()- pCharacter->width())+5);
                            break;
                        case Entity::hitSide::LEFT :
                            pCharacter->setX((CollisionDetected->right()) -5);
                            break;
                        }
                    }

                }else if(CollisionDetected->data(1) == "FinDuNiveau"){
                    if(!isFinished){
                        pCharacter->setVisible(false);
                        isFinished=true;
                        setAnimationEndingButon(CollisionDetected);

                        QGraphicsSimpleTextItem* tips = new QGraphicsSimpleTextItem();
                        tips->setZValue(FIRST_LIGNE);

                        tips =  m_pScene->createText(QPointF(7140,1200),
                                                     "Bravo vous avez fini le jeu !", 40, Qt::green);
                        tips =  m_pScene->createText(QPointF(7140,1250),
                                                     "Merci d'avoir joué, vous pouvez fermer la fenêtre.", 20, Qt::gray);
                    }
                }else{
                    //Parcourt la list des local collision
                    for (int i =0;i < collidingSidesL.count();i++) {

                        switch (collidingSidesL.at(i)) {
                        case Entity::hitSide::DOWN:
                            pCharacter->setY((CollisionDetected->top()-pCharacter->height()));
                            if(!pCharacter->getIsJump())
                                pCharacter->setIsOnFloor(true);
                            pCharacter->setIsJump(false);
                            pCharacter->m_velocity.setY(0);
                            break;
                        case  Entity::hitSide::UP:
                            pCharacter->m_velocity.setY(0);
                            pCharacter->setY((CollisionDetected->bottom()+1));
                            break;
                        case Entity::hitSide::RIGHT :
                            pCharacter->setX((CollisionDetected->left()- pCharacter->width())+5);
                            break;
                        case Entity::hitSide::LEFT :
                            pCharacter->setX((CollisionDetected->right()) -5);
                            break;
                        }
                    }
                }

                collidingSidesL.clear();
          }
        }else{
            pCharacter->setIsOnFloor(false);
        }
        if(!pCharacter->parentScene()->isInsideScene(nextSpriteRect)){
            qDebug() << "Le joueur est sortit de la scene";
            setupCharacterDeath();
        }
    }else {
        pGhost->setY(pGhost->y() + GHOST_SPEED * elapsedTimeInMilliseconds/15.0);
    }
    //Attire le joueur vers le bas de l'écran
    pCharacter->gravityApplied(elapsedTimeInMilliseconds);
}

//!
//! Définit l'animation que va prendre le bouton de fin de niveau
//! @brief GameCore::setAnimationDeath
//!
void GameCore::setAnimationDeath()
{
    QImage spriteSheet(GameFramework::imagesPath() +  "deathAnimationV2.png");

    QList<QImage> deathFrameList;
    // Découpage de la spritesheet
    for (int frameIndex = 0; frameIndex <= FRAME_COUNT_GHOST; frameIndex++) {

        QImage CurrentFrameImage = spriteSheet.copy((frameIndex % COLUMN_COUNT_GHOST) * FRAME_SIZE_GHOST,
                                                    (frameIndex / COLUMN_COUNT_GHOST) * FRAME_SIZE_GHOST,
                                                    FRAME_SIZE_GHOST, FRAME_SIZE_GHOST);

        pGhost->addAnimationFrame(QPixmap::fromImage(CurrentFrameImage.scaled(FRAME_SIZE_GHOST * 1.5,
                                                                              FRAME_SIZE_GHOST * 1.5,
                                                                              Qt::IgnoreAspectRatio,
                                                                              Qt::SmoothTransformation)));
    }
    pGhost->startAnimation(50);
}

//!
//! Créé un sprite pour symbolisé la mort du joueur.
//! @brief GameCore::setAnimationDeath
//!
void GameCore::setAnimationEndingButon(Sprite* &endingButon)
{

    if(isFinished){

        QImage spriteSheet(GameFramework::imagesPath() +  "EmergencyMeetingButton.png");

        // Découpage de la spritesheet
        for (int frameIndex = 0; frameIndex <= FRAME_COUNT_ENDING_BUTON_ACTIVE; frameIndex++) {

            QImage CurrentFrameImage = spriteSheet.copy((frameIndex % COLUMN_COUNT_ENDING_BUTON_ACTIVE) * FRAME_ENDING_BUTON_ACTIVE_WIDTH,
                                                        (frameIndex / COLUMN_COUNT_ENDING_BUTON_ACTIVE) * FRAME_ENDING_BUTON_ACTIVE_HEIGT,
                                                        FRAME_ENDING_BUTON_ACTIVE_WIDTH, FRAME_ENDING_BUTON_ACTIVE_HEIGT);

            endingButon->addAnimationFrame(QPixmap::fromImage(CurrentFrameImage.scaled(FRAME_ENDING_BUTON_ACTIVE_WIDTH,
                                                                                  FRAME_ENDING_BUTON_ACTIVE_HEIGT,
                                                                                  Qt::IgnoreAspectRatio,
                                                                                  Qt::SmoothTransformation)));
        }
        endingButon->startAnimation(600);

    }else {
        QImage spriteSheet(GameFramework::imagesPath() +  "EmergencyMeetingButton.png");

        // Découpage de la spritesheet
        for (int frameIndex = 0; frameIndex <= FRAME_COUNT_ENDING_BUTON; frameIndex++) {

            QImage CurrentFrameImage = spriteSheet.copy((frameIndex % COLUMN_COUNT_ENDING_BUTON) * FRAME_ENDING_BUTON_WIDTH,
                                                        (frameIndex / COLUMN_COUNT_ENDING_BUTON) * FRAME_ENDING_BUTON_HEIGHT,
                                                        FRAME_ENDING_BUTON_WIDTH, FRAME_ENDING_BUTON_HEIGHT);

            endingButon->addAnimationFrame(QPixmap::fromImage(CurrentFrameImage.scaled(FRAME_ENDING_BUTON_WIDTH,
                                                                                  FRAME_ENDING_BUTON_HEIGHT,
                                                                                  Qt::IgnoreAspectRatio,
                                                                                  Qt::SmoothTransformation)));
        }
        endingButon->startAnimation(600);
    }
}

//!
//! Mets en place tout les éléments symbolisant la mort du joueur.
//! @brief GameCore::setupCharacterDeath
//!
void GameCore::setupCharacterDeath(){

    //Le joueur est considéré comme mort.
    pCharacter->setIsDeath(true);
    pGhost->setData(1,"Ghost");
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

    QString textMort = "mort";
    if(pCharacter->getDeathCount() > 1){
        textMort += "s";
    }
    pDeathCount->setText("Nombre de " + textMort + " : " + QString::number(pCharacter->getDeathCount()));

    //Refait apparaitre les enemis si le joueur est mort de suite 5 fois.
    if(pCharacter->getDeathCount()%5 == 0){
        //Message prévenant le joueur du retour des ennemis.
        pAlert->setZValue(FIRST_LIGNE);
        pAlert =  m_pScene->createText(QPointF(50,1300),
                                       "Les Bulios sont de retour !!", 20, Qt::red);
        reloadEnnemi();
    }else {
        m_pScene->removeItem(pAlert);
    }
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




