#ifndef CHARACTER_H
#define CHARACTER_H

#include <QObject>
#include <QPointF>

#include <QGraphicsTransform>
#include <QList>

#include <sprite.h>


class Character: public Sprite
{
public:


    Character(QGraphicsItem* pParent = nullptr);

    //Type d'animation du joueurs
    enum animation{
        BASE = 0,
        DEPLACEMENT = 1,
        SAUT = 3,
        ATTAQUE = 4,
    };

    void configureAnimation(animation player);
    void respawn();

    QPointF m_velocity = QPointF(0,0);
    QPointF m_lastVelocity = m_velocity;
    QPointF getVelocity();
    void updateCharacterVelocity();

    bool m_isOnFloor = false;
    bool getIsOnFloor();
    void setIsOnFloor(bool _isOnFloor);

    bool m_isJump = false;
    bool getIsJump();
    void setIsJump(bool _isJump);

    //Mort
    bool m_isDeath = false;
    bool getIsDeath();
    void setIsDeath(bool _isDeath);

    //Compteur de mort(s)
    int m_deathCount = 0;
    int getDeathCount();
    void incrementDeathCount();

    /*
    bool m_keyUpPressed;
    bool m_keyDownPressed;
    bool m_keyLeftPressed;
    bool m_keyRightPressed;
    */

public slots:

    void onKeyPressed(int key);
    void onKeyReleased(int key);

private:
     void configureTransformationMatrix();

     QList<QImage>m_listAnimation;
     void setAnimationDeplacementList();
};

#endif // CHARACTER_H
