#pragma once
#include "tuile.h"
#include "memoire.h"
#include "jeu.h"
#include "controleur.h"
#include <string>
#include <list>


//  QT
//  CODE DE LA CLASSE :
//	PiocheException
//  Pioche


using namespace std;

class PiocheException {
public:
    PiocheException(const string& i) : info(i) {}
    string getInfo() const { return info; }
private:
    string info;
};


class Pioche{
private:
    list<Tuile *> tuiles;


public:
    unsigned int getTaillePioche() const { return tuiles.size(); };
    bool estvide() const { return tuiles.empty(); };
    list<Tuile*>& getListeTuiles() { return tuiles; }
    Pioche(const Pioche& pioche) = default;

Pioche& operator=(const Pioche & pioche) = default;

    //piocher !!!

    //a metre dans les actions de l'extession classique
    Tuile* piocherClassique();
    list<Tuile*>& listTuileLieu(const string lieu);
    Tuile* piocher();

    unsigned int nbResteRiviere();
    Tuile* piocherRiviere();
    unsigned int nbResteSource();
    Tuile* piocherSource();

    Tuile* piocherLieu(const string lieu);
    unsigned int nbResteLieu(const string lieu);
    void supTulie(Tuile*);

    //Pioche(Jeu);
    Pioche(list<Tuile*>& l) : tuiles(l) {};
    ~Pioche() = default;
};
