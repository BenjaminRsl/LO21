#include "mesjoueurs.h"
#include "mesmeeples.h"
#include <QPen>
#include <QPainter>
#include <vector>

//initialisation des constante pour la création du cadre de joueurs
int MesJoueurs::taille_rect_w =300;
int MesJoueurs::taille_rect_h = 100;
int MesJoueurs::x = 0;
int MesJoueurs::y = 200;

//constructeurs de joueurs
MesJoueurs::MesJoueurs(Joueur* j, int i) : joueur(j), id(i), points("Nombre de point :   0"),
    nom(QString::fromStdString(joueur->getNom()))
{
    zone.setRect(x,y+(i*taille_rect_h)+i*10,taille_rect_w,taille_rect_h);
    zone.setBrush(QBrush(QColor(206, 206, 206)));
    zone.setPen(QPen("black"));
    for(vector<Meeple*>::iterator it_meeple = j->getMeeplesJoueur().begin();
        it_meeple != j->getMeeplesJoueur().end(); it_meeple++)
    {
        //création des meeples en fonction de la type
        if((*it_meeple)->getNom()=="Simple")
        {
            meeples.push_back(new Rectangle(j->getCouleur(),*it_meeple));
        }
        if((*it_meeple)->getNom()=="Double")
        {
            meeples.push_back(new Rond(j->getCouleur(),*it_meeple));
        }
        if((*it_meeple)->getNom()=="Abbe")
        {
            meeples.push_back(new Losange(j->getCouleur(),*it_meeple));
        }
    }
}



