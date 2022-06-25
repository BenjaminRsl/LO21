#ifndef MATUILE_H
#define MATUILE_H

#include <QGraphicsItem>
#include <QLabel>
#include <QMouseEvent>
#include "tuile.h"


//  QT
//  CODE DE LA CLASSE :
//	MonFondTuile



class MonFondTuile : public QGraphicsPixmapItem//, public QGraphicsPixmapItem
{
public:

    Tuile& getTuile(){return *tuile;}
    MonFondTuile();
    MonFondTuile(unsigned int id, Tuile* p_tuile = nullptr);
    MonFondTuile* getMaTuile(){return this;}
    //QGraphicsPixmapItem* getImage(){return &tuile_image;}

signals:
    void rightClicked();
    void leftClicked();

protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *em);
    void mousePressEvent(QGraphicsSceneMouseEvent *em);

private:
    Tuile* tuile;
};


#endif // MATUILE_H
