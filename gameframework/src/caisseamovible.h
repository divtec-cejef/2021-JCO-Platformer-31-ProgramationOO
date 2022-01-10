#ifndef CAISSEAMOVIBLE_H
#define CAISSEAMOVIBLE_H

#include <QObject>
#include <QPointF>

#include <QGraphicsTransform>
#include <QList>

#include <sprite.h>
#include <entity.h>


class caisseAmovible : public Entity
{
public:
    caisseAmovible(QGraphicsItem* pParent = nullptr);

    QPointF getVelocity();
    void updateVelocity();

    //Définit si la caisse doit être détruite ou non.
    void setIsDeath(bool _isDeath);

    //Définit les déplacement de la caisse dans le jeu.
    //void futureCollision();
    void collisionDetection(QRectF rect);
    void move(long long elapsedTimeInMilliseconds);
};

#endif // CAISSEAMOVIBLE_H
