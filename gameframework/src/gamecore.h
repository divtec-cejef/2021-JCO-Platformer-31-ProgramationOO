/**
  \file
  \brief    Déclaration de la classe GameCore.
  \author   JCO
  \author   LKU
  \date     Janvier 2022
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
#include "caisseamovible.h"


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
    void setupCharacterDeath();

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

    QGraphicsSimpleTextItem* pDeathCount = new QGraphicsSimpleTextItem();

    //Joueur
    Character* pCharacter = new Character();

    Sprite* pGhost = new Sprite();
    void setAnimationDeath();
QRadialGradient lGradient;

    QList<QGraphicsTransform*> m_transformsForFlip;

    QList<Bulio*> m_pBulioL;
    QList<CaisseAmovible*> m_pCaisseMovL;

    Ground* m_Grounds = new Ground;

    //Collision
    void currentCollision(Entity* entity);
    void futureCollision(Entity* entity);


private slots:

    //    void onSpriteDestroyed(QObject* pSprite);

};


#endif // GAMECORE_H
