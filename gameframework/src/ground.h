#ifndef GROUND_H
#define GROUND_H

#include <QObject>
#include <QPointF>

#include <QGraphicsTransform>
#include <QList>

#include <sprite.h>


class Ground : public Sprite
{
public:



    //Type d'animation du joueurs
    enum orientation{
        GROUND_UP,
        GROUND_DOWN,
        GROUND_LEFT,
        GROUND_RIGHT,
        CORNER_UP_RIGHT,
        CORNER_UP_LEFT,
        CORNER_DOWN_RIGHT,
        CORNER_DOWN_LEFT,
        GROUND_OF_GROUND

    };

    Ground(QGraphicsItem* pParent = nullptr);
    void configureOrientation(orientation ground);

};

#endif // GROUND_H
