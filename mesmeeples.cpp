#include "mesmeeples.h"
#include "grilledejeu.h"
#include "fenetrejeu.h"
#include <QPainter>
#include <QDebug>
#include <QPen>
#include <math.h>
#include <QMessageBox>



/* ---------------- MEEPLE SIMPLE  ---------------- */
//constucteur
Rectangle::Rectangle(Couleurs c, Meeple* m) : meeple(m)
{
    setRect(0, 0, 10, 10);
    setPen(QPen(Qt::black));

    switch (c) {
    case Couleurs::Blanc :
        setBrush(QBrush(Qt::white));
        break;
    case Couleurs::Rose :
        setBrush(QBrush(Qt::magenta));
        break;
    case Couleurs::Rouge :
        setBrush(QBrush(Qt::red));
        break;
    case Couleurs::Bleu :
        setBrush(QBrush(Qt::blue));
        break;
    default:
        setBrush(QBrush(Qt::black));
        break;
    }
    setFlag(QGraphicsPixmapItem::ItemIsMovable);
    setFlag(QGraphicsPixmapItem::ItemIsSelectable);
    setZValue(100000000);
}

//permet de reposer le meeple en récupérant les coordonnées
void Rectangle::mouseReleaseEvent(QGraphicsSceneMouseEvent* em)
{
    int x = pos().x();
    int y = pos().y();
    Plateau& plateau = fenetrejeu::getControleur().getPlateau();

    if(this->posy < MaScene::taille_case * MaScene::taille_bas) // si j'ai pas pose
    {   //si il était pas hors de la grille on doit le récupérer

        if(!fenetrejeu::getControleur().getAction()->recupererMeeple(plateau,*getMeeple()))
        {
            QMessageBox* info = new QMessageBox();
            info->setText("Récupérer un paysan n'est pas possible");
            info->show();
            setPos(this->posx,this->posy); //ancienne valeur
            QGraphicsRectItem::mouseReleaseEvent(em);
            return;
        }
    }

    string cardinalite;
    Cardinal car;
    string compatibilite;
    Compatibilite comp;

    int a= 5; //moitier du carrée
    int taille_sous_case = MaScene::taille_case/3;
    int posix = x + a;
    int posiy = y + a;

    int xm = posix /  MaScene::taille_case ;
    int ym = posiy /  MaScene::taille_case ;

    int x_milieu = posix %  MaScene::taille_case ;
    int y_milieu = posiy %  MaScene::taille_case ;
    int positionx = x_milieu % taille_sous_case ;
    int positiony = y_milieu % taille_sous_case ;

    if (x_milieu < taille_sous_case) // NO, O, SO
    {
        if(y_milieu<taille_sous_case)
        {
            if(positiony<positionx)
            {
                car=Cardinal::NO;
                comp=Compatibilite::H;
                cardinalite = "NO";
                compatibilite = "H";
            }
            else
            {
                car=Cardinal::NO;
                comp=Compatibilite::G;
                cardinalite = "NO";
                compatibilite = "G";
            }
        }
        else
        {
            if(y_milieu<2*taille_sous_case)
            {
                car=Cardinal::O;
                comp=Compatibilite::G;
                cardinalite = "O";
                compatibilite = "G";
            }
            else
            {
                if(positiony<-positionx+taille_sous_case)
                {
                    car=Cardinal::SO;
                    comp=Compatibilite::G;
                    cardinalite = "SO";
                    compatibilite = "G";
                }
                else
                {
                    car=Cardinal::SO;
                    comp=Compatibilite::B;
                    cardinalite = "SO";
                    compatibilite = "B";
                }
          }
        }
    }
    else
    {
        if(x_milieu<2*taille_sous_case) // N, C, S
        {
            if(y_milieu<taille_sous_case)
            {
                car=Cardinal::N;
                comp=Compatibilite::H;
                cardinalite = "N";
                compatibilite = "H";
            }
            else
            {
                if(positiony<2*taille_sous_case)
                {
                    car=Cardinal::C;
                    comp=Compatibilite::nul;
                    cardinalite = "C";
                    compatibilite = "nul";
                }
                else
                {
                    car=Cardinal::S;
                    comp=Compatibilite::B;
                    cardinalite = "S";
                    compatibilite = "B";
                }
            }
        }
        else // NE, E, SE
        {
            if(y_milieu<taille_sous_case)
            {
                if(positiony<-positionx+taille_sous_case)
                {
                    car=Cardinal::NE;
                    comp=Compatibilite::H;
                    cardinalite = "NE";
                    compatibilite = "H";
                }
                else
                {
                    car=Cardinal::NE;
                    comp=Compatibilite::D;
                    cardinalite = "NE";
                    compatibilite = "D";
                }
            }
            else
            {
                if(y_milieu<2*taille_sous_case)
                {
                    car=Cardinal::E;
                    comp=Compatibilite::D;
                    cardinalite = "E";
                    compatibilite = "D";
                }
                else
                {
                    if(positiony<positionx)
                    {
                        car=Cardinal::SE;
                        comp=Compatibilite::D;
                        cardinalite = "SE";
                        compatibilite = "D";
                    }
                    else
                    {
                        car=Cardinal::SE;
                        comp=Compatibilite::B;
                        cardinalite = "SE";
                        compatibilite = "B";
                    }
                }
            }
        }
    }
    qDebug()<<QString::fromStdString(cardinalite)<<QString::fromStdString(compatibilite);
    //action de poser
    if(y< (MaScene::taille_bas-2)*MaScene::taille_case && x<MaScene::taille_case * (MaScene::taille_grille-2))
    {
        if(plateau.getTuiles()[ym][xm].tuilePresente())
        {
            Tuile* tuile =  plateau.getTuiles()[ym][xm].getTuile();
            if(fenetrejeu::getControleur().getAction()->poserMeeple(plateau,*getMeeple(),*tuile,car,comp))
            {
                Endroit* endroit = tuile->getEndroitFromACase(car, comp);
                string lieux = endroit->getLieu()->getLieu();
                QString lieu = QString::fromStdString(lieux);
                QMessageBox* info = new QMessageBox();
                info->setText("Ajout du Meeple dans le lieux de type  :  " + lieu);
                info->show();
                this->posx=pos().x();
                this->posy=pos().y();
                setPos(x,y);
                QGraphicsRectItem::mouseReleaseEvent(em);
                return;
            }
            else
            {
                QMessageBox* info = new QMessageBox();
                info->setText("Impossible de poser le meeple ici");
                info->show();
                setPos(this->posx,this->posy); //ancienne valeur
                QGraphicsRectItem::mouseReleaseEvent(em);
                return;
            }
        }
        else
        {
            QMessageBox* info = new QMessageBox();
            info->setText("Impossible de poser le meeple ici");
            info->show();
            setPos(this->posx,this->posy); //ancienne valeur
            QGraphicsRectItem::mouseReleaseEvent(em);
            return;
        }
    }
    setPos(x,y); //ancienne valeur
    QGraphicsRectItem::mouseReleaseEvent(em);
    return;
  }


