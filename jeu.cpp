#include"jeu.h"
#include "tuile.h"
#include <list>
using namespace std;

//création du singleton
Jeu* Jeu::jeuInstance = nullptr;

Jeu& Jeu::getInstanceJeu()
{
    if(jeuInstance==nullptr){
        jeuInstance= new Jeu();
    }
    return *jeuInstance;
}
