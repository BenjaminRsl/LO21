#include "tuile.h"
#include "espace.h"

list<Tuile*>& Espace::getListTuiles()
{
    list<Tuile*>* result = new list<Tuile*>;
    for(auto it = paire_tuile_espace.begin() ; it != paire_tuile_espace.end() ; it++)
    {
        result->push_back((*it).first);
    }
    return *result;
}

list<Endroit*>& Espace::getListEndroit()
{

    list<Endroit*>* result =  new list<Endroit*>;
    for(auto it = paire_tuile_espace.begin() ; it != paire_tuile_espace.end() ; it++)
    {
        result->push_back((*it).second);
    }
    return *result;
}


void Espace::addPaires(list<pair<Tuile*,Endroit*>> liste)
{
    for(auto it = liste.begin() ; it!= liste.end() ; it++)
    {
        paire_tuile_espace.push_back((*it));
    }
}

void Espace::addPaire(pair<Tuile*,Endroit*> paire )
{
     paire_tuile_espace.push_back(paire);
}
