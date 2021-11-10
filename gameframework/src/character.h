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

    Sprite* SpritePlayer;
    Character(Sprite* _player);
    void setSpritePlayer(Sprite* _SpritePlayer);

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
};

#endif // CHARACTER_H
