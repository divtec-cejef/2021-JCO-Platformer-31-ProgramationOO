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

//Ajoute Supp
#include "sprite.h"

const int PLAYER_SPEED = 10 ; // vitesse de déplacement du joueur en pixels/s
const int PLAYER_STOP = 0;

const int SCENE_WIDTH = 1280;


//spriteSheet animation de marche à gauche
const int FRAME_WIDTH = 192;
const int FRAME_HEIGHT = 192;
const int FRAME_COUNT = 4;
const int COLUMN_COUNT = 2;
const float SCALE_RATIO = 2;


//Type d'animation du joueurs
enum ANIM_PLAYER{
    SAUT,
    DEPLA_GAUCHE,
    DEPLA_DROITE,
    ATTA_GAUCHE,
    ATTA_DROITE
};

static char PressedKeyInit;

void configureAnimation(Sprite* pSprite) {


    //if(Player == GAUCHE){
    QImage spriteSheet(GameFramework::imagesPath() + "MarcheGaucheV4.png");


    // Découpage de la spritesheet
    for (int frameIndex = 0; frameIndex < COLUMN_COUNT; frameIndex++) {
        QImage sprite = spriteSheet.copy((frameIndex % FRAME_COUNT) * FRAME_WIDTH,
                                         (frameIndex / FRAME_COUNT) * FRAME_HEIGHT,
                                         FRAME_WIDTH, FRAME_HEIGHT);

        pSprite->addAnimationFrame(QPixmap::fromImage(sprite.scaled(FRAME_WIDTH * 1,
                                                                    FRAME_HEIGHT * 1,
                                                                    Qt::IgnoreAspectRatio,
                                                                    Qt::SmoothTransformation)));
    }

    //pSprite->setAnimationSpeed(25);
    //}else{
        //pSprite = new Sprite(GameFramework::imagesPath() + "BasicPoseGauche.png");
   // }
}


//! Initialise le contrôleur de jeu.
//! \param pGameCanvas  GameCanvas pour lequel cet objet travaille.
//! \param pParent      Pointeur sur le parent (afin d'obtenir une destruction automatique de cet objet).
GameCore::GameCore(GameCanvas* pGameCanvas, QObject* pParent) : QObject(pParent) {

    // Mémorise l'accès au canvas (qui gère le tick et l'affichage d'une scène)
    m_pGameCanvas = pGameCanvas;
    
    // Créé la scène de base et indique au canvas qu'il faut l'afficher.
    m_pScene = pGameCanvas->createScene(0, 0, SCENE_WIDTH, SCENE_WIDTH / GameFramework::screenRatio());
    pGameCanvas->setCurrentScene(m_pScene);
    
    // Trace un rectangle blanc tout autour des limites de la scène.
    m_pScene->addRect(m_pScene->sceneRect(), QPen(Qt::white));
    

    // Instancier et initialiser les sprite ici :
    // ...
    Sprite* pSprite = new Sprite(GameFramework::imagesPath() + "BasicPoseGaucheV3.png");
    m_pScene->addSpriteToScene(pSprite, 20,600);

    pSprite->startAnimation(100);
    //ANIM_PLAYER Player = GAUCHE;
    configureAnimation(pSprite);

    m_pPlayer = pSprite;


    // ...
    // m_pGameCanvas->startTick();

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
    switch(key) {
    case Qt::Key_Left:
        distanceLeft = PLAYER_SPEED;
        break;

    case Qt::Key_Right:
        distanceRight = PLAYER_SPEED;
        break;
    }
}

//! Traite le relâchement d'une touche.
//! \param key Numéro de la touche (voir les constantes Qt)
void GameCore::keyReleased(int key) {
    emit notifyKeyReleased(key);

    switch(key) {
    case Qt::Key_Left:

        distanceLeft = PLAYER_STOP;
        break;

    case Qt::Key_Right:
        distanceRight = PLAYER_STOP;
        break;
    }
}

//! Cadence.
//! éplace le joueur en fonction de la touche préssé.
//! \param elapsedTimeInMilliseconds  Temps écoulé depuis le dernier appel.
void GameCore::tick(long long elapsedTimeInMilliseconds) {

    float distance = PLAYER_SPEED * elapsedTimeInMilliseconds / 1000.0F;


        m_pPlayer->setX(m_pPlayer->x() + distanceRight);
        //configureAnimation(pSprite);

        m_pPlayer->setX(m_pPlayer->x() - distanceLeft);

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



