#ifndef FENETREJEU_H
#define FENETREJEU_H

#include <QtWidgets/QApplication>
#include <QWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QFormLayout>
#include <QMainWindow>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGraphicsView>

#include "grilledejeu.h"
#include "mesboutons.h"
#include "matuile.h"
#include "controleur.h"
#include "mainwindow.h"

//  QT
//  CODE DE LA CLASSE :
//	fenetrejeu
//  fenetrepoint


class FenetrePrincipale;


//permet de créer la fenetre de jeu
class fenetrejeu : public QWidget
{
    friend class fenetrepoint;
    Q_OBJECT
public:
    fenetrejeu(QWidget *parent = nullptr);
    virtual ~fenetrejeu();
    void decaler_bas();
    void agrandir_tableau_gauche();
    void agrandir_tableau_bas();
    void decaler_droite();
    static Controleur& getControleur(){return controleur;}
    static MaScene* getScene(){return m_scene;}

private slots: // définir des fonctions visibles par les connections
    void valider_tuile(bool b);
    void valider_tour(bool b);
    void zoomIn(bool b);
    void zoomOut(bool b);

private:
    static int joueurCourrant;
    FenetrePrincipale* monparent;
    static Controleur controleur;
    QGraphicsView* m_view;
    static MaScene* m_scene;
    MesBoutons* btn_valider_tuile;
    MesBoutons* btn_valider_tour;
    MesBoutons* btn_zoomer;
    MesBoutons* btn_dezoomer;
};


//permet de créer la fenetre pour ajouter les points
class fenetrepoint : public QWidget
{
    Q_OBJECT
public:
    fenetrepoint(int c,QWidget *parent = nullptr);

private slots: // définir des fonctions visibles par les connections
    void valider(bool b);

private:
    QLineEdit *Points;
    QFormLayout *Donnee;
    fenetrejeu* monparent;
    QPushButton* btn_valider;
    QString nom;
    QLabel* nbT;
    int courrant;
};


#endif // MAINWINDOWS_H
