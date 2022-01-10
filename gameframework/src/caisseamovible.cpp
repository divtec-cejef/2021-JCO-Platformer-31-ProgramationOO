#include "caisseamovible.h"

//Ajoute Supp
#include "utilities.h"
#include "playertickhandler.h"
#include "sprite.h"
#include "time.h"
#include <QString>
#include "gamescene.h"
#include "gamecanvas.h"
#include "resources.h"

// Vitesse de la caisse
const int VITESSE_DEPLACEMENT = 5;

caisseAmovible::caisseAmovible(QGraphicsItem* pParent) : Entity(GameFramework::imagesPath() + "CaisseV1.png", pParent)
{

}
