#include "playertickhandler.h"
#include "spritetickhandler.h"

#include "sprite.h"
#include "gamescene.h"

#include <QDebug>

const int PLAYER_SPEED = 200;

PlayerTickHandler::PlayerTickHandler(Sprite* pParentSprite) : SpriteTickHandler(pParentSprite)
{

}

void PlayerTickHandler::init() {
    m_initialPos = m_pParentSprite->pos();
}
void PlayerTickHandler::tick(long long elapsedTimeInMilliseconds) {

    QPointF spriteMovement = m_spriteVelocity * elapsedTimeInMilliseconds / 1000.;

    // Détermine la prochaine position du sprite
    QRectF nextSpriteRect = m_pParentSprite->globalBoundingBox().translated(spriteMovement);

    // Récupère tous les sprites de la scène que toucherait ce sprite à sa prochaine position
    auto collidingSprites = m_pParentSprite->parentScene()->collidingSprites(nextSpriteRect);

    // Supprimer le sprite lui-même, qui collisionne toujours avec sa boundingbox
    collidingSprites.removeAll(m_pParentSprite);
    bool collision = !collidingSprites.isEmpty();

    // Si les bords sont atteints ou s’il y a collision : le sprite change de direction
    if (m_pParentSprite->right() > m_pParentSprite->parentScene()->width() ||
            m_pParentSprite->left() < 0.0 ||
            collision)
        m_playerDirection *= -1;
}


}
