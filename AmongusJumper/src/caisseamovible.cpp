/**
  \file
  \brief    Définition de la classe CaisseAmovible.
  @author   LKU
  @date     Janvier 2022
 */
#include "caisseamovible.h"

//Ajoute Supp
#include "utilities.h"
//#include "playertickhandler.h"
#include "sprite.h"
#include "time.h"
#include <QString>
#include "gamescene.h"
#include "gamecanvas.h"
#include "resources.h"

// Vitesse de la caisse
//const int VITESSE_DEPLACEMENT = 5;

CaisseAmovible::CaisseAmovible(QGraphicsItem* pParent) : Entity(GameFramework::imagesPath() + "CaisseV2.png", pParent)
{

}


//!
//! Permet de définir si la caisse est sur le sol ou non.
//! @param _isOnFloor nouvelle état de la caisse.
//!
void CaisseAmovible::setIsOnFloor(bool _isOnFloor){
    this->m_isOnFloor = _isOnFloor;
}


//!
//! Permet de définir si le bulio doit être en vie ou non.
//! @brief caisseAmovible::setIsDeath
//! @param _isDeath nouvelle état du bulio.
//!
void CaisseAmovible::setIsDeath(bool _isDeath){
    this->m_isDeath = _isDeath;
}

void CaisseAmovible::collisionDetection(QRectF rect){

}

void CaisseAmovible::updateVelocity(){

}
