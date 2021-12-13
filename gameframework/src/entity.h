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
    //virtual void setupDeath();


    void setScene(GameScene* m_pScene);

    //Collision
    //virtual void currentCollision();
    virtual void collisionDetection(QRectF rect);

    static void uniqueSide(QList<hitSide>* collidingSidesList, hitSide appendToSide);

private:

    void setAnimationDeplacementList();




protected:
    GameScene* m_pScene = nullptr;
    QPointF m_gravity = QPointF(0,2);
    bool m_isDeath = false;
    bool m_isOnFloor = false;
    void gravityApplied(long long elapsedTime);




};

#endif // ENTITY_H
