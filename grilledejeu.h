#ifndef GRILLEDEJEU_H
#define GRILLEDEJEU_H

#include <QGraphicsScene>
#include <QObject>
#include <QWidget>

#include "matuile.h"
#include "mesmeeples.h"
#include "controleur.h"
#include "mesjoueurs.h"
#include <QGridLayout>


//  QT
//  CODE DE LA CLASSE :
//	MaScene

//permet de créer la scene où se passe la partie
class MaScene : public QGraphicsScene
{
public:
    explicit MaScene(QList<MesJoueurs*> liste, QObject *parent = nullptr);
    static int taille_grille;
    static int taille_bas;
    static int taille_case;
    QList<MonFondTuile*> plateau;
    static MonFondTuile* pioche;
    QList<MesJoueurs*> joueurs;
    void piocher_classique(Controleur& controleur);
    void updateSize(int x,int y);
    MesJoueurs* trouver_joueur(int index);
    static QList<QGraphicsRectItem*> rectangles_compatibilite;
};

#endif // GRILLEDEJEU_H
