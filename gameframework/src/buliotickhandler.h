#ifndef BULIOTICKHANDLER_H
#define BULIOTICKHANDLER_H

#include <bulio.h>
#include "entitytickhandler.h"
#include <gamecore.h>
#include "gamescene.h"

//!
//! \brief Cette classe est permet de crée un ennemie se déplaçant de droite à gauche.
//! \section1 Déplacement du Bulio
//! Le Bulio se déplace toujours à droite si il ne rentre pas en collision avec un autre sprite,
//! si telle est le cas le bulio change de dirction et continue à se déplacé dans le sens opposé du sprite
//! touché.
//! Il est soumis à la gravité si il n'y a pas de sol sous ses pieds il sera attiré en bas de l'écran.
//! //! \section2 Mort du Bulio
//! Le Bulio peut mourrir de deux manière différente.
//! Soit le joueur touche le bulio sur la partie superieur de son sprite ou alors le Bulio touche le bord de la scene.
//!
class BulioTickHandler : public EntityTickHandler
{
public:
    BulioTickHandler(Entity* pParentSprite = nullptr,GameCore* newGameCore = nullptr);

    void tick(long long elapsedTimeInMilliseconds);

    void currentCollision();
    void nextCollision();

private:

};

#endif // BULIOTICKHANDLER_H
