#pragma once
#include "pioche.h"
#include "plateau.h"
#include "jeu.h"
#include "extension.h"
#include "joueur.h"
#include "controleur.h"

// CODE DE LA CLASSE :
//	Memoire

class Memoire
{
    friend class Controleur;
    friend class Jeu;
private:
    unsigned int nbTour;
    Jeu jeu;
    list<Tuile*> pioche;
    Plateau plateau;
    list<Extension*> extensions;
    list<Joueur*> joueurs;
    list<Lieu*> lieux;

public:
    //Memoire(Controleur& controleur);
    virtual ~Memoire() = default;
    unsigned int getNbTour() { return nbTour; }
};

