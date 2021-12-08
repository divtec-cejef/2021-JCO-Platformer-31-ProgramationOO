#ifndef ENTITY_H
#define ENTITY_H

#include <QObject>
#include <QPointF>

#include <QGraphicsTransform>
#include <QList>

#include <sprite.h>


class Entity: public Sprite
{
public:

     Entity(const QPixmap& rPixmap, QGraphicsItem* pParent = nullptr);




    void configureAnimation();


    QPointF m_velocity = QPointF(0,0);
    QPointF m_lastVelocity = m_velocity;
    QPointF getVelocity();
    void updateCharacterVelocity();


    bool getIsOnFloor();
    void setIsOnFloor(bool _isOnFloor);


    bool getIsJump();
    void setIsJump(bool _isJump);

     //Mort
    bool getIsDeath();
    void setIsDeath(bool _isDeath);

private:

     bool m_isDeath = false;
     bool m_isOnFloor = false;


     void setAnimationDeplacementList();


};

#endif // ENTITY_H
