#ifndef CHARACTER_H
#define CHARACTER_H

#include <QObject>
#include <QPointF>

#include <QGraphicsTransform>
#include <QList>

#include <sprite.h>
#include <entity.h>

//!
//! \brief la Classe Character gère le joueur dans une scene
//! Cette classe est permet de crée le personnage que va incarné le joueur.
//! Elle gère les animations du sprite ainsi que ses déplacement dans la scene.
//!
class Character: public Entity
{
public:


    Character(QGraphicsItem* pParent = nullptr);

    //Type d'animation du joueurs
    enum animation{
        BASE = 0,
        DEPLACEMENT = 1,
        SAUT = 3,
        ATTAQUE = 4,
    };

    void configureAnimation(animation player);

    void updateCharacterVelocity();

    void setIsOnFloor(bool _isOnFloor);


    bool getIsJump();
    void setIsJump(bool _isJump);

    void futureCollision();

    //Mort
    void setIsDeath(bool _isDeath);
    //void setupDeath();

    //Compteur de mort(s)
    int getDeathCount();
    void incrementDeathCount();

    void respawn();

public slots:

    void onKeyPressed(int key);
    void onKeyReleased(int key);

private:

    bool m_isJump = false;


    int m_deathCount = 0;

    void configureTransformationMatrix();

    QList<QImage>m_listAnimation;
    void setAnimationDeplacementList();
};

#endif // CHARACTER_H
