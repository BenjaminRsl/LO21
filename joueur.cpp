#include "joueur.h"



/*
------------------------   Joueur  ----------------------
*/


void Joueur::ajouter_meeple(Meeple& meeple)
{
    meeples.push_back(&meeple);
}


Joueur::~Joueur() //libéré les meeples
{
    std::cout << " #######  DESCTUCTION JOUEUR  ####### \n\n";
    for (size_t i = 0; i < meeples.size(); i++)
    {
        delete meeples[i];
    }
}

void Joueur::afficher()
{
    std::cout << " ------- Afichage Joueur ------- \n";
    std::cout << "Nom du joueur  :  "<< nom << "\n";
    /*
    std::cout << "Nombre de points  :  " << points << "\n";
    for (size_t i = 0; i < meeples.size(); i++)
    {
        meeples[i]->afficher();
    }
    */
}

void Joueur::setCouleur_meeple(Couleurs couleur){
    for(auto it = meeples.begin(); it!=meeples.end() ; it++)
    {
        (*it)->setCouleur(couleur);
    }
}





