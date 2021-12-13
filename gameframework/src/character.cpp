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

//Type d'animation du joueurs
const int NBR_ANIMATION = 6;

//! spriteSheet animation de marche à gauche/droite
const int FRAME_WIDTH = 60;
const int FRAME_HEIGHT = 60;
const int FRAME_COUNT = 4;
const int COLUMN_COUNT = 2;

struct collisionDistance{
    double top;
    double down;
    double right;
    double left;

};

//!
//! Construit le character du joueur et l'initialise.
//! @brief Character::Character
//! @param   pParent Pointeur sur le parent (afin d'obtenir une destruction automatique de cet objet).
//!
Character::Character(QGraphicsItem* pParent) : Entity(GameFramework::imagesPath() + "BasicPoseV4.png", pParent)
{

}

//!
//! @brief Character::getIsJump
//! @return si le joueur saute.
//!
bool Character::getIsJump(){
    return this->m_isJump;
}

//!
//! Permet de définir si le joueur est entrains de sauter ou non.
//! @brief Character::setIsJump
//! @param _isJump nouvelle état du joueur.
//!
void Character::setIsJump(bool _isJump){
    this->m_isJump = _isJump;
}

//!
//! @brief Character::getIsOnFloor
//! @return si le joueur est sur le sol.
//!
bool Character::getIsOnFloor(){
    return this->m_isOnFloor;
}

//!
//! Permet de définir si le joueur est sur le sol ou non.
//! @brief Character::setIsOnFloor
//! @param _isOnFloor nouvelle état du joueur.
//!
void Character::setIsOnFloor(bool _isOnFloor){
    this->m_isOnFloor = _isOnFloor;
}

//!
//! @brief Character::getIsDeath
//! @return si le joueur est mort.
//!
bool Character::getIsDeath(){
    return this->m_isDeath;
}

//!
//! Permet de définir si le joueur doit être en vie ou non.
//! @brief Character::setIsDeath
//! @param _isDeath nouvelle état du joueur.
//!
void Character::setIsDeath(bool _isDeath){
    this->m_isDeath = _isDeath;
}

int Character::getDeathCount(){
    qDebug() << this->m_deathCount;
    return this->m_deathCount;
}
void Character::incrementDeathCount(){
    this->m_deathCount++;
    qDebug() << "Nombre de mort(s) : " << this->m_deathCount;

}

//!
//! @brief Character::getVelocity
//! @return la velocité actuel du joueur
//!
QPointF Character::getVelocity(){
    return m_velocity;
};

//!
//! Définit l'animation dans la quel le sprite du joueur doit être.
//! @brief Character::configureAnimation
//! @param player animation du joueur paramétrer
//!
void Character::configureAnimation(animation player) {

    clearAnimations();
    QString iSprite;

    switch (player) {
    case DEPLACEMENT:
        iSprite = "MarcheDroiteV9.png";
        break;
    case SAUT:
        iSprite = "SautDroiteV7.png";
        break;
    default:
        iSprite = "BasicPoseV4.png";
        break;
    }

    QImage directionFrame(GameFramework::imagesPath() + iSprite);
    if(iSprite == "MarcheDroiteV9.png"){

        QImage spriteSheet(GameFramework::imagesPath() + iSprite);

        //QList<QImage> listFrame;
        // Découpage de la spritesheet
        for (int frameIndex = 0; frameIndex < FRAME_COUNT; frameIndex++) {
            QImage frameSheet = spriteSheet.copy((frameIndex % COLUMN_COUNT) * FRAME_WIDTH,
                                             (frameIndex / COLUMN_COUNT) * FRAME_HEIGHT,
                                             FRAME_WIDTH, FRAME_HEIGHT);

            //Oriente l'animation selon la velocité du joueur
            if(m_velocity.x() < 0)
                directionFrame = frameSheet.mirrored(true,false);
            else
                directionFrame = frameSheet;

            addAnimationFrame(QPixmap::fromImage(directionFrame.scaled(FRAME_WIDTH * 1,
                                                                        FRAME_HEIGHT * 1,
                                                                        Qt::IgnoreAspectRatio,
                                                                        Qt::SmoothTransformation)));
        }

    }else {
        //Oriente l'animation selon l'actuel ou l'ancienne velocité du joueur
        if(m_velocity.x() < 0 || m_lastVelocity.x() < 0)
            directionFrame = directionFrame.mirrored(true,false);

        addAnimationFrame(QPixmap::fromImage(directionFrame.scaled(FRAME_WIDTH * 1,
                                                                     FRAME_HEIGHT * 1,
                                                                     Qt::IgnoreAspectRatio,
                                                                     Qt::SmoothTransformation)));
    }
    startAnimation(25);
}

