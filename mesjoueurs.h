#ifndef MESJOUEURS_H
#define MESJOUEURS_H
#include <QRect>
#include <QLabel>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include "joueur.h"

//  QT
//  CODE DE LA CLASSE :
//	MesJoueurs


class MesJoueurs
{
public:
    MesJoueurs(Joueur* j = nullptr,int i=0);
    QGraphicsRectItem zone;
    static int taille_rect_w ;
    static int taille_rect_h ;
    static int x;
    static int y;
    Joueur * joueur;
    int id;
    QList<QGraphicsItem*> meeples;
    QGraphicsTextItem points;
    QGraphicsTextItem nom;
};



#endif // MESJOUEURS_H
