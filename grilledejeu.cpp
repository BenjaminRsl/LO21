#include "grilledejeu.h"
#include  "pioche.h"
#include "controleur.h"
#include "fenetrejeu.h"
#include <QFont>
#include <QMessageBox>

//initialisation des attributs pour le plateau
int MaScene::taille_grille=2;
int MaScene::taille_case=60;
int MaScene::taille_bas=2;


QList<QGraphicsRectItem*> MaScene::rectangles_compatibilite;
MonFondTuile* MaScene::pioche=nullptr;


//action de piocher pour le front
void MaScene::piocher_classique(Controleur& controleur){
/* ------ Création d'une tuile sur la pioche ------  */
    Tuile *t;
     t= controleur.getAction()->piocher(controleur.getPlateau(),controleur.getPioche());
    if(t)
    {
        unsigned int identifiant = t->getId();
        MonFondTuile* tuile=new MonFondTuile(identifiant,t);
        tuile->setPos(taille_case*taille_grille-taille_case+taille_case,140);
        MaScene::pioche=tuile;
        MaScene::pioche->setFlag(QGraphicsPixmapItem::ItemIsMovable,true);
        MaScene::pioche->setFlag(QGraphicsPixmapItem::ItemIsSelectable,true);
        addItem(tuile);

        /*--------- Grisage des espaces possible ---------*/

        Plateau& plateau = fenetrejeu::getControleur().getPlateau();
        plateau.afficherPlateau();
        for(auto it = rectangles_compatibilite.begin() ; it != rectangles_compatibilite.end() ; it++ )
        {
            delete (*it);
        }
        rectangles_compatibilite.clear();
        for (int y = 0 ; y!= taille_bas -1 ; y++)
        {
            for(int x = 0 ; x!= taille_grille -1 ; x++)
            {

                if(fenetrejeu::getControleur().getAction()->estCompatible(plateau,&(MaScene::pioche->getTuile()),y,x))
                {
                   if((MaScene::pioche->getTuile().tuileAvecRiviere() &&
                       fenetrejeu::getControleur().getAction()->CompatibiliteRiviere(plateau,&(MaScene::pioche->getTuile()),y,x)) ||
                      (! MaScene::pioche->getTuile().tuileAvecRiviere()))
                   {
                        QGraphicsRectItem* rect = new QGraphicsRectItem();
                        rect->setRect(x*taille_case,y*taille_case,taille_case,taille_case);
                        rect->setBrush(QBrush(QColor(220, 220, 220)));
                        rect->setPen(QPen("black"));
                        rect->setZValue(-100);
                        rectangles_compatibilite.push_back(rect);
                        addItem(rect);
                     }
                }
            }
        }
    }
    else
    {
        QMessageBox info;
        info.setText("Pioche vide !!");
        info.show();
    }
}

