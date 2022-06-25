#pragma once
#include <list>
#include <iostream>
#include <string>
#include "meeple.h"
#include "lieu.h"
#include "tuile.h"
#include "joueur.h"
#include "plateau.h"

using namespace std;

class Meeple;

// CODE DE LA CLASSE :
//	ExtensionException
//	Extension


/*
------------------------   Execption  ----------------------
*/

class ExtensionException {
public:
    ExtensionException(const string& i) :info(i) {}
    string getInfo() const { return info; }
private:
    string info;
};


/*
------------------------   Extension ----------------------
*/

class Extension
{
protected:
    list<Meeple*> ensembleMeeples;
    list<Lieu*> ensembleLieux;
    list<Tuile*> ensembleTuiles;
    void ajouterMeeple(Meeple* meeple);
    void ajouterLieu(Lieu* lieu);
    void ajouterTuile(Tuile* tuile);
    friend class Controleur;

public:
    list<Meeple*>& getEnsMeeples() { return ensembleMeeples; };
    list<Lieu*>& getEnsLieux()  { return ensembleLieux; };
    list<Tuile*>& getEnsTuiles()  { return ensembleTuiles; };
    //constructeur utile
    Extension() {}

    Extension(Extension& ext):ensembleMeeples(ext.ensembleMeeples), ensembleLieux(ext.ensembleLieux),
        ensembleTuiles(ext.ensembleTuiles)
    {
        std::cout<<"\n ========= Extension copiée =========== \n";
    }

    Extension& operator=(Extension& ext){
        ensembleMeeples = ext.ensembleMeeples;
        ensembleLieux = ext.ensembleLieux;
        ensembleTuiles = ext.ensembleTuiles;
        std::cout << "\n ========= Extension copiée =========== \n";
    }

    //Extension(list<Meeple*> meeples, list<Lieu*> lieux, list<Tuile*> tuiles, list<Regle*> regles);
    //fin constructeur

    virtual ~Extension() {}

    //virtual void afficher();

};


class Classique : public Extension
{
public:
    Classique();
    ~Classique() {
    }
};


class AubergesEtCathedrales : public Extension
{
public:
   AubergesEtCathedrales();
};
