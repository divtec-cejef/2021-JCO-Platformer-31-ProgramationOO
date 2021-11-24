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

    void updateCharacterVelocity();


    QPointF m_velocity = QPointF(0,0);
    //void setVelocity(QPointF m_velocity);
    QPointF getVelocity();


    bool isOnFloor = false;
    bool isJump = false;


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
};

#endif // CHARACTER_H
