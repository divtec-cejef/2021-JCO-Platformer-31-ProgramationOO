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
    QPointF velocity = QPointF(0,10);
    bool isOnFloor = false;
    bool isJump = false;
    QVariant collisionCurrent;

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
    Sprite* Pplayer;


    int distanceLeft = 0;
    int distanceRight = 0;
    int distanceJump = 0;
    int m_playerDirection = 1;

    //QPointF p_position = QPointF(0,0);

    void configureTransformationMatrix();

    QList<QGraphicsTransform*> m_transformsForFlip;



private slots:

//    void onSpriteDestroyed(QObject* pSprite);

};


#endif // GAMECORE_H
