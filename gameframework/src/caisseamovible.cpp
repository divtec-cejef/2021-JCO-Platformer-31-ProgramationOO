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
//const int VITESSE_DEPLACEMENT = 5;

caisseAmovible::caisseAmovible(QGraphicsItem* pParent) : Entity(GameFramework::imagesPath() + "CaisseV1.png", pParent)
{

}

//! Permet de savoir si la caisse est sur le sol.
//! @return si la caisse est sur le sol.
//!
bool caisseAmovible::getIsOnFloor(){
    return this->m_isOnFloor;
}

//!
//! Permet de définir si la caisse est sur le sol ou non.
//! @param _isOnFloor nouvelle état de la caisse.
//!
void caisseAmovible::setIsOnFloor(bool _isOnFloor){
    this->m_isOnFloor = _isOnFloor;
}

//!
//! Permet de savoir l'états de la caisse.
//! @return si la caisse est détruite ou non.
//!
bool caisseAmovible::getIsDeath(){
    return this->m_isDeath;
}

//!
//! Permet de définir si le bulio doit être en vie ou non.
//! @brief caisseAmovible::setIsDeath
//! @param _isDeath nouvelle état du bulio.
//!
void caisseAmovible::setIsDeath(bool _isDeath){
    this->m_isDeath = _isDeath;
}

void caisseAmovible::collisionDetection(QRectF rect){

}
