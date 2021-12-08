#ifndef BULIO_H
#define BULIO_H

#include <QObject>
#include <QPointF>

#include <QGraphicsTransform>
#include <QList>

#include <sprite.h>
#include <entity.h>

class Bulio: public Entity
{
public:
    Bulio(QGraphicsItem* pParent = nullptr);


    //Type d'animation du joueurs
    enum animation{
        BASE = 0,
        DEPLACEMENT = 1,
        SAUT = 3,
        ATTAQUE = 4,
    };

    void configureAnimation(animation bulio);


    QPointF getVelocity();
    void updateCharacterVelocity();


    bool getIsOnFloor();
    void setIsOnFloor(bool _isOnFloor);


    bool getIsJump();
    void setIsJump(bool _isJump);

    //Mort
    bool getIsDeath();
    void setIsDeath(bool _isDeath);

    //Compteur de mort(s)
    int getDeathCount();
    void incrementDeathCount();

    void respawn();

public slots:

    void onKeyPressed(int key);
    void onKeyReleased(int key);

private:

    bool m_isJump = false;


    int m_deathCount = 0;

    void configureTransformationMatrix();

    QList<QImage>m_listAnimation;
    void setAnimationDeplacementList();
};


#endif // BULIO_H