//!
//! Reste tout les valeurs du joueur comme elles étaient à leur inisialisation.
//! @brief Character::respawn
//!
void Character::respawn(){

    this->setIsJump(false);
    this->setIsOnFloor(false);
    this->setIsDeath(false);

    QPointF velocityReste = QPointF(0,0);
    this->m_velocity = velocityReste;
}

void Character::setAnimationDeplacementList(){
/*
    QString iSprite;

    switch () {
    case DEPLA_GAUCHE:
        iSprite = "MarcheGaucheV9.png";
        break;
    case DEPLA_DROITE:
        iSprite =  "MarcheDroiteV9.png";
        break;
    case SAUT:
        iSprite = "SautDroiteV7.png";
        break;
    default:
        iSprite = "BasicPoseV4.png";
        break;
    }
    for (int i;i <= NBR_ANIMATION;i++) {

        if(i >= NBR_ANIMATION){
            QImage spriteSheet(GameFramework::imagesPath() + iSprite);

            //iSprite == "MarcheDroiteV9.png" || iSprite == "MarcheGaucheV9.png"
            // Découpage de la spritesheet
            for (int frameIndex = 0; frameIndex < FRAME_COUNT; frameIndex++) {
                QImage CurrentAnimImage = spriteSheet.copy((frameIndex % COLUMN_COUNT) * FRAME_WIDTH,
                                                 (frameIndex / COLUMN_COUNT) * FRAME_HEIGHT,
                                                 FRAME_WIDTH, FRAME_HEIGHT);


                 m_listAnimation.append(CurrentAnimImage);
            }

    }else {
            m_listAnimation.append()
        }

*/
}
/*
void Character::futureCollision(){

    // Détermine la prochaine position du sprite selon sa velwocité
    QRectF nextSpriteRect = this->globalBoundingBox().translated(this->m_velocity);

    if(!this->parentScene()->isInsideScene(nextSpriteRect)){
        qDebug() << "Le joueur est sortit de la scene";
        setupCharacterDeath();
    }

    // Récupère tous les sprites de la scène que toucherait ce sprite à sa prochaine position
    auto listeFuturCollision = this->parentScene()->collidingSprites(nextSpriteRect);
    // Supprime le sprite lui-même, qui collisionne toujours awdvec sa boundingbox
    listeFuturCollision.removeAll(this);

    //récupère la valeur de liste (remplis/vide)
    bool futurCollision = !listeFuturCollision.isEmpty();

    if(futurCollision){
        //Cherche de potentielle futur collisions entre le joueur et les autres sprites
        for (Sprite* CollisionDetected : listeFuturCollision) {

            if (CollisionDetected->data(1) == "sol") {

                if(!this->getIsJump())
                    this->setIsOnFloor(true);

                this->m_velocity.setY(0.0);
                this->setIsJump(false);

                QRectF zoneDeCollision = this->boundingRect().intersected(CollisionDetected->boundingRect());
                qDebug() << "Y collision :" << zoneDeCollision.y();
                qDebug() << "X collision :" << zoneDeCollision.x();

                if(zoneDeCollision.height() < zoneDeCollision.width()){
                      qDebug() << "Collision de haut/bas";
                }else if(zoneDeCollision.height() > zoneDeCollision.width()){
                        qDebug() << "Collision de côté";
                }
            }

            if (CollisionDetected->data(1) == "Piege") {

                if(!this->getIsDeath()){
                    //qDebug() << "HO NON UN PIEGE AHHHH";
                    m_pGameCanvas->getView()->centerOn(CollisionDetected->pos());
                }
                setupCharacterDeath();
            }
        }
    }else {
        this->setIsOnFloor(false);
    }

}

//!
//! Mets en place tout les éléments symbolisant la mort du joueur.
//! @brief GameCore::setupCharacterDeath
//!
void Character::setupDeath(GameScene pScene){
    //Le joueur est considéré comme mort.
    this->setIsDeath(true);
    //Créé le fantôme dans la scene.
    setAnimationDeath();
    //Positionne le fantôme à la place du joueur
    pGhost->setPos(this->pos());
    //Supprime le joueur de la scene.
    m_pScene->removeSpriteFromScene(pCharacter);
    //Ajoute du fantome à la scene.
    m_pScene->addSpriteToScene(pGhost);
    //Ajoute d'une mort au compteur.
    pCharacter->incrementDeathCount();
}
*/

