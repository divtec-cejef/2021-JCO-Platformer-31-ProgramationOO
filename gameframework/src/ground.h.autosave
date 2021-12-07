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

    QList<QImage> m_groundImagesList;
    void setGroundImages();

    //! Type d'orientation du sol.
    //! \brief The orientation enum
    //!
    enum orientation{
        GROUND_UP = 0,
        GROUND_DOWN = 1,
        GROUND_LEFT = 2,
        GROUND_RIGHT = 3,
        CORNER_UP_RIGHT = 4,
        CORNER_UP_LEFT = 5,
        CORNER_DOWN_RIGHT = 6,
        CORNER_DOWN_LEFT = 7,
        GROUND_OF_GROUND = 8

    };
    void configureOrientation(orientation orientation, Sprite* &ground);
    void generatorGround(int colonne,int ligne,QPointF posGroupe);

    Ground(QGraphicsItem* pParent = nullptr);
    void configureOrientation(orientation ground);

};

#endif // GROUND_H