/* ---------------- MEEPLE DOUBLE  ---------------- */

Rond::Rond(Couleurs c, Meeple* m):meeple(m)
{
    setRect(0, 0, 10, 10);
    setPen(QPen(Qt::black));

    switch (c) {
    case Couleurs::Blanc :
        setBrush(QBrush(Qt::white));
        break;
    case Couleurs::Rose :
        setBrush(QBrush(Qt::magenta));
        break;
    case Couleurs::Rouge :
        setBrush(QBrush(Qt::red));
        break;
    case Couleurs::Bleu :
        setBrush(QBrush(Qt::blue));
        break;
    default:
        setBrush(QBrush(Qt::black));
        break;
    }
    setZValue(100000000);
    setFlag(QGraphicsPixmapItem::ItemIsMovable);
    setFlag(QGraphicsPixmapItem::ItemIsSelectable);
}

void Rond::mouseReleaseEvent(QGraphicsSceneMouseEvent *em)
{
    int x = pos().x();
    int y = pos().y();

    Plateau& plateau = fenetrejeu::getControleur().getPlateau();

    if(this->posy < MaScene::taille_case * MaScene::taille_bas) // si j'ai pas pose
    {   //si il était pas hors de la grille on doit le récupérer

        if(!fenetrejeu::getControleur().getAction()->recupererMeeple(plateau,*getMeeple()))
        {
            QMessageBox* info = new QMessageBox();
            info->setText("Récupérer un paysan n'est pas possible");
            info->show();
            setPos(this->posx,this->posy); //ancienne valeur
            QGraphicsEllipseItem::mouseReleaseEvent(em);
            return;
        }
    }

    string cardinalite;
    Cardinal car;
    string compatibilite;
    Compatibilite comp;

    int a= 5; //moitier du carrée
    int taille_sous_case = MaScene::taille_case/3;
    int posix = x + a;
    int posiy = y + a;

    int xm = posix /  MaScene::taille_case ;
    int ym = posiy /  MaScene::taille_case ;

    int x_milieu = posix %  MaScene::taille_case ;
    int y_milieu = posiy %  MaScene::taille_case ;
    int positionx = x_milieu % taille_sous_case ;
    int positiony = y_milieu % taille_sous_case ;

    if (x_milieu < taille_sous_case) // NO, O, SO
    {
        if(y_milieu<taille_sous_case)
        {
            if(positiony<positionx)
            {
                car=Cardinal::NO;
                comp=Compatibilite::H;
                cardinalite = "NO";
                compatibilite = "H";
            }
            else
            {
                car=Cardinal::NO;
                comp=Compatibilite::G;
                cardinalite = "NO";
                compatibilite = "G";
            }
        }
        else
        {
            if(y_milieu<2*taille_sous_case)
            {
                car=Cardinal::O;
                comp=Compatibilite::G;
                cardinalite = "O";
                compatibilite = "G";
            }
            else
            {
                if(positiony<-positionx+taille_sous_case)
                {
                    car=Cardinal::SO;
                    comp=Compatibilite::G;
                    cardinalite = "SO";
                    compatibilite = "G";
                }
                else
                {
                    car=Cardinal::SO;
                    comp=Compatibilite::B;
                    cardinalite = "SO";
                    compatibilite = "B";
                }
          }
        }
    }
    else
    {
        if(x_milieu<2*taille_sous_case) // N, C, S
        {
            if(y_milieu<taille_sous_case)
            {
                car=Cardinal::N;
                comp=Compatibilite::H;
                cardinalite = "N";
                compatibilite = "H";
            }
            else
            {
                if(positiony<2*taille_sous_case)
                {
                    car=Cardinal::C;
                    comp=Compatibilite::nul;
                    cardinalite = "C";
                    compatibilite = "nul";
                }
                else
                {
                    car=Cardinal::S;
                    comp=Compatibilite::B;
                    cardinalite = "S";
                    compatibilite = "B";
                }
            }
        }
        else // NE, E, SE
        {
            if(y_milieu<taille_sous_case)
            {
                if(positiony<-positionx+taille_sous_case)
                {
                    car=Cardinal::NE;
                    comp=Compatibilite::H;
                    cardinalite = "NE";
                    compatibilite = "H";
                }
                else
                {
                    car=Cardinal::NE;
                    comp=Compatibilite::D;
                    cardinalite = "NE";
                    compatibilite = "D";
                }
            }
            else
            {
                if(y_milieu<2*taille_sous_case)
                {
                    car=Cardinal::E;
                    comp=Compatibilite::D;
                    cardinalite = "E";
                    compatibilite = "D";
                }
                else
                {
                    if(positiony<positionx)
                    {
                        car=Cardinal::SE;
                        comp=Compatibilite::D;
                        cardinalite = "SE";
                        compatibilite = "D";
                    }
                    else
                    {
                        car=Cardinal::SE;
                        comp=Compatibilite::B;
                        cardinalite = "SE";
                        compatibilite = "B";
                    }
                }
            }
        }
    }
    qDebug()<<QString::fromStdString(cardinalite)<<QString::fromStdString(compatibilite);
    //action de poser
    if(y< (MaScene::taille_bas-2)*MaScene::taille_case && x<MaScene::taille_case * (MaScene::taille_grille-2))
    {

        if(plateau.getTuiles()[ym][xm].tuilePresente())
        {
            Tuile* tuile =  plateau.getTuiles()[ym][xm].getTuile();
            if(fenetrejeu::getControleur().getAction()->poserMeeple(plateau,*getMeeple(),*tuile,car,comp))
            {
                Endroit* endroit = tuile->getEndroitFromACase(car, comp);
                string lieux = endroit->getLieu()->getLieu();
                QString lieu = QString::fromStdString(lieux);
                QMessageBox* info = new QMessageBox();
                info->setText("Ajout du Meeple dans le lieux de type  :  " + lieu);
                info->show();
                this->posx=pos().x();
                this->posy=pos().y();
                setPos(x,y);
                QGraphicsEllipseItem::mouseReleaseEvent(em);
                return;
            }
            else
            {
                QMessageBox* info = new QMessageBox();
               info->setText("Impossible de poser le meeple ici sd1");
               info->show();
               setPos(this->posx,this->posy); //ancienne valeur
               QGraphicsEllipseItem::mouseReleaseEvent(em);
               return;
            }
        }
        else
        {
            QMessageBox* info = new QMessageBox();
           info->setText("Impossible de poser le meeple ici sd1");
           info->show();
           setPos(this->posx,this->posy); //ancienne valeur
           QGraphicsEllipseItem::mouseReleaseEvent(em);
           return;
        }
    }
    setPos(x,y);
    QGraphicsEllipseItem::mouseReleaseEvent(em);
    return;
}


