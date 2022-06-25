#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QApplication>
#include <QWidget>
#include <QtWidgets/QPushButton>

class FenetrePrincipale : public QWidget
{
    Q_OBJECT
public:
    FenetrePrincipale();

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
