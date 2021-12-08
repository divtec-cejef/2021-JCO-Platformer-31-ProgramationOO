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

Entity::Entity(const QPixmap& rPixmap, QGraphicsItem* pParent) : Sprite(rPixmap,pParent)
{

}

void Entity::configureAnimation(){

}

bool Entity::getIsOnFloor(){
    return this->m_isOnFloor;
}

void Entity::setIsOnFloor(bool _isOnFloor){
    this->m_isOnFloor = _isOnFloor;
}

bool Entity::getIsDeath(){
    return this->m_isOnFloor;
}

void Entity::setIsDeath(bool _isOnFloor){
    this->m_isOnFloor = _isOnFloor;
}

