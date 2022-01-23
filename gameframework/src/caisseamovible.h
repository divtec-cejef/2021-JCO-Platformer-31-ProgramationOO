#ifndef CAISSEAMOVIBLE_H
#define CAISSEAMOVIBLE_H

#include <QObject>
#include <QPointF>

#include <QGraphicsTransform>
#include <QList>

#include <sprite.h>
#include <entity.h>

//!
//! \brief The CaisseAmovible class
//! Cette classe hérite de la classe \ref Entity elle permet de géré l'état d'une caisse dans une scene.
//! \section1 Déplacement de la caisse
//! Les déplacement sont géré par la classe \ref CaisseAmovTickHandler.
class CaisseAmovible : public Entity
{
public:
    CaisseAmovible(QGraphicsItem* pParent = nullptr);

    //Gestion des déplacement de la caisse
    void updateVelocity();
    //Définit les déplacement de la caisse dans le jeu.
    void collisionDetection(QRectF rect);

    void setIsOnFloor(bool _isOnFloor);

    //Définit si la caisse doit être détruite ou non.
    void setIsDeath(bool _isDeath);



};

#endif // CAISSEAMOVIBLE_H
