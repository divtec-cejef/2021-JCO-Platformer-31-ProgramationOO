#ifndef GROUND_H
#define GROUND_H

#include <QObject>
#include <QPointF>

#include <QGraphicsTransform>
#include <QList>

#include <sprite.h>

//! la classe Ground permettant de générer automatiquement des groupes de sol en précisant simplement l’emplacement du premier bloc,
//! le nombre de colonnes et de lignes. Cette classe s’occupe de la gestion de l’orientation des blocs,
//! en utilisant une sprite sheet. Actuellement, elle ne peut pas générer des figures complexes.
//! Elle fait uniquement des rectangles et des carrés.
class Ground : public Sprite
{
public:
    Ground(GameScene* CurrentScene);

    //! Type d'orientation possible du sol.
    //! \brief The orientation enum
    //!
    enum orientation{
        GROUND_UP = 0,
        GROUND_DOWN = 1,
        GROUND_LEFT = 2,
        GROUND_RIGHT = 3,
        CORNER_UP_RIGHT = 4,
        CORNER_UP_LEFT = 5,
        CORNER_DOWN_RIGHT = 6,
        CORNER_DOWN_LEFT = 7,
        GROUND_OF_GROUND = 8

    };
    void generated(int colonne,int ligne,QPointF posGroupe);

    void setScene(GameScene* CurrentScene);

    Ground(QGraphicsItem* pParent = nullptr);


private:
    GameScene* m_pScene;
    QList<QImage> m_groundImagesList;
    void setGroundImages();

    void configureOrientation(orientation orientation, Sprite* &ground);
};

#endif // GROUND_H
