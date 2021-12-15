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
#include "bulio.h"

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
    QPointF m_gravity = QPointF(0,2);
    //QPointF velocity = QPointF(0,0);

    void gravityApplied(Entity* entity,QPointF &enti_velocity,long long elapsedTime);

    void tick(long long elapsedTimeInMilliseconds);

    //Collision
    void getCollisonLocate(QList<Entity::hitSide>&collisionLocateList,QRectF posSprite,QRectF intersected);
    //void commonInteraction(Entity* CurrentEntity, Sprite* sprite,QRectF posSprite,QRectF intersected);

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

    //Collision


    //Actuelle
    //void currentCollision(Sprite* entity);
    //Future
    //void futurCollision(Sprite* entity);

    //Joueur
    Character* pCharacter = new Character();
    Sprite* pGhost = new Sprite();
    void setAnimationDeath();
    void setupCharacterDeath();

    QList<QGraphicsTransform*> m_transformsForFlip;

    QList<Bulio*> m_pBulioList;

    Ground* m_Grounds = new Ground;

    //Collision
    void currentCollision(Entity* entity);
    void futureCollision(Entity* entity);


private slots:

//    void onSpriteDestroyed(QObject* pSprite);

};


#endif // GAMECORE_H
