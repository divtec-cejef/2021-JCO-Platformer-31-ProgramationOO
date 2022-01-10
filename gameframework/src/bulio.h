#ifndef BULIO_H
#define BULIO_H

#include <QObject>
#include <QPointF>

#include <QGraphicsTransform>
#include <QList>

#include <sprite.h>
#include <entity.h>

//#include "buliotickhandler.h"

class Bulio: public Entity
{
public:
    Bulio(QGraphicsItem* pParent = nullptr);


    //Type d'animation du bulio
    enum animation{
        BASE = 0,
        DEPLACEMENT = 1,
        SAUT = 3,
        ATTAQUE = 4,
    };

    //Configuration des animation du bulio
    void configureAnimation(animation bulio);

    //Gestion des déplacement du Bulio
    QPointF getVelocity();
    void updateVelocity();
    //Définit les déplacement du Bulio dans le jeu.
    void collisionDetection(QRectF rect);
    //void move(long long elapsedTimeInMilliseconds);


    bool getIsOnFloor();
    void setIsOnFloor(bool _isOnFloor);


    bool getIsJump();
    void setIsJump(bool _isJump);

    //Définit si le Bulio doit être détruite ou non.
    bool getIsDeath();
    void setIsDeath(bool _isDeath);

    void respawn();



public slots:

    void onKeyPressed(int key);
    void onKeyReleased(int key);

private:

    bool m_isJump = false;

    void configureTransformationMatrix();

    QList<QImage>m_listAnimation;
    void setAnimationDeplacementList();

};


#endif // BULIO_H
