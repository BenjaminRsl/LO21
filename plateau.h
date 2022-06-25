#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "tuile.h"

using namespace std;



//  CODE DE LA CLASSE :
//	PlateauException
//  Plateau
// Plateau -> TuilePlateau

class PlateauException {
public:
    PlateauException(const string& i) :info(i) {}
    string getInfo() const { return info; }
private:
    string info;
};


class Plateau {
public:
    //Plateau() : tuiles() { tuiles[0][0] = Tuile_plateau(0); };
    /*--- constructeur ---*/
    Plateau()=default;
    Plateau(const Plateau& p);
    //Plateau& operator=(const Plateau& p);
    ~Plateau() = default;

    //classe qui est utile pour le plateau car en plus de stocker la tuile
//on stocke l'information pour si on peur poser une tuile
    class TuilePlateau {
    public:
        /*--- constructeurs ---*/
        TuilePlateau() : tuile(nullptr), posable(0) {};
        TuilePlateau(Tuile* t) : tuile(t), posable(1) {};

        /*--- geteur ---*/
        Tuile* getTuile() const {
            return tuile;
        };

        //savoir si on peut poser une tuile
        bool estPosable() const { return posable == 1 && tuile == nullptr; };
        //savoir s'il y a une tuile sur le plateau
        bool tuilePresente() const { return posable == 1 && tuile != nullptr; };
        //on peut maintenant poser la tuile à cette emplacement
        void devientPosable() { posable = 1; };

    private:
        Tuile* tuile;
        bool posable;
    };

    //fonction pour afficher le plateau sur la console
    void afficherPlateau() const;

    vector<vector<TuilePlateau>>& getTuiles() {
        return tuiles;
    }


    //fonction pour fuisionner tous les espaces après avoir poser une tuile
    //void FusionEspace(Tuile* t, unsigned int l, unsigned int c);

    //permet d'avoir le nombre de lignes du plateau
    unsigned int getTaileLigne() const { return tuiles.size();};
    //permet d'avoir le nombre de colones du plateau
    unsigned int getTaileCol() const { if (tuiles.empty()) return 0; else return tuiles.front().size(); };

    //permet d'avoir le nombre tuiles posés sur le plateau
    unsigned int getNbTuiles() const;


private:
    //on represente le plateau par un vector de vector pour acceder à l'opérateur []
    //on a au final un plateau qui représente un tableau en 2 dimentions
    vector<vector<TuilePlateau>> tuiles;



};
