#include "fabrique.h"

/* ----- Constructeur -----*/

Fabrique::Fabrique(list<Extension*> ext)//:extensions()
{
    //extension.clear()
    for (auto it = ext.begin(); it != ext.end(); it++)
    {
        extensions.push_back(*it);
    }
}


/* ----- Les Fabriques ----- */


Jeu& Fabrique::fabriquerJeu() { //fabrique non utilisé pour le moment !
    Jeu* instance = new Jeu(fabriquerTuile());
    return *instance;
}

list<Meeple*> Fabrique::fabriquerMeeple() {
    list<Meeple*> listeMeeple;
    //list<Meeple*>* listeMeeple = new list<Meeple*>;
    for (auto it = extensions.begin(); it != extensions.end(); it++)
    {
        for(auto it2 = (*it)->getEnsMeeples().begin() ; it2!=(*it)->getEnsMeeples().end();it++)
        {
            listeMeeple.push_back((*it2));
        }
        //listeMeeple.merge((*it)->getEnsMeeples());
    }
    return listeMeeple;
}

list<Tuile*> Fabrique::fabriquerTuile() {
    list<Tuile*>* listeTuile=new list<Tuile*>;
    for (auto it = extensions.begin(); it != extensions.end(); it++)
    {
        for(auto it2 = (*it)->getEnsTuiles().begin() ; it2!=(*it)->getEnsTuiles().end();it++)
        {
            listeTuile->push_back((*it2));
        }
        //listeMeeple.merge((*it)->getEnsMeeples());
    }
    return *listeTuile;
}

list<Lieu*> Fabrique::fabriquerLieu()
{
    list<Lieu*> listeLieu;
    for (auto it = extensions.begin(); it != extensions.end(); it++)
    {
        listeLieu.merge((**it).getEnsLieux());
    }
    return listeLieu;
}

