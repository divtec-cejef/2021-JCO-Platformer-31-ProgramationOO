#ifndef CHARACTER_H
#define CHARACTER_H

#include <QObject>
#include <QPointF>

#include <QGraphicsTransform>
#include <QList>

#include <sprite.h>


class Character
{
public:

    Sprite* m_player;
    Character(Sprite* _player);


    //Type d'animation du joueurs
    enum ANIM_PLAYER{
        SAUT,
        DEPLA_GAUCHE,
        DEPLA_DROITE,
        ATTA_GAUCHE,
        ATTA_DROITE,
        BASE
    };

    void configureAnimation(ANIM_PLAYER animation);


};

#endif // CHARACTER_H
