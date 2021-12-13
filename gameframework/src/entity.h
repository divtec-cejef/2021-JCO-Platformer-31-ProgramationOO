#ifndef ENTITY_H
#define ENTITY_H

#include <QObject>
#include <QPointF>

#include <QGraphicsTransform>
#include <QList>

#include <sprite.h>

//!
//! \brief The Entity class
//! Cette classe est permet de crée une entité et de la géré avec différente méthode.
//! Une entité est un sprite qui à des fonctions qui lui son propre elle peut avoir pluiseur aniamtion,une velocité
//! qui lui est propre.
//!
//!
class Entity: public Sprite
{
public:

     Entity(const QPixmap& rPixmap, QGraphicsItem* pParent = nullptr);

     enum hitSide{
         UP,
         DOWN,
         RIGHT,
         LEFT
     };

    virtual void configureAnimation();
    void uniqueSide(QList<hitSide> collidingSidesList, hitSide appendToSide);

    QPointF m_velocity;
    QPointF m_lastVelocity = m_velocity;
    QPointF getVelocity();
    void updateCharacterVelocity();

    bool getIsOnFloor();
    virtual void setIsOnFloor(bool _isOnFloor);

    bool getIsDeath();
    virtual void setIsDeath(bool _isDeath);

    //Collision
    //virtual void currentCollision();
    virtual void collisionDetection(QRectF rect);

private:
     QPointF m_gravity = QPointF(0,2);
     void setAnimationDeplacementList();
     void gravityApplied(long long elapsedTime);



protected:
     bool m_isDeath = false;
     bool m_isOnFloor = false;


};

#endif // ENTITY_H
