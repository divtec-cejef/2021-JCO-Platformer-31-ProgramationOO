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

//Ajoute Supp
#include <QString>

const int PLAYER_SPEED = 10 ; // vitesse de déplacement du joueur en pixels/s
const int PLAYER_JUMP= -10 ; //Vitesse du saute
const int PLAYER_STOP = 0;

//résolution de la fenetre
const int SCENE_WIDTH = 1280;


//spriteSheet animation de marche à gauche

//const float SCALE_RATIO = 2;

//static
static Sprite* WOODCAISSE_SPRITE;

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

    m_pScene->addSpriteToScene(pCharacter, 300,200);

    pCharacter->startAnimation(25);

    //configureAnimation(pCharacter,BASE);


    Sprite* caisseM1 = new Sprite(GameFramework::imagesPath() + "CaisseMetalV1.png");
    caisseM1->setData(1,"Metal_caisse");
    caisseM1->setData(2,"Sol");
    m_pScene->addSpriteToScene(caisseM1, 300,465);


    Sprite* Sol1 = new Sprite(GameFramework::imagesPath() + "solV2.png");
    Sol1->setData(1,"soltest");
    Sol1->setData(2,"sol");
    m_pScene->addSpriteToScene(Sol1, 1,600);

    WOODCAISSE_SPRITE = new Sprite(GameFramework::imagesPath() + "CaisseV1.png");
    WOODCAISSE_SPRITE->setData(1,"Wood_caisse");
    WOODCAISSE_SPRITE->setData(2,"sol");
    m_pScene->addSpriteToScene(WOODCAISSE_SPRITE, 600,465);



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
    //emit notifyKeyPressed(key);

    Character::animation player;

    switch(key) {
    case Qt::Key_Left:
       pCharacter->m_velocity.setX(-PLAYER_SPEED);
        player = Character::DEPLA_GAUCHE;
        break;

    case Qt::Key_Right:
        pCharacter->m_velocity.setX(PLAYER_SPEED);
        player = Character::DEPLA_DROITE;
        break;

    case Qt::Key_Up:
        if(isOnFloor){
            player = Character::SAUT;
            pCharacter->m_velocity.setY(PLAYER_JUMP);
            isJump = true;
            qDebug() << "isJump : " << isJump;
        }else{
            player = Character::BASE;
        }
        //qDebug() << "pCharacter->m_velocity y : " << pCharacter->m_velocity.y();
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
        //if(isOnFloor){
        player = Character::SAUT;
        pCharacter->m_velocity.setY(PLAYER_JUMP);
        isJump = true;
        //qDebug() << "isJump : " << isJump;
        //}
        break;

    default:
        player = Character::BASE;
    }
     //m_character(pCharacter).configureAnimation();
    pCharacter->configureAnimation(player);
}

//! Traite le relâchement d'une touche.
//! \param key Numéro de la touche (voir les constantes Qt)
void GameCore::keyReleased(int key) {
    //emit notifyKeyReleased(key);

    switch(key) {
    case Qt::Key_Left:
        pCharacter->m_velocity.setX(PLAYER_STOP);
        //distanceLeft = PLAYER_STOP;
        break;

    case Qt::Key_Right:
        pCharacter->m_velocity.setX(PLAYER_STOP);
        //distanceRight = PLAYER_STOP;
        break;
    case Qt::Key_Up:
        pCharacter->m_velocity.setY(PLAYER_STOP);
        //isJump = false;
        //qDebug() << "isJump : " << isJump;
        break;

    case Qt::Key_A:
        pCharacter->m_velocity.setX(PLAYER_STOP);
        break;

    case Qt::Key_D:
        pCharacter->m_velocity.setX(PLAYER_STOP);
        break;

    case Qt::Key_Space:
        pCharacter->m_velocity.setY(PLAYER_STOP);
        isJump = false;
        break;
    }
    //if(!isOnFloor)
        //pCharacter->configureAnimation(Character::SAUT);
    //else {
        pCharacter->configureAnimation(Character::BASE);
    //}
}

//! Cadence.
//! éplace le joueur en fonction de la touche préssé.
//! \param elapsedTimeInMilliseconds  Temps écoulé depuis le dernier appel.
void GameCore::tick(long long elapsedTimeInMilliseconds) {

    pCharacter->setPos(pCharacter->pos()+ pCharacter->m_velocity);
    // Récupère tous les sprites de la scène qui touche ce sprite
    auto listeCurrentCollision = pCharacter->parentScene()->collidingSprites(pCharacter);
    // Supprimer le sprite lui-même
    listeCurrentCollision.removeAll(pCharacter);

    //récupère la valeur de liste (remplis/vide)
    bool currentCollision  = !listeCurrentCollision.isEmpty();

    if(currentCollision){
        //Cherche les collisions entre le joueurs les autres sprites
        for (Sprite* CollisionDetected : listeCurrentCollision) {


            if(CollisionDetected->data(1) == "Wood_caisse"){

                WOODCAISSE_SPRITE->setX(WOODCAISSE_SPRITE->x() + pCharacter->m_velocity.x());
                //p_position.setX(m_pCharacter->x() + 1);

            }else if(CollisionDetected->data(1) == "Metal_caisse"){
                //pCharacter->setX(pCharacter->x() + pCharacter->pCharacter->m_velocity.x());
                //p_position.setY(-4);

            }
        }
    }

    // Détermine la prochaine position du sprite selon sa velocité
    QPainterPath nextSpriteRect = pCharacter->globalShape().translated(pCharacter->m_velocity);



    // Récupère tous les sprites de la scène que toucherait ce sprite à sa prochaine position
    auto listeFuturCollision = pCharacter->parentScene()->collidingSprites(nextSpriteRect);
    // Supprime le sprite lui-même, qui collisionne toujours avec sa boundingbox
    listeFuturCollision.removeAll(pCharacter);

    //récupère la valeur de liste (remplis/vide)
    bool futurCollision = !listeFuturCollision.isEmpty();

    if(futurCollision){
        //Cherche de potentielle futur collisions entre le joueur et les autres sprites
        for (Sprite* CollisionDetected : listeFuturCollision) {
            if (CollisionDetected->data(2) == "sol") {

                if(!isOnFloor)
                    //pCharacter->configureAnimation(Character::BASE);
                    isOnFloor = true;
                     pCharacter->m_velocity.setY(0.0);
                    isJump = false;

                //qDebug() << "sol pas loin";
            }else{
                isOnFloor = false;
            }
        }
    }else {
        isOnFloor = false;
    }

    //Si le joueur ne touche pas le sol alors il est attiré vers le bas
    if (!isOnFloor){
        //qDebug() << "PAS SUR LE SOL";
        pCharacter->setPos(pCharacter->pos() + pCharacter->m_velocity * (elapsedTimeInMilliseconds/100.0));
        pCharacter->m_velocity+= gravity * (elapsedTimeInMilliseconds/100.0);
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




