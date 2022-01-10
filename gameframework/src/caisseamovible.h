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

    //Gestion des déplacement de la caisse
    QPointF getVelocity();
    void updateVelocity();
    //Définit les déplacement de la caisse dans le jeu.
    void collisionDetection(QRectF rect);
    //void move(long long elapsedTimeInMilliseconds);

    bool getIsOnFloor();
    void setIsOnFloor(bool _isOnFloor);

    //Définit si la caisse doit être détruite ou non.
    bool getIsDeath();
    void setIsDeath(bool _isDeath);



};

#endif // CAISSEAMOVIBLE_H
