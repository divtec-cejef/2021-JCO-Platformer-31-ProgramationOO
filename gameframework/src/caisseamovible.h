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
    void updateVelocity();
    //Définit les déplacement de la caisse dans le jeu.
    void collisionDetection(QRectF rect);

    void setIsOnFloor(bool _isOnFloor);

    //Définit si la caisse doit être détruite ou non.
    void setIsDeath(bool _isDeath);



};

#endif // CAISSEAMOVIBLE_H
