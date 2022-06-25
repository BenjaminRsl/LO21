#include "matuile.h"
#include <QPen>
#include <QFlags>

#include <QGraphicsSceneMouseEvent>
#include <QString>
#include "fenetrejeu.h"


QString genimage()
{
    int choix = rand()%28;
    QString chemin(":/tuile");
    QString num= QString ::number(choix, 10 );;
    chemin= chemin + num;
    chemin= chemin + ".jpg";
    return chemin;
}


QString genimage(unsigned int id)
{
    QString chemin(":/tuile");
    QString num= QString ::number(id, 10 );;
    chemin= chemin + num;
    chemin= chemin +".jpg";
    return chemin;
}


MonFondTuile::MonFondTuile() : tuile(nullptr) //: tuile_image() //,tuile_fond()
{
    //a supprimer
    QPixmap image(genimage());
    image=image.scaled(QSize(60,60));
    setPixmap(image);
}

MonFondTuile::MonFondTuile(unsigned int id, Tuile* p_tuile) : tuile(p_tuile)
{
    //a supprimer
    QPixmap image(genimage(id));
    image=image.scaled(QSize(60,60));
    setPixmap(image);
}

void MonFondTuile::mouseReleaseEvent(QGraphicsSceneMouseEvent *em)
{
    int x_milieu= (int) pos().x()+30;
    int y_milieu= (int) pos().y()+30;
    int x = x_milieu - (x_milieu % 60);
    int y = y_milieu - (y_milieu % 60);

    setPos(x,y);
    QGraphicsPixmapItem::mouseReleaseEvent(em);
}

void MonFondTuile::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(event->button() == Qt::RightButton){
        QPixmap pt =(this->pixmap());
        QTransform trans;
        trans=trans.rotate(90);
        this->getTuile().Rotation();
        if(flags()== (QGraphicsPixmapItem::ItemIsSelectable |QGraphicsPixmapItem::ItemIsMovable) ){
            setPixmap(this->pixmap().transformed(trans));
        }

        /*--------- Grisage des espaces possible ---------*/

            Plateau& plateau = fenetrejeu::getControleur().getPlateau();

            for(auto it = MaScene::rectangles_compatibilite.begin() ; it != MaScene::rectangles_compatibilite.end() ; it++ )
            {
                delete (*it);
            }
            MaScene::rectangles_compatibilite.clear();
            for (int y = 0 ; y!= MaScene::taille_bas -1 ; y++)
            {
                for(int x = 0 ; x!= MaScene::taille_grille -1 ; x++)
                {
                        if(fenetrejeu::getControleur().getAction()->estCompatible(plateau,&(MaScene::pioche->getTuile()),y,x))
                        {
                           if((MaScene::pioche->getTuile().tuileAvecRiviere() &&
                               fenetrejeu::getControleur().getAction()->CompatibiliteRiviere(plateau,&(MaScene::pioche->getTuile()),y,x)) ||
                              (! MaScene::pioche->getTuile().tuileAvecRiviere()))
                           {
                            QGraphicsRectItem* rect = new QGraphicsRectItem(x*MaScene::taille_case,y*MaScene::taille_case,60,60);
                            rect->setBrush(QBrush(QColor(220, 220, 220)));
                            rect->setPen(QPen("black"));
                            rect->setZValue(-100);
                            MaScene::rectangles_compatibilite.push_back(rect);
                            fenetrejeu::getScene()->addItem(rect);
                        }
                    }
                }

            }
      }
}



