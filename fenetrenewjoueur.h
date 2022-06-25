#ifndef FENETRENEWJOUEUR_H
#define FENETRENEWJOUEUR_H

#include <QtWidgets/QApplication>
#include <QWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QComboBox>
#include <QStringListModel>
#include <QRadioButton>
#include "mainwindow.h"

//  QT
//  CODE DE LA CLASSE :
//	FenetreNewJoueur

class FenetrePrincipale;

//fenetre pour ajouer les joueurs
class FenetreNewJoueur : public QWidget
{
    Q_OBJECT
public:
    FenetreNewJoueur(QWidget *parent=nullptr);
    FenetrePrincipale* monparent;

private:
    static int nbjoueur;
    QLineEdit *Nom;
    //QLineEdit *Couleur;
    QPushButton *Enregistrer;
    QComboBox *Couleur;
    QPushButton *Annuler;
    QFormLayout *Donnee;
    QStringListModel *ListeC;
    QRadioButton *Radio_IA;

signals:
private slots:
void enregistrer();
void annuler();

};

#endif
