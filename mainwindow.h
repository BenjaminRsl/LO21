#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QApplication>
#include <QWidget>
#include <QtWidgets/QPushButton>
#include "fenetrenewjoueur.h"
#include "fenetrechoixextensions.h"
#include "fenetrejeu.h"
#include <list>

//  QT
//  CODE DE LA CLASSE :
//	FenetrePrincipale


class FenetrePrincipale : public QWidget
{

    Q_OBJECT
public:
    FenetrePrincipale(QWidget* parent =nullptr);

     list<Joueur*> listeJoueurs;
     list<Extension*> listeExt;
     ~FenetrePrincipale(){}
public slots:
    void AfficherPage1();
    void AfficherPage2();
    void AfficherPage3();

private:

    QPushButton *NewJoueur;

    QPushButton *ChoixExtensions;

    QPushButton *StartPartie;

    QPushButton *Quitter;




};

#endif
