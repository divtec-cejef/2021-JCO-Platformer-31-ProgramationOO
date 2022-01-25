/*! \mainpage Amongus-Jumper
 *
 * \author LKU
 *
 * \section Préambule
 * Dans le cadre de l’atelier de 31-Programmation OO enseigné par Jérôme Connus,
 * nous devons réaliser un jeu vidéeo pour testé nos connaissance en c++. Le code sera par la suite évaluée.
 * \section intro_sec Introduction
 * Amongus-Jumper est un jeu vidéo dit Platformer. Un Platformer est un sous-genre du jeux vidéo d’action qui consiste à contrôler un personnage
 * qui doit sauter sur des plateformes dans les airs et éviter des obstacles. vous pouvez retrouvé le code du joueur dans \ref Character ainsi que dans
 * le \ref GameCore.
 * \section Entité
 * les Sprites ayant une vélocité, pouvant être détruit ou étant soumis à la gravité sont considérés comme vivants, et sont donc des entités.
 * Actuellement, il existe trois classes qui découlent de la classe \ref Entity.
 * Les classes \ref Bulio, \ref Character et \ref CaisseAmovible gérant respectivement les ennemis, le joueur et les caisses en bois.
 * \section Gestion des collisions
 * Les collisions sont détectées et utilisées par les entités du jeu. La plupart des entités comme les caisses gèrent leur collision par leur TickHandler()
 * (qui est activé dans le tick() du \ref gamecore).
 * Le TickHandler() va s’occuper des collisions (selon le type d’entité) par anticipation ou par collision actuelle.
 * \subsection  Collision par anticipation
 * La collision par anticipation est utilisée essentiellement pour la gestion de la gravité.
 * Effectivement, on en a besoin pour savoir à l’avance à quel moment l’entité devra être attirée par le bas ou non.
 * Pour ce faire, on utilise la vélocité de l’entité pour savoir si elle va entrer en collision avec la scène ou un élément de celle-ci.
 * On utilise la fonction nextCollision() du \ref TickHandlerEntity.
 * \subsection  Collision actuelle
 * Ce type de collision se produit lors d’un contact direct entre l’entité et un autre sprite.
 * Par exemple, pour savoir si une caisse doit se déplacer, on vérifie si le joueur touche la caisse.
 * \subsection  Collision ciblée
 * Dans ce jeu, on a besoin de savoir de quel côté une entité entre en contact avec un sprite.
 * Pour ce faire, les entités utilisent la méthode \ref getCollisionLocate() qui récupère les valeurs de la fonction \ref intersected()
 * mise à dispositions par Qt. Celle-ci renvoie l'intersection entre les deux rectangles donnés.
 * En l’occurrence, on utilise la bouding Box des deux sprites pour ensuite localiser la zone en contact.
 * \section Annexes
 *  Vous retrouvez plus d'informations dans les 3 PDF dans répertoire doc.
 */

#include "mainfrm.h"

#include <QApplication>

/**
 * @brief main
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainFrm w;
    w.show();

    // Pour un mode d'affichage fenêtré, plein écran
    // w.showMaximized();

    // Pour un mode d'affichage non-fenêtré, plein écran
    // w.showFullScreen();

    return a.exec();
}
