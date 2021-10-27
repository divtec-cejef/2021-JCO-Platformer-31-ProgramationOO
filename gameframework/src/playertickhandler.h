/**
  \file
  \brief    Méthodes utilitaires permettant d'accéder aux tick du joueur.
  \author   Léo Küttel
  \date     Novembre 2021
  \version  1.0
*/
#ifndef PLAYERTICKHANDLER_H
#define PLAYERTICKHANDLER_H


#include <QPointF>
#include "spritetickhandler.h"
class PlayerTickHandler : public SpriteTickHandler
{
public:
    PlayerTickHandler(Sprite* pParentSprite = nullptr);
    virtual void init();
    virtual void tick(long long elapsedTimeInMilliseconds);
private:
    int m_playerDirection = 1;
    QPointF m_initialPos;
};
#endif // PLAYERTICKHANDLER_H
