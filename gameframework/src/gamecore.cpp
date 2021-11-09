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
const int FRAME_WIDTH = 96;
const int FRAME_HEIGHT = 96;
const int FRAME_COUNT = 4;
const int COLUMN_COUNT = 2;
//const float SCALE_RATIO = 2;


//Type d'animation du joueurs
enum ANIM_PLAYER{
    SAUT,
    DEPLA_GAUCHE,
    DEPLA_DROITE,
    ATTA_GAUCHE,
    ATTA_DROITE,
    BASE
};


//static
static Sprite* WOODCAISSE_SPRITE;
static Sprite* METALCAISSE_SPRITE;


void configureAnimation(Sprite* pSprite,ANIM_PLAYER Player) {

    pSprite->clearAnimations();
    QString iSprite;

    switch (Player) {
    case DEPLA_GAUCHE:
        iSprite = "MarcheGaucheV7.png";
        break;
    case DEPLA_DROITE:
        iSprite =  "MarcheDroiteV7.png";
        break;
    case SAUT:
        iSprite = "SautDroiteV1.png";
        break;
    case BASE:
        iSprite = "BasicPoseV2.png";
    }

    if(iSprite == "MarcheDroiteV7.png" || iSprite == "MarcheGaucheV7.png"){

        QImage spriteSheet(GameFramework::imagesPath() + iSprite);

        // Découpage de la spritesheet
        for (int frameIndex = 0; frameIndex < FRAME_COUNT; frameIndex++) {
            QImage sprite = spriteSheet.copy((frameIndex % COLUMN_COUNT) * FRAME_WIDTH,
                                             (frameIndex / COLUMN_COUNT) * FRAME_HEIGHT,
                                             FRAME_WIDTH, FRAME_HEIGHT);

            pSprite->addAnimationFrame(QPixmap::fromImage(sprite.scaled(FRAME_WIDTH * 1,
                                                                        FRAME_HEIGHT * 1,
                                                                        Qt::IgnoreAspectRatio,
                                                                        Qt::SmoothTransformation)));
        }

        // qDebug() << "MARCHE "<< iSprite;
    }else {
        //pSprite = new Sprite(GameFramework::imagesPath() + "BasicPoseV1.png");
        pSprite->addAnimationFrame(GameFramework::imagesPath() + iSprite);
        //qDebug() << "BASE " << iSprite;

    }
    pSprite->startAnimation(25);


    //pSprite->setAnimationSpeed(25);
    //}else{
    //pSprite = new Sprite(GameFramework::imagesPath() + "BasicPoseGauche.png");
    //}
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
    Pplayer = new Sprite(GameFramework::imagesPath() + "BasicPoseV2.png");
    m_pScene->addSpriteToScene(Pplayer, 300,200);

    Pplayer->setAnimationSpeed(25);
    configureAnimation(Pplayer,BASE);



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






    //Sprite* Sol2 = new Sprite(GameFramework::imagesPath() + "solV1.png");
    //Sol2->setData(1,"sol");
    //m_pScene->addSpriteToScene(Sol2, 700,600);


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

    ANIM_PLAYER animation;

    switch(key) {
    case Qt::Key_Left:
        velocity.setX(-PLAYER_SPEED);
        animation = DEPLA_GAUCHE;
        break;

    case Qt::Key_Right:
        velocity.setX(PLAYER_SPEED);
        animation = DEPLA_DROITE;
        break;

    case Qt::Key_Up:
        if(isOnFloor){
            animation = SAUT;
            velocity.setY(PLAYER_JUMP);
            isJump = true;
            qDebug() << "isJump : " << isJump;
        }else{
            animation = BASE;
        }
        //qDebug() << "velocity y : " << velocity.y();
        break;

    case Qt::Key_A:
        velocity.setX(-PLAYER_SPEED);
        animation = DEPLA_GAUCHE;
        break;

    case Qt::Key_D:
        velocity.setX(PLAYER_SPEED);
        animation = DEPLA_DROITE;
        break;

    case Qt::Key_Space:
        //if(isOnFloor){
        animation = SAUT;
        velocity.setY(PLAYER_JUMP);
        isJump = true;
        //qDebug() << "isJump : " << isJump;
        //}
        break;

    default:
        animation = BASE;
    }
    Pplayer->setAnimationSpeed(25);
     m_character().configureAnimation(Character::SAUT);
    //configureAnimation(Pplayer,animation);
}

