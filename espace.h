#pragma once
#include <list>
#include "tuile.h"
#include <utility>

// CODE DE LA CLASSE :
//	Espace

using namespace std;

class Tuile;
class Endroit;

class Espace
{
public:
    bool estPosable() { return nbMeeples==0; } // est posable s'il le lieu n'est pas pris
    Espace():nbMeeples(0) {};

    void setEspPris(unsigned int nb){nbMeeples=nb;}
    unsigned int incrementNbMeeple(){nbMeeples++; return nbMeeples; }
    list<Tuile*>& getListTuiles();
    list<Endroit*>& getListEndroit();

    void addPaires(list<pair<Tuile*,Endroit*>> liste );
    void addPaire(pair<Tuile*,Endroit*> paire);

    list<pair<Tuile*,Endroit*>>& getPaire(){return paire_tuile_espace;}

private:
    list<pair<Tuile*,Endroit*>> paire_tuile_espace;
    unsigned int nbMeeples;
};


