#pragma once
#include <fstream>
#include"jeu.h"
#include"pioche.h"
#include"plateau.h"
#include "joueur.h"
#include "memoire.h"
#include "list"
#include "action.h"
#include "extension.h"


// CODE DE LA CLASSE :
//	ExceptionControleur
// Controleur

using namespace std;

class ExceptionControleur
{
public:
    ExceptionControleur(const string& i) :info(i) {}
    string getInfo() const { return info; }
private:
    string info;
};

class Pioche;
class Action;
class Extension;

class Controleur
{
public:

    //get
    Controleur* getContoleur() {return this;}
    Pioche& getPioche() { return *pioche; }
    Plateau& getPlateau() { return plateau; }
    list<Extension*>& getExtension()  { return listeextensions; }
    Jeu& getJeu() { return Jeu::getInstanceJeu(); }
    list<Joueur*>& getListJoueur() { return joueurs; }
    size_t getNbJoueur()const { return joueurs.size(); }
    Action* getAction() {return action;}
    Controleur& operator=(list<Extension*>& extensions );

    const Plateau& getPlateau() const{ return plateau; }
    const list<Joueur*>& getListeJoueur() const { return joueurs; }
    const list<Lieu*>& getListeLieux() const { return lieux;  }
    unsigned int getNbTour() const { return nbTour; }


    Controleur(list<Extension*> extensions);
    Controleur();
    virtual ~Controleur(); //itérateur pour joueur ?
    //Controleur(const Controleur& cont) = delete;
    // utile
    void incrementeTour() { nbTour++; }
    void ajouterJoueur(Joueur& joueur);
    void jouer();

    /*
     * Si on gère la mémoire cependant trop compliqué à lier avec le front
     *
    void restaurer_memoire(unsigned int nbTour);
    void restaurer_memoire_fichier(unsigned int nbTour, string chemin="");
    void sauvegarder();
    void sauvegader_fichier(string chemin);
    */
private:
    // Pour le jeu
    list<Extension*> listeextensions;
    Pioche* pioche;
    unsigned int nbTour;
    Jeu jeu;
    list<Lieu*> lieux;
    Plateau plateau;
    list<Joueur*> joueurs;
    Action* action;


    // Pour la mémoire
    //list<Memoire> historique;

    // initialisation du controleur pour les résaurations de mémoire
    //void setControleur(unsigned int nbTour, list<Tuile> pioche, list<Joueur*> joueurs, list<Extension*> extensions);
    //void setControleur(Memoire memoire);
};

