#include "entity.h"
#include "character.h"

#include <cmath>
#include <QDebug>
#include <QSettings>

#include "utilities.h"
#include "playertickhandler.h"
#include "sprite.h"
#include "time.h"

//Ajoute Supp
#include <QString>
#include "gamescene.h"
#include "gamecanvas.h"
#include "resources.h"

Entity::Entity(const QPixmap& rPixmap, QGraphicsItem* pParent) : Sprite(pParent)
{

}
