#include "mainwindow.h"
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
#include <QString>
#include <QMessageBox>

//constructeur de la fenetre principale
FenetrePrincipale::FenetrePrincipale(QWidget* parent) : QWidget()
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

//fenetre Joueur
void FenetrePrincipale::AfficherPage1()
{
    FenetreNewJoueur* fenetrejoueur;
    fenetrejoueur = new FenetreNewJoueur(this);
    fenetrejoueur->show();
}

//fenetre extensions
void FenetrePrincipale::AfficherPage2()
{
    FenetreChoixExtensions* fenetreext;
    fenetreext = new FenetreChoixExtensions(this);
    fenetreext->show();
}

//fenetre pour lancer le jeu
void FenetrePrincipale::AfficherPage3()
{
    if(listeExt.empty()){
        QMessageBox::information(
                    this,
                    tr("Alerte !"),
                    tr("(!)   Aucune extension n'a été sélectionnée  (!)"));
    }
    else
    {
        if(listeJoueurs.size()>=2 && listeJoueurs.size()<=4)
        {
            fenetrejeu* fenetre = new fenetrejeu(this);
            fenetre->show();
        }
        else
        {
            QMessageBox::information(
                        this,
                        tr("Alerte !"),
                        tr("(!)  Nombre de joueurs non valide (!)"));

        }
    }
}
