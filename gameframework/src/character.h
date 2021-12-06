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
        SAUT,
        DEPLA_GAUCHE,
        DEPLA_DROITE,
        ATTA_GAUCHE,
        ATTA_DROITE,
        BASE
    };

    void configureAnimation(animation player);

    QPointF m_velocity = QPointF(0,0);
    QPointF getVelocity();
    void updateCharacterVelocity();

    bool isOnFloor = false;
    bool getIsOnFloor();
    void setIsOnFloor(bool _isOnFloor);

    bool isJump = false;
    bool getIsJump();
    void setIsJump(bool _isJump);

    bool isDeath = false;
    bool getIsDeath();
    void setIsDeath(bool _isDeath);

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

     QList<QImage>m_AnimationDeplacementList;
     void setAnimationDeplacementList();
};

#endif // CHARACTER_H
