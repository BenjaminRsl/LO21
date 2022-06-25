
#include "meeple.h"

// Classe Meeple


Meeple::Meeple(const std::string& n, const Couleurs c, const Fonctions f, unsigned short int v , unsigned short int nbPoints ):
    nom(n), couleur(c), valeur(v), poser(nullptr), type (f, nbPoints) { }

Meeple::Meeple(const std::string& n, unsigned short int v):
    nom(n), valeur(v), poser(nullptr){};

Meeple::Meeple(const Meeple& m):
    nom(m.nom), valeur(m.valeur), poser(nullptr), type(m.type.get_fonction(),m.type.get_nb_points()){};

void Meeple::afficher()
{
    cout << "Nom : " << nom  << " ; valeur : " << valeur << " ; ";
    switch (couleur) {
    case Couleurs::Bleu: cout << "Couleur : bleu"; break;
    case Couleurs::Blanc: cout << "Couleur : blanc"; break;
    case Couleurs::Rose: cout << "Couleur : rose"; break;
    case Couleurs::Rouge: cout << "Couleur : rouge"; break;
    default: cout << "Couleur : inconnu !"; break;
    }
    cout << "\n";
}
