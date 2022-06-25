#include "mainwindows.h"
#include "fenetrenewjoueur.h"
#include "fenetrechoixextensions.h"
#include "fenetrejeu.h"
#include<QLabel>
#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QScrollBar>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMainWindow>

FenetrePrincipale::FenetrePrincipale() : QWidget()
{
    setFixedSize(1000, 750);

    NewJoueur = new QPushButton("Ajouter des joueurs", this);

    NewJoueur->setToolTip("Permet d'ajouter un nouveau joueur");
    NewJoueur->setCursor(Qt::PointingHandCursor);
    NewJoueur->move(100, 200);



    QObject::connect(NewJoueur, SIGNAL(clicked()), this, SLOT(AfficherPage1()));

    ChoixExtensions = new QPushButton("Ajouter des extensions", this);

    ChoixExtensions->setToolTip("Permet d'ajouter un nouveau joueur");
    ChoixExtensions->setCursor(Qt::PointingHandCursor);
    ChoixExtensions->move(100, 350);

    QObject::connect(ChoixExtensions, SIGNAL(clicked()), this, SLOT(AfficherPage2()));





    StartPartie = new QPushButton("Démarrer la Partie", this);

    StartPartie->setToolTip("Permet de lancer une Game");
    StartPartie->setCursor(Qt::PointingHandCursor);
    StartPartie->move(100, 500);
    QObject::connect(StartPartie, SIGNAL(clicked()), this, SLOT(AfficherPage3()));





    Quitter = new QPushButton("Quitter", this);

    Quitter->setToolTip("Quitte le programme");
    Quitter->setCursor(Qt::PointingHandCursor);
    Quitter->move(100, 650);

    QObject::connect(Quitter, SIGNAL(clicked()), qApp, SLOT(quit()));

}
void FenetrePrincipale::AfficherPage1()
{
    FenetreNewJoueur *fenetre = new FenetreNewJoueur;
    fenetre->show();
}

void FenetrePrincipale::AfficherPage2()
{
    FenetreChoixExtensions* fenetre = new FenetreChoixExtensions;
    fenetre->show();
}

void FenetrePrincipale::AfficherPage3()
{
    fenetrejeu* fenetre = new fenetrejeu;
    fenetre->show();
}

