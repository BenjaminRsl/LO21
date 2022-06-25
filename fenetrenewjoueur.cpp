#include "fenetrenewjoueur.h"
#include <QMessageBox>

//initialisation du nombre de joueur
int FenetreNewJoueur::nbjoueur=0;


FenetreNewJoueur::FenetreNewJoueur(QWidget *parent)
{
    FenetrePrincipale * main = dynamic_cast<FenetrePrincipale*>(parent);
     if(main)
        monparent=main;

    setFixedSize(500, 350);
    Nom = new QLineEdit;
    Couleur = new QComboBox;
    QStringList items;
        items << tr("Blanc") << tr("Bleu") << tr("Rose") << tr("Rouge");
    ListeC = new QStringListModel(items, this);
    Couleur->setModel(ListeC);
    Radio_IA = new QRadioButton;
    Donnee = new QFormLayout;
    Donnee->addRow("Votre Nom", Nom);
    Donnee->addRow("Votre Couleur", Couleur);
    Donnee->addRow("Cocher si IA", Radio_IA);
    setLayout(Donnee);
    //Enregistrement du joueur
    Enregistrer = new QPushButton("Enregistrer", this);
    Enregistrer->setToolTip("Permet d'enregistrer un nouveau joueur");
    Enregistrer->setCursor(Qt::PointingHandCursor);
    Enregistrer->move(250, 150);
    //Annuler
    Annuler = new QPushButton("Supprimer", this);
    Annuler->setToolTip("Supprimer la liste de tous les joueurs");
    Annuler->setCursor(Qt::PointingHandCursor);
    Annuler->move(350, 150);
    QObject::connect(Enregistrer, SIGNAL(clicked()), this, SLOT(enregistrer()));
    QObject::connect(Annuler, SIGNAL(clicked()), this, SLOT(annuler()));

};

//action pouer enregistrer
void FenetreNewJoueur::enregistrer()
{
    if(nbjoueur<4)
    {
        int choix_couleur = Couleur->currentIndex();
        Couleurs ma_couleur;
        switch (choix_couleur) {
        case 0 :
             ma_couleur =Couleurs::Blanc;
            break;
        case 1:
            ma_couleur = Couleurs::Bleu;
            break;
        case 2 :
             ma_couleur =Couleurs::Rose;
             break;
        case 3:
            ma_couleur = Couleurs::Rouge;
            break;
        default:
            throw "Erreur";
        }
        Joueur* newjoueur;
        bool verif = false;
        if( Radio_IA->isChecked())
        {
              if(monparent->listeJoueurs.size()==0)
              {
                  QMessageBox::warning(
                              this,
                              tr("!!  Erreur joueur  !!"),
                              tr(" Le premier joueur ne peut pas être une IA !!! "));
              }
              else
              {
                  newjoueur = new IA(Nom->displayText().toStdString(),ma_couleur);
                  newjoueur->getPoints() = 0;
                  verif = true;
             }

        }
       else
        {
             newjoueur = new Joueur(Nom->displayText().toStdString(),ma_couleur);
             newjoueur->getPoints() = 0;
             verif = true;
        }

        if(monparent && verif){
            monparent->listeJoueurs.push_back(newjoueur);
            QMessageBox::information(
                        this,
                        tr("Nouveau joueur !"),
                        tr("    Nouveau joueur \""+Nom->displayText().toLatin1()+"\" bien ajouté "));
            nbjoueur++;
        }

    }
    else
      {
        QMessageBox::information(
                    this,
                    tr("Alerte !"),
                    tr("(!)  Nombre de joueurs maximum atteint  (!)"));
        close();
    }
}

//action annuler
void FenetreNewJoueur::annuler()
{
    if(monparent)
    {
        monparent->listeJoueurs.clear();
        QMessageBox::information(
                    this,
                    tr("Message !"),
                    tr("(!) Vous supprimer la liste des joueurs  (!)"));
    }
}


