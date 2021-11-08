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


//Ajoute Supp
#include <QString>

const int PLAYER_SPEED = 50 ; // vitesse de déplacement du joueur en pixels/s
const int PLAYER_JUMP= 10 ; //Vitesse du saute
const int PLAYER_STOP = 0;

//résolution de la fenetre
const int SCENE_WIDTH = 1280;


//spriteSheet animation de marche à gauche
const int FRAME_WIDTH = 192;
const int FRAME_HEIGHT = 192;
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
        iSprite = "MarcheGaucheV4.png";
        break;
    case DEPLA_DROITE:
        iSprite =  "MarcheDroiteV4.png";
        break;
    case SAUT:
        iSprite = "BasicPoseV1.png";
        break;
    case BASE:
        iSprite = "BasicPoseV1.png";
    }

    if(iSprite == "MarcheDroiteV4.png" || iSprite == "MarcheGaucheV4.png"){

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
        pSprite->addAnimationFrame(GameFramework::imagesPath() + "BasicPoseV1.png");
        qDebug() << "BASE " << iSprite;

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
    Pplayer = new Sprite(GameFramework::imagesPath() + "BasicPoseV1.png");
    m_pScene->addSpriteToScene(Pplayer, 500,200);

    Pplayer->setAnimationSpeed(25);
    configureAnimation(Pplayer,BASE);

    WOODCAISSE_SPRITE = new Sprite(GameFramework::imagesPath() + "CaisseV1.png");
    WOODCAISSE_SPRITE->setData(1,"Wood_caisse");
    m_pScene->addSpriteToScene(WOODCAISSE_SPRITE, 200,500);

    Sprite* caisseM1 = new Sprite(GameFramework::imagesPath() + "CaisseMetalV1.png");
    caisseM1->setData(1,"Metal_caisse");
    m_pScene->addSpriteToScene(caisseM1, 700,200);

    Sprite* Sol1 = new Sprite(GameFramework::imagesPath() + "solV1.png");
    Sol1->setData(1,"sol");
    m_pScene->addSpriteToScene(Sol1, 500,600);

    Sprite* Sol2 = new Sprite(GameFramework::imagesPath() + "solV1.png");
    Sol2->setData(1,"sol");
    m_pScene->addSpriteToScene(Sol2, 700,600);


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
        //distanceLeft = PLAYER_SPEED;
        //p_position.setX(-PLAYER_SPEED);
        animation = DEPLA_GAUCHE;
        break;

    case Qt::Key_Right:
        //distanceRight = PLAYER_SPEED;
        velocity.setX(PLAYER_SPEED);
        animation = DEPLA_DROITE;
        break;

    case Qt::Key_Up:
        //if(isOnFloor){
        animation = BASE;
        //distanceJump = PLAYER_JUMP;
        velocity.setY(-10);
        isJump = true;
        qDebug() << "isJump : " << isJump;
        //}
        break;

    default:
        animation = BASE;
    }
    Pplayer->setAnimationSpeed(25);
    configureAnimation(Pplayer,animation);
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
        isJump = false;
        qDebug() << "isJump : " << isJump;
        break;
    }

    configureAnimation(Pplayer,BASE);
    //other keys

    //do collisions


}

//! Cadence.
//! éplace le joueur en fonction de la touche préssé.
//! \param elapsedTimeInMilliseconds  Temps écoulé depuis le dernier appel.
void GameCore::tick(long long elapsedTimeInMilliseconds) {

    bool currentCollision = false;
    bool futurCollision = false;
    QPointF bondingBoxSize = QPointF(0,40);
    // Détermine la prochaine position du sprite
    QRectF nextSpriteRect = Pplayer->globalBoundingBox().translated(bondingBoxSize);
    // Récupère tous les sprites de la scène que toucherait ce sprite à sa prochaine position
    auto listeFuturCollision = Pplayer->parentScene()->collidingSprites(nextSpriteRect);
    futurCollision = !listeFuturCollision.isEmpty();

    // Récupère tous les sprites de la scène qui touche ce sprite
    auto listeCurrentCollision = Pplayer->parentScene()->collidingSprites(Pplayer);
    // Supprimer le sprite lui-même, qui collisionne toujours avec sa boundingbox
    listeCurrentCollision.removeAll(Pplayer);

    currentCollision = !listeCurrentCollision.isEmpty();
    if(currentCollision){

        for (Sprite* CollisionDetected : listeCurrentCollision) {

            if(CollisionDetected->data(1) == "Wood_caisse"){

                WOODCAISSE_SPRITE->setX(WOODCAISSE_SPRITE->x() - 1);
                //p_position.setX(m_pPlayer->x() + 1);

            }else if(CollisionDetected->data(1) == "Metal_caisse"){
                Pplayer->setX(Pplayer->x() - 10);
                //p_position.setY(-4);

            }
        }
    }
    if(futurCollision){
        for (Sprite* CollisionDetected : listeFuturCollision) {
            if (CollisionDetected->data(1) == "sol") {
                isOnFloor = true;
                isJump = false;
                //Pplayer->setY(Pplayer->y() - 1);
               qDebug() << "sol pas loin";
            }
        }
         qDebug() << "aedferfrg";
    }
    if (!isOnFloor){
        //qDebug() << "PAS SUR LE SOL";
        Pplayer->setPos(Pplayer->pos() + velocity * (elapsedTimeInMilliseconds/100.0));
        velocity+= gravity * (elapsedTimeInMilliseconds/100.0);
    }
    if(isJump || !currentCollision){
        isOnFloor = false;
    }

        Pplayer->setPos(Pplayer->pos()+ velocity);


    /*
    auto collidingSprites = Pplayer->parentScene()->collidingSprites(nextSpriteRect);

    // Si la prochaine position du sprite n'est pas comprise au sein de la scène,
    // ou s’il y a collision, le sprite n’est pas déplacé et change de direction
    if (!Pplayer->parentScene()->isInsideScene(nextSpriteRect) ||
    collision)
    m_playerDirection *= -1;
    else
    // S'il n'y a pas de collision et que le sprite ne sort pas de la scène, on le déplace
    // (en lui appliquant le vecteur de déplacement)
    Pplayer->setPos(Pplayer->pos() + velocity);
    */
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