//! Traite le relâchement d'une touche.
//! \param key Numéro de la touche (voir les constantes Qt)
void GameCore::keyReleased(int key) {
    emit notifyKeyReleased(key);

    switch(key) {
    case Qt::Key_Left:
        velocity.setX(PLAYER_STOP);
        //distanceLeft = PLAYER_STOP;
        break;

    case Qt::Key_Right:
        velocity.setX(PLAYER_STOP);
        //distanceRight = PLAYER_STOP;
        break;
    case Qt::Key_Up:
        velocity.setY(PLAYER_STOP);
        //isJump = false;
        //qDebug() << "isJump : " << isJump;
        break;

    case Qt::Key_A:
        velocity.setX(PLAYER_STOP);
        break;

    case Qt::Key_D:
        velocity.setX(PLAYER_STOP);
        break;

    case Qt::Key_Space:
        velocity.setY(PLAYER_STOP);
        isJump = false;
        break;
    }
    if(isOnFloor)
        configureAnimation(Pplayer,BASE);
    else {
        configureAnimation(Pplayer,SAUT);
    }
}

//! Cadence.
//! éplace le joueur en fonction de la touche préssé.
//! \param elapsedTimeInMilliseconds  Temps écoulé depuis le dernier appel.
void GameCore::tick(long long elapsedTimeInMilliseconds) {

    Pplayer->setPos(Pplayer->pos()+ velocity);
    // Récupère tous les sprites de la scène qui touche ce sprite
    auto listeCurrentCollision = Pplayer->parentScene()->collidingSprites(Pplayer);
    // Supprimer le sprite lui-même
    listeCurrentCollision.removeAll(Pplayer);

    //récupère la valeur de liste (remplis/vide)
    bool currentCollision  = !listeCurrentCollision.isEmpty();

    if(currentCollision){
        //Cherche les collisions entre le joueurs les autres sprites
        for (Sprite* CollisionDetected : listeCurrentCollision) {


            if(CollisionDetected->data(1) == "Wood_caisse"){

                WOODCAISSE_SPRITE->setX(WOODCAISSE_SPRITE->x() + velocity.x());
                //p_position.setX(m_pPlayer->x() + 1);

            }else if(CollisionDetected->data(1) == "Metal_caisse"){
                //Pplayer->setX(Pplayer->x() + velocity.x());
                //p_position.setY(-4);

            }
        }
    }

    // Détermine la prochaine position du sprite selon sa velocité
    QPainterPath nextSpriteRect = Pplayer->globalShape().translated(velocity);



    // Récupère tous les sprites de la scène que toucherait ce sprite à sa prochaine position
    auto listeFuturCollision = Pplayer->parentScene()->collidingSprites(nextSpriteRect);
    // Supprime le sprite lui-même, qui collisionne toujours avec sa boundingbox
    listeFuturCollision.removeAll(Pplayer);

    //récupère la valeur de liste (remplis/vide)
    bool futurCollision = !listeFuturCollision.isEmpty();

    if(futurCollision){
        //Cherche de potentielle futur collisions entre le joueur et les autres sprites
        for (Sprite* CollisionDetected : listeFuturCollision) {
            if (CollisionDetected->data(2) == "sol") {

                if(!isOnFloor)
                    configureAnimation(Pplayer,BASE);

                isOnFloor = true;
                velocity.setY(0.0);
                isJump = false;

                //qDebug() << "sol pas loin";
            }else{
                isOnFloor = false;
            }
        }
    }else {
        isOnFloor = false;
    }

    if (!isOnFloor){
        //qDebug() << "PAS SUR LE SOL";
        Pplayer->setPos(Pplayer->pos() + velocity * (elapsedTimeInMilliseconds/100.0));
        velocity+= gravity * (elapsedTimeInMilliseconds/100.0);
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




