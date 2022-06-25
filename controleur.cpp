#include "controleur.h"
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include "mainwindow.h"


/* --- Desctructeur de base du controleur  --- */

Controleur::~Controleur()
{
    for(auto it_extension = listeextensions.begin() ; it_extension != listeextensions.end() ; it_extension++)
    {
        delete (*it_extension);
    }
    delete pioche;
    for(auto it_lieu = lieux.begin() ; it_lieu != lieux.end() ; it_lieu++)
    {
        delete (*it_lieu);
    }
    for(auto it_j = joueurs.begin() ; it_j != joueurs.end() ; it_j++)
    {
        delete (*it_j);
    }
    delete action;
}




/* --- Constructeur de base du controleur  --- */


Controleur& Controleur::operator=(list<Extension*>& extensions ){

    for (list<Extension*>::iterator it = extensions.begin(); it != extensions.end(); it++)
    {
        Controleur::listeextensions.push_back(*it);
    }

    // initialisation du jeu
    for (list<Extension*>::iterator it = extensions.begin(); it != extensions.end(); it++)
    {
        for (list<Tuile*>::iterator it2 = (*it)->ensembleTuiles.begin(); it2 != (*it)->ensembleTuiles.end(); it2++)

        {
            Jeu::getInstanceJeu().getListeTuiles().push_back(*it2);
        }
    }

    //initialisation de la pioche

    pioche = new Pioche(Jeu::getInstanceJeu().getListeTuiles());
    //initialisation des lieux
    for (auto it = extensions.begin(); it != extensions.end(); it++)
    {
        for (auto it2 = (*it)->ensembleLieux.begin(); it2 != (*it)->ensembleLieux.end(); it2++)
        {
            lieux.push_back(*it2);
        }
    }

    return *this;
}


Controleur::Controleur() :
    nbTour(0),action(new ActionClassique()) {}


Controleur::Controleur(list<Extension*> extensions) :
    nbTour(0), action(new ActionClassique())
{

    for (list<Extension*>::iterator it = extensions.begin(); it != extensions.end(); it++)
    {
        Controleur::listeextensions.push_back(*it);
    }

    // initialisation du jeu
    for (list<Extension*>::iterator it = extensions.begin(); it != extensions.end(); it++)
    {
        for (list<Tuile*>::iterator it2 = (*it)->ensembleTuiles.begin(); it2 != (*it)->ensembleTuiles.end(); it2++)

        {
            Jeu::getInstanceJeu().getListeTuiles().push_back(*it2);
        }
    }

    //initialisation de la pioche

    pioche = new Pioche(Jeu::getInstanceJeu().getListeTuiles());

    //initialisation des lieux
    for (auto it = extensions.begin(); it != extensions.end(); it++)
    {
        for (auto it2 = (*it)->ensembleLieux.begin(); it2 != (*it)->ensembleLieux.end(); it2++)
        {
            lieux.push_back(*it2);
        }
    }
}



//ajoute les joueurs et les meeples s'ils sont créés
void Controleur::ajouterJoueur(Joueur& nvJ) {
    if (getNbJoueur() > 4)
        throw ExceptionControleur("Nombre de joueur supérieur au maximum (à savoir 4)");
    else
    {
        nvJ.getMeeplesJoueur().clear();

        for(auto it_e = listeextensions.begin(); it_e != listeextensions.end(); it_e++)
        {
            for(auto it_m = (*it_e)->getEnsMeeples().begin(); it_m != (*it_e)->getEnsMeeples().end(); it_m++)
            {
                (*it_m)->setCouleur(nvJ.getCouleur());
                nvJ.ajouter_meeple((**it_m));
            }
        }
        joueurs.push_back(&nvJ);

    }
}




/* --- Méthode pour l'historique  --- */


/*
void Controleur::setControleur(unsigned int p_nbTour, const Pioche p_pioche, list<Joueur*> p_joueurs, list<Extension*> p_extensions)
{
    fabrique = p_extensions;
    jeu =fabrique.fabriquerTuile();
    extensions.clear();
    joueurs.clear();
    lieux.clear();
    nbTour =p_nbTour;
    pioche = new Pioche(p_pioche);


    //initialisation des listes

    lieux = fabrique.fabriquerLieu();
    for (auto it = p_extensions.begin(); it !=p_extensions.end(); it++)
    {
        extensions.push_back(new Extension(**it));
    }

    for (auto it = p_joueurs.begin(); it != p_joueurs.end(); it++)
    {
        joueurs.push_back(new Joueur(**it));
    }
}


void  Controleur::setControleur(Memoire memoire)
{
    setControleur(memoire.nbTour,memoire.pioche,memoire.joueurs,memoire.extensions);
}


void Controleur::sauvegarder()
{
    //ajout dans l'historique rapide
    historique.push_back(*this);

}

void Controleur::restaurer_memoire(unsigned int nbTour)
{
    bool test = false;
    for (auto it = historique.begin(); it != historique.end(); it++)
    {
        if ((*it).getNbTour() == nbTour)
        {
            test = true;
            setControleur(nbTour, (*it).pioche, (*it).joueurs, (*it).extensions);
        }
    }
    if (test==false)
        throw ExceptionControleur("Impossible de restaurer la mémoire le nombre du tour ne correspond pas\n");
}


void Controleur::restaurer_memoire_fichier(unsigned int nbTour, std::string chemin)
{
    if (chemin == "")
    {
        restaurer_memoire(nbTour);
    }
    else
    {
        ifstream Fichier(chemin, ios::in | ios::binary);
        if (!Fichier)
        {
            throw "Impossible d'ouvrir le fichier";
        }
        Memoire* memoire;
        Fichier.read((char*) memoire, sizeof(Memoire));
        setControleur(*memoire);
        delete memoire;
    }
}
*/
