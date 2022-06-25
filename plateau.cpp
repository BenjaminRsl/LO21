#include <iostream>
#include "plateau.h"
#include "tuile.h"
#include <string>
#include <vector>
#include <iomanip>
using namespace std;


//fonction qui compte le nombre de tuiles sur le plateau
unsigned int Plateau::getNbTuiles() const {
    //on verifie que le tableau n'est pas vide
    if (getTaileLigne() == 0)
        return 0;
    unsigned int nb = 0;
    //on parcours les lignes
    for (unsigned int i = 0;i < getTaileLigne();i++) {
        //on parcours les colonnes
        for (unsigned int j = 0;j < getTaileCol();j++) {
            //on compte la tuile est présente sur le tableau
            if (tuiles[i][j].tuilePresente())
                nb++;
        }
    }
    return nb;
}

//fonction pour afficher un plateau sur a console
void Plateau::afficherPlateau() const {
    cout << "nb ligne:" << getTaileLigne()<<"\n";
    cout << "nb colonne:" << getTaileCol() << "\n";

    //parcours les lignes
    for (unsigned int l = 0;l < getTaileLigne();l++) {
        //parcours des colonnes
        for (unsigned int c = 0;c < getTaileCol();c++) {
            //affichage quand il n'y pas de tuile et qu'on ne peut poser  à cette endroit
            if (!tuiles[l][c].tuilePresente() && !tuiles[l][c].estPosable())
                cout<< setw(6)<<"\\ ";
            //affichage quand il n'y pas de tuile et qu'on peut poser à cette endroit
            if (tuiles[l][c].estPosable())
                cout << setw(6) << "+ ";
            //affichage quand il y une tuile
            if (tuiles[l][c].tuilePresente())
                cout << setw(4) << "T"<< setw(2)<< tuiles[l][c].getTuile()->getId();
        }
        cout << "\n";
    }
}








