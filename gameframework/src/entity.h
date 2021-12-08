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




    virtual void configureAnimation();


    QPointF m_velocity = QPointF(0,0);
    QPointF m_lastVelocity = m_velocity;

    QPointF getVelocity();
    void updateCharacterVelocity();


    bool getIsOnFloor();
    virtual void setIsOnFloor(bool _isOnFloor);


     //Mort
    bool getIsDeath();
    virtual void setIsDeath(bool _isDeath);

private:

     void setAnimationDeplacementList();


protected:
     bool m_isDeath = false;
     bool m_isOnFloor = false;


};

#endif // ENTITY_H