/* ---------------- MEEPLE ABBE  ---------------- */


Losange::Losange(Couleurs c, Meeple* m) : meeple(m)
{
    QPolygon polygon;
    polygon << QPoint(0, 6) << QPoint(6, 12) << QPoint(12, 6) << QPoint(6, 0);
    // MaScene.addPolygon(polygon);
    setPolygon(polygon);
    setPen(QPen(Qt::black));

    switch (c) {
    case Couleurs::Blanc :
        setBrush(QBrush(Qt::white));
        break;
    case Couleurs::Rose :
        setBrush(QBrush(Qt::magenta));
        break;
    case Couleurs::Rouge :
        setBrush(QBrush(Qt::red));
        break;
    case Couleurs::Bleu :
        setBrush(QBrush(Qt::blue));
        break;
    default:
        setBrush(QBrush(Qt::black));
        break;
    }

    setZValue(100000000);
    setFlag(QGraphicsPixmapItem::ItemIsMovable);
    setFlag(QGraphicsPixmapItem::ItemIsSelectable);

}


void Losange::mouseReleaseEvent(QGraphicsSceneMouseEvent *em)
{
    int x = pos().x();
    int y = pos().y();


    Plateau& plateau = fenetrejeu::getControleur().getPlateau();

    if(this->posy < MaScene::taille_case * MaScene::taille_bas) // si j'ai pas pose
    {   //si il était pas hors de la grille on doit le récupérer

        if(!fenetrejeu::getControleur().getAction()->recupererMeeple(plateau,*getMeeple()))
        {
            QMessageBox* info = new QMessageBox();
            info->setText("Récupérer un paysan n'est pas possible");
            info->show();
            setPos(this->posx,this->posy); //ancienne valeur
            QGraphicsPolygonItem::mouseReleaseEvent(em);
            return;
        }
    }

    string cardinalite;
    Cardinal car;
    string compatibilite;
    Compatibilite comp;

    int a= 5; //moitier du carrée
    int taille_sous_case = MaScene::taille_case/3;
    int posix = x + a;
    int posiy = y + a;

    int xm = posix /  MaScene::taille_case ;
    int ym = posiy /  MaScene::taille_case ;

    int x_milieu = posix %  MaScene::taille_case ;
    int y_milieu = posiy %  MaScene::taille_case ;
    int positionx = x_milieu % taille_sous_case ;
    int positiony = y_milieu % taille_sous_case ;

    if (x_milieu < taille_sous_case) // NO, O, SO
    {
        if(y_milieu<taille_sous_case)
        {
            if(positiony<positionx)
            {
                car=Cardinal::NO;
                comp=Compatibilite::H;
                cardinalite = "NO";
                compatibilite = "H";
            }
            else
            {
                car=Cardinal::NO;
                comp=Compatibilite::G;
                cardinalite = "NO";
                compatibilite = "G";
            }
        }
        else
        {
            if(y_milieu<2*taille_sous_case)
            {
                car=Cardinal::O;
                comp=Compatibilite::G;
                cardinalite = "O";
                compatibilite = "G";
            }
            else
            {
                if(positiony<-positionx+taille_sous_case)
                {
                    car=Cardinal::SO;
                    comp=Compatibilite::G;
                    cardinalite = "SO";
                    compatibilite = "G";
                }
                else
                {
                    car=Cardinal::SO;
                    comp=Compatibilite::B;
                    cardinalite = "SO";
                    compatibilite = "B";
                }
          }
        }
    }
    else
    {
        if(x_milieu<2*taille_sous_case) // N, C, S
        {
            if(y_milieu<taille_sous_case)
            {
                car=Cardinal::N;
                comp=Compatibilite::H;
                cardinalite = "N";
                compatibilite = "H";
            }
            else
            {
                if(positiony<2*taille_sous_case)
                {
                    car=Cardinal::C;
                    comp=Compatibilite::nul;
                    cardinalite = "C";
                    compatibilite = "nul";
                }
                else
                {
                    car=Cardinal::S;
                    comp=Compatibilite::B;
                    cardinalite = "S";
                    compatibilite = "B";
                }
            }
        }
        else // NE, E, SE
        {
            if(y_milieu<taille_sous_case)
            {
                if(positiony<-positionx+taille_sous_case)
                {
                    car=Cardinal::NE;
                    comp=Compatibilite::H;
                    cardinalite = "NE";
                    compatibilite = "H";
                }
                else
                {
                    car=Cardinal::NE;
                    comp=Compatibilite::D;
                    cardinalite = "NE";
                    compatibilite = "D";
                }
            }
            else
            {
                if(y_milieu<2*taille_sous_case)
                {
                    car=Cardinal::E;
                    comp=Compatibilite::D;
                    cardinalite = "E";
                    compatibilite = "D";
                }
                else
                {
                    if(positiony<positionx)
                    {
                        car=Cardinal::SE;
                        comp=Compatibilite::D;
                        cardinalite = "SE";
                        compatibilite = "D";
                    }
                    else
                    {
                        car=Cardinal::SE;
                        comp=Compatibilite::B;
                        cardinalite = "SE";
                        compatibilite = "B";
                    }
                }
            }
        }
    }
    qDebug()<<QString::fromStdString(cardinalite)<<QString::fromStdString(compatibilite);
    //action de poser
    if(y< (MaScene::taille_bas-2)*MaScene::taille_case && x<MaScene::taille_case * (MaScene::taille_grille-2))
    {

        if(plateau.getTuiles()[ym][xm].tuilePresente())
        {
            Tuile* tuile =  plateau.getTuiles()[ym][xm].getTuile();
            if(fenetrejeu::getControleur().getAction()->poserMeeple(plateau,*getMeeple(),*tuile,car,comp))
            {
                Endroit* endroit = tuile->getEndroitFromACase(car, comp);
                string lieux = endroit->getLieu()->getLieu();
                QString lieu = QString::fromStdString(lieux);
                QMessageBox* info = new QMessageBox();
                info->setText("Ajout du Meeple dans le lieux de type  :  " + lieu);
                info->show();
                this->posx=pos().x();
                this->posy=pos().y();
                setPos(x,y);
                QGraphicsPolygonItem::mouseReleaseEvent(em);
                return;
            }
            else
            {
                QMessageBox* info = new QMessageBox();
               info->setText("Impossible de poser le meeple ici sd1");
               info->show();
               setPos(this->posx,this->posy); //ancienne valeur
               QGraphicsPolygonItem::mouseReleaseEvent(em);
               return;
            }
        }
        else
        {
            QMessageBox* info = new QMessageBox();
           info->setText("Impossible de poser le meeple ici sd1");
           info->show();
           setPos(this->posx,this->posy); //ancienne valeur
           QGraphicsPolygonItem::mouseReleaseEvent(em);
           return;
        }
    }
    setPos(x,y);
    QGraphicsPolygonItem::mouseReleaseEvent(em);
    return;
}

