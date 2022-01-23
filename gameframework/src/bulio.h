#ifndef BULIO_H
#define BULIO_H

#include <QObject>
#include <QPointF>

#include <QGraphicsTransform>
#include <QList>

#include <sprite.h>
#include <entity.h>

//!
//! \brief la Classe Bulio gère l'ennemie de base du jeu, dans une scene.
//! Cette classe hérite de la classe \ref Entity elle permet de géré l'état d'une caisse dans une scene.
//! Elle gère les animations ainsi que sa propre mort.
//! \section1 Déplacement du Bulio
//! Les déplacement sont géré par la classe \ref BulioTickHandler.
class Bulio: public Entity
{
public:
    Bulio(QGraphicsItem* pParent = nullptr);

    //Type d'animation du bulio
    enum animation{
        BASE = 0,
        DEPLACEMENT = 1,
    };

    //Configuration des animation du bulio
    void configureAnimation(animation bulio);

    //Définit les déplacement du Bulio dans le jeu.
    void collisionDetection(QRectF rect);
    //void move(long long elapsedTimeInMilliseconds);

    void setIsOnFloor(bool _isOnFloor);

    bool getIsJump();
    void setIsJump(bool _isJump);

    //Définit si le Bulio doit être détruite ou non.
    void setIsDeath(bool _isDeath);

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
