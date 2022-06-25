#ifndef MESMEEPLES_H
#define MESMEEPLES_H

#include <QWidget>
#include <QGraphicsRectItem>
#include "joueur.h"
#include "mesjoueurs.h"

//  QT
//  CODE DE LA CLASSE :
//	Rectangle
//  Losange
//  Rond


//Meeple Simple
class Rectangle : public QGraphicsRectItem//, public QGraphicsPixmapItem
{
public:
    QString id="rectangle";
    Rectangle(Couleurs c=Couleurs::SansCouleur, Meeple* m=nullptr);
    Meeple* getMeeple(){return meeple;}
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *em);
    int posx;
    int posy;
signals:
    void rightClicked();
    void leftClicked();
private:
    Meeple* meeple;
};


//Double
class Rond : public QGraphicsEllipseItem
{
public:
    QString id="rond";
    Rond(Couleurs c=Couleurs::SansCouleur, Meeple* m=nullptr);
    Meeple* getMeeple(){return meeple;}
    int posx;
    int posy;
signals:
    void rightClicked();
    void leftClicked();
protected:
       void mouseReleaseEvent(QGraphicsSceneMouseEvent *em);
private:
       Meeple* meeple;
};


//Abbée
class Losange : public QGraphicsPolygonItem
{
public:
    QString id="losange";
    Losange(Couleurs  c=Couleurs::SansCouleur, Meeple* m=nullptr);
    Meeple* getMeeple(){return meeple;}
    int posx;
    int posy;
signals:
    void rightClicked();
    void leftClicked();
protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *em);
private:
    Meeple* meeple;

};



#endif // MESMEEPLES_H
