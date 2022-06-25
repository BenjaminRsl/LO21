#ifndef FENETRECHOIXEXTENSIONS_H
#define FENETRECHOIXEXTENSIONS_H

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
#include <QCheckBox>
#include "extension.h"
#include "mainwindow.h"

//  QT
//  CODE DE LA CLASSE :
//	FenetreChoixExtensions

class FenetrePrincipale;

//permet de créer la fenêtre pour le choix des extensions
class FenetreChoixExtensions :  public QWidget
{
    Q_OBJECT
public:
    FenetreChoixExtensions(QWidget *parent =nullptr);
    FenetrePrincipale* monparent;
    ~FenetreChoixExtensions(){}
private:
    QCheckBox *Ext_Auberge_et_cathedrales;
    QCheckBox *Ext_Classique;
    QPushButton *Enregistrer;
    QPushButton *Annuler;

private slots:
    void valider();
    void annuler();

};

#endif
