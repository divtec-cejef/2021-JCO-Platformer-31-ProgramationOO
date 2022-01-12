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
//! \section1 Déplacement d'une entité
//! Une entité peut se mouvoire dans un espace donnée(la scene sur la quelle elle a été assigné).
//! Ses déplacement sont géré par la méthodes updateVelocity() qui modifie la variable m_velocity qui
//! enregistre la vitesse actuel qu'elle a dans la scene.
//! \section2 Mort de l'entité
//! La mort d'une entité consite à renvoyé un booléan qui redéfinit sont état et le détruit de la scene sur la quel il apparait.
//!
class Entity: public Sprite
{
public:

    Entity(const QPixmap& rPixmap, QGraphicsItem* pParent = nullptr);


/*    Entity(const QPixmap& rPixmap, QGraphicsItem* pParent = nullptr,
           QPointF _spawnPoint = QPoint(0.0,0.0));*/

    enum hitSide{
        UP =0,
        DOWN =1,
        RIGHT=2,
        LEFT =3
    };

    virtual void configureAnimation();
    //void uniqueSide(QList<hitSide> collidingSidesList, hitSide appendToSide);

    //Gestion des déplacement
    QPointF m_velocity;
    QPointF m_lastVelocity = m_velocity;
    QPointF getVelocity();
    virtual void updateVelocity();

    bool getIsOnFloor();
    virtual void setIsOnFloor(bool _isOnFloor);

    QPointF m_spawnPoint = QPointF(0,0);
    void setSpawnPoint(QPointF _spawnPoint);
    QPointF getSpawnPoint();


    bool getIsDeath();
    virtual void setIsDeath(bool _isDeath);
    //virtual void setupDeath();


    void setScene(GameScene* m_pScene);

    //Collision
    //virtual void currentCollision();
    virtual void collisionDetection(QRectF rect);

    static void uniqueSide(QList<hitSide>* collidingSidesList, hitSide appendToSide);

    void getCollisionLocate(QList<Entity::hitSide>&collisionLocateL,
                                      QRectF posSprite,QRectF intersected);
    void gravityApplied(long long elapsedTime);

private:

    void setAnimationDeplacementList();

protected:
    GameScene* m_pScene = nullptr;
    QPointF m_gravity = QPointF(0,2);
    bool m_isDeath = false;
    bool m_isOnFloor = false;





};

#endif // ENTITY_H
