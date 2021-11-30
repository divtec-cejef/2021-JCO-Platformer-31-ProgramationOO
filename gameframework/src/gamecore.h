/**
  \file
  \brief    Déclaration de la classe GameCore.
  \author   JCO
  \date     septembre 2018
*/
#ifndef GAMECORE_H
#define GAMECORE_H

#include <QObject>
#include <QPointF>

#include <QGraphicsTransform>
 #include <QList>
#include "character.h"
#include "gameview.h"
#include "ground.h"

class GameCanvas;
class GameScene;
class Sprite;

//! \brief Classe qui gère la logique du jeu.
//!
//! Dans son état actuel, cette classe crée une scène vide, délimite
//! sa surface avec une ligne blanche puis démarre la cadence du jeu.
class GameCore : public QObject
{

    Q_OBJECT
public:
    explicit GameCore(GameCanvas* pGameCanvas, QObject *parent = nullptr);
    ~GameCore();

    void keyPressed(int key);
    void keyReleased(int key);

    void mouseMoved(QPointF newMousePosition);
    void mouseButtonPressed(QPointF mousePosition, Qt::MouseButtons buttons);
    void mouseButtonReleased(QPointF mousePosition, Qt::MouseButtons buttons);


    //Physique
    QPointF gravity = QPointF(0,2);
    QPointF velocity = QPointF(0,0);
    bool isOnFloor = false;
    bool isJump = false;


    void tick(long long elapsedTimeInMilliseconds);


signals:
    void notifyMouseMoved(QPointF newMousePosition);
    void notifyMouseButtonPressed(QPointF mousePosition, Qt::MouseButtons buttons);
    void notifyMouseButtonReleased(QPointF mousePosition, Qt::MouseButtons buttons);
    void notifyKeyPressed(int key);
    void notifyKeyReleased(int key);

private:

    GameCanvas* m_pGameCanvas;
    GameScene* m_pScene;
    GameView* m_pView;


    //Character m_character();

    int distanceLeft = 0;
    int distanceRight = 0;
    int distanceJump = 0;
    int m_playerDirection = 1;

    //QPointF p_position = QPointF(0,0);


    Character* pCharacter = new Character();
    Ground* pGround = new Ground();
    QList<QGraphicsTransform*> m_transformsForFlip;

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

    void configureOrientation(orientation orientation, Sprite* &ground);



private slots:

//    void onSpriteDestroyed(QObject* pSprite);

};


#endif // GAMECORE_H
