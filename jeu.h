#pragma once

#include"tuile.h"
#include <iostream>
#include <string>
using namespace std;

//  CODE DE LA CLASSE :
//	JeuException
//  Jeu

class JeuException {
public:
    JeuException(const string& i) : info(i) {}
    string getInfo() const { return info; }
private:
    string info;
};

//singleton de jeu
class Jeu {  // La class Jeu est responsable du cycle de vie (composition) des tuiles. Le constructeur et le destructeur devront veilleir à allouer et à désallouer la mémoire
    friend class Controleur;
private:
    list<Tuile*> tuiles;
    //const Carte& getTuile(size_t i)const { return tuiles[i]; }; // getTuile en privée pour que seul iterator y est accès
    unsigned int getTaileJeu() const { return tuiles.size(); };

    list<Tuile*>& getListeTuiles() { return tuiles; }
    Jeu(list<Tuile*>& l) { tuiles = l; };
    Jeu& operator= (const Jeu&) = default;
    Jeu(Jeu& jeu) = default; //controleur gère la mémoire
    ~Jeu() = default ;
    Jeu() = default;

    static Jeu* jeuInstance;
    static Jeu& getInstanceJeu();
};
