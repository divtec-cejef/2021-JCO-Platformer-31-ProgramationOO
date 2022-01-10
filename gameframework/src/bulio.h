#ifndef BULIO_H
#define BULIO_H

#include <QObject>
#include <QPointF>

#include <QGraphicsTransform>
#include <QList>

#include <sprite.h>
#include <entity.h>

//!
//! \brief la Classe Character gère l'ennemie de base du jeu, dans une scene
//! Cette classe est permet de crée un ennemie se déplaçant de droite à gauche.
//! Elle gère les animations, ses déplacement, les collisions entre elle
//! et les sprites qu'elle touche ainsi que sa propre mort.
//! \section1 Déplacement du Bulio
//! Le Bulio se déplace toujours à droite si il ne rentre pas en collision avec un autre sprite
//! , si telle est le cas le bulio change de dirction et continue à se déplacé dans le sens opposé du sprite
//! touché.
//! Le Bulio est soumis à la gravité si il n'y a pas de sol sous ses pieds il sera attiré en bas de l'écran.
//! \section2 Mort du Bulio
//! Le Bulio peut mourrir de deux manière différente.
//! Soit le joueur touche le bulio sur la partie superieur de son sprite ou alors le Bulio touche le bord de la scene.
class Bulio: public Entity
{
public:
    Bulio(QGraphicsItem* pParent = nullptr);


    //Type d'animation du bulio
    enum animation{
        BASE = 0,
        DEPLACEMENT = 1,
        SAUT = 3,
        ATTAQUE = 4,
    };

    //Configuration des animation du bulio
    void configureAnimation(animation bulio);

    //Gestion des déplacement du Bulio
    void updateVelocity();
    //Définit les déplacement du Bulio dans le jeu.
    void collisionDetection(QRectF rect);
    //void move(long long elapsedTimeInMilliseconds);

    void setIsOnFloor(bool _isOnFloor);


    bool getIsJump();
    void setIsJump(bool _isJump);

    //Définit si le Bulio doit être détruite ou non.
    void setIsDeath(bool _isDeath);

    void respawn();



public slots:

    void onKeyPressed(int key);
    void onKeyReleased(int key);

private:

    bool m_isJump = false;

    void configureTransformationMatrix();

    QList<QImage>m_listAnimation;
    void setAnimationDeplacementList();

};


#endif // BULIO_H