//constructeur de la scène
MaScene::MaScene(QList<MesJoueurs*> list,QObject *parent) : QGraphicsScene(parent),joueurs(list)
{
   setSceneRect(0,0,3000,3000); //Définit la taille de la scène

    /* ------ Grille ------  */
    for(int i=0;i<taille_bas;i++)
    {
        addLine(0,i*taille_case,taille_case*taille_grille-taille_case,i*taille_case, QPen(Qt::gray));

    }
    for(int i=0;i<taille_grille;i++)
    {
        addLine(i*taille_case,0,i*taille_case,taille_bas*taille_case-taille_case,QPen(Qt::gray));
    }

    // Ajout des zones joueurs
    for(auto it = list.begin();it!=list.end();it++)
    {
        addItem(&(*it)->zone);
    }
    //Police
    QFont style;
    style.setStyleHint(QFont::Fantasy);
    style.setPointSize(10);
    //boucle pour positionner les joueurs et les meeples
    int x,y;
    int i;
    int addx,addy;
    int j=0;
    for (auto it = joueurs.begin();it != joueurs.end() ; it++)
    {
        x = (*it)->x;
        y = (*it)->y;
        // Texte pour les points du joueurs
        (*it)->points.setPos(x+10,y+(10+MesJoueurs::taille_rect_h)*j+20);
        (*it)->points.setFont(style);
        addItem(&((*it)->points));
        // Texte pour le nom du joueurs
        (*it)->nom.setPos(x+10,y+(10+MesJoueurs::taille_rect_h)*j);
        (*it)->nom.setFont(style);
        addItem(&((*it)->nom));
        i=1;
        for (auto it2 = (*it)->meeples.begin(); it2!=(*it)->meeples.end()  ; it2++)
        {
            addx=i*20;
            addy=75;
            (*it2)->setPos(x+addx,y+(MesJoueurs::taille_rect_h*j)+addy);

            //ajout de la position du meeple
            Rectangle* rec = dynamic_cast<Rectangle*>(*it2);
            Losange* los = dynamic_cast<Losange*>(*it2);
            Rond* ron = dynamic_cast<Rond*>(*it2);

            if(rec)
            {
                rec->posx = x+addx;
                rec->posy= y+(MesJoueurs::taille_rect_h*j)+addy;
            }
            if(los)
            {
                los->posx = x+addx;
                los->posy= y+(MesJoueurs::taille_rect_h*j)+addy;
            }
            if(ron)
            {
                ron->posx = x+addx;
                ron->posy= y+(MesJoueurs::taille_rect_h*j)+addy;
            }
            addItem(*it2);
            i++;
        }
        j++;
    }
}

//fonction qui va déplacer les meeples et les joueurs quand la taille du plateau augmente
void MaScene::updateSize(int x, int y )
{
    int j=0;
    int i;
    for (auto it = joueurs.begin(); it != joueurs.end() ; it++ )
    {
        (*it)->zone.setRect((*it)->x + x ,(*it)->y + y+(MesJoueurs::taille_rect_h)*j ,(*it)->taille_rect_w,(*it)->taille_rect_h);
        (*it)->points.setPos((*it)->x + x ,(*it)->y + y+(10+MesJoueurs::taille_rect_h)*j+20);
        (*it)->nom.setPos((*it)->x + x ,(*it)->y + y+(10+MesJoueurs::taille_rect_h)*j);
        i=1;
        int a,b;
        for(auto it2 = (*it)->meeples.begin() ; it2 != (*it)->meeples.end() ;it2++)
        {
            a=i*20;
            b=75;
            if((*it2)->pos().y()>=taille_bas*taille_case)
            {
                (*it2)->setPos((*it)->x+a,(*it)->y + y+ (MesJoueurs::taille_rect_h)*j + b);
                //ajout de la position du meeple
                Rectangle* rec = dynamic_cast<Rectangle*>(*it2);
                Losange* los = dynamic_cast<Losange*>(*it2);
                Rond* ron = dynamic_cast<Rond*>(*it2);

                if(rec)
                {

                    rec->posx = (*it)->x+a;
                    rec->posy= (*it)->y + y+ (MesJoueurs::taille_rect_h)*j + b;
                }
                if(los)
                {
                    los->posx = (*it)->x+a;
                    los->posy= (*it)->y + y+ (MesJoueurs::taille_rect_h)*j + b;
                }
                if(ron)
                {
                    ron->posx = (*it)->x+a;
                    ron->posy= (*it)->y + y+ (MesJoueurs::taille_rect_h)*j + b;
                }
            }
            i++;
        }
        j++;
        (*it)->x += x;
        (*it)->y += y;
    }
}

//fonction qui trouve un joueur à partir de son index
MesJoueurs* MaScene::trouver_joueur(int index){
    for (auto it = joueurs.begin(); it != joueurs.end() ; it++ )
    {
        if((*it)->id==index)
            return (*it);
    }
    return nullptr;
}

