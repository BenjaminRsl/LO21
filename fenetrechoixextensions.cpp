#include "fenetrechoixextensions.h"
#include <QWidget>
#include <QMessageBox>

//Constructeur de la fenetre pour le choix des extensions
FenetreChoixExtensions::FenetreChoixExtensions(QWidget *parent) : QWidget()
{
    //utilisation du parent afin de stocker les valeurs de la page
    FenetrePrincipale * main = dynamic_cast<FenetrePrincipale*>(parent);
     if(main)
        monparent=main;
    //Création des boutons et des cases
    setFixedSize(500, 350);
    Ext_Auberge_et_cathedrales = new QCheckBox("Auberge et cathédrales", this);
    Ext_Auberge_et_cathedrales->setToolTip("Permet de choisir cette extension");
    Ext_Auberge_et_cathedrales->setCursor(Qt::PointingHandCursor);
    Ext_Auberge_et_cathedrales->move(240, 100);
    Ext_Classique = new QCheckBox("Classique", this);
    Ext_Classique->setToolTip("Permet de choisir cette extension");
    Ext_Classique->setCursor(Qt::PointingHandCursor);
    Ext_Classique->move(50, 100);
    Enregistrer = new QPushButton("Enregistrer", this);
    Enregistrer->setToolTip("Permet d'enregistrer un nouveau joueur");
    Enregistrer->setCursor(Qt::PointingHandCursor);
    Enregistrer->move(200, 150);
    Annuler = new QPushButton("Annuler", this);
    Annuler->setToolTip("Annuler");
    Annuler->setCursor(Qt::PointingHandCursor);
    Annuler->move(350, 150);
    QObject::connect(Annuler, SIGNAL(clicked()), this, SLOT(annuler()));
    QObject::connect(Enregistrer, SIGNAL(clicked()), this, SLOT(valider()));
};

//action du bouton valider
void FenetreChoixExtensions::valider()
{
    if(Ext_Classique->isChecked()) // Si ma case Classique est cochée
    {
        Classique* classique = new Classique();
        if(monparent)
        {
            list<Extension*> ext;
            ext.push_back(classique);
            monparent->listeExt.push_back(new Classique(*classique));
            QMessageBox::information(
                        this,
                        tr("Ajout !"),
                        tr("Ajout de l'extension classique"));

        }
        else
        {
            delete classique;
        }
    if(Ext_Auberge_et_cathedrales->isChecked()) //si auberge est cathédrale
    {
        AubergesEtCathedrales* aub = new AubergesEtCathedrales();
        if(monparent)
        {
            monparent->listeExt.push_back(aub);
        }
        else
            delete aub;
       }
    close();
    } // Fin si ma case Classique est cochée
    else //Sinon si m'a case n'est pas coché je lance une fenetre d'erreur
    {
        QMessageBox::information(
                    this,
                    tr("! Erreur !"),
                    tr("Vous devez selectionner au moins l'extension de base...."));
    }
}

//boutons pour annuler la selection du parent concernant les extensions
void FenetreChoixExtensions::annuler()
{
    if(monparent)
    {
        monparent->listeExt.clear();
        QMessageBox::information(
                    this,
                    tr("Message !"),
                    tr("(!) Vous supprimer la liste des extensions  (!)"));
    }
}


