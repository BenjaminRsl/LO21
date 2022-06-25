#include "pioche.h"
#include <stdlib.h>
#include <ctime>
#include <cstdlib >
#include <string>


unsigned int Pioche::nbResteLieu(const string lieu) {
    //nombre de tuiles dans la pioche qui ont le lieu en question
    unsigned int nb = 0;
    //pour toutes les tuiles de la pioche
    for (auto it = tuiles.begin(); it != tuiles.end(); it++)
    {
        //pour tous les endroits de la tuile
        for (auto it_endroit = (*it)->getListEndroit().begin(); it_endroit != (*it)->getListEndroit().end(); it_endroit++)
        {
            //on veifie le nom du lieu de l'endroit
            if ((*it_endroit)->getLieu()->getLieu() == lieu)
            {
                nb++;
                break;
            }
        }
    }
    return nb;
}

unsigned int Pioche::nbResteSource() {
    //on appele la fonction avec le lieu source
    return Pioche::nbResteLieu("Source");

}

unsigned int Pioche::nbResteRiviere() {
    //on appele la fonction avec le lieu rivière
    return Pioche::nbResteLieu("Riviere");
}

list<Tuile*>& Pioche::listTuileLieu(const string lieu) {
    list<Tuile*> listTuile;
    for (auto it = tuiles.begin(); it != tuiles.end(); it++)
    {
        //pour tous les endroits de la tuile
        for (auto it_endroit = (*it)->getListEndroit().begin(); it_endroit != (*it)->getListEndroit().end(); it_endroit++)
        {
            //on veifie le nom du lieu de l'endroit
            if ((*it_endroit)->getLieu()->getLieu() == lieu)
            {
                listTuile.push_back(*it);
            }
        }
    }
    return listTuile;
}

void Pioche::supTulie(Tuile* t) {
    list<Tuile*>::iterator it = find(getListeTuiles().begin(), getListeTuiles().end(), t);
    if (it == getListeTuiles().end())
        throw PiocheException("erreur la tuile n'est pas trouvée");
    else {
        getListeTuiles().erase(it);
    }

}

