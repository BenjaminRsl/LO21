#ifndef ACTION_H
#define ACTION_H
#include "controleur.h"
#include "extension.h"
#include "meeple.h"
#include "tuile.h"
#include "plateau.h"
#include "pioche.h"

// CODE DE LA CLASSE :
//	Action
// ActionClassique

class Pioche;
class Action
{
public:
    Action()=default;
    virtual ~Action()=default;

    //action plateau
    virtual bool poserTuile(Plateau& plateau, Tuile* t, unsigned int l, unsigned int c) = 0;
    pair<pair<unsigned int, unsigned int>, unsigned int > choixIA(Plateau& plateau, Tuile* t);
    bool CompatibiliteRiviere(Plateau& plateau,Tuile* t, unsigned int l, unsigned int c);

    //permet de savoir si cette tuile est compatible
    virtual bool estCompatible(Plateau& plateau, Tuile* t, unsigned int l, unsigned int c);

    //fonction pour savoir si on peut poser au moins une tuile
    //permet de savoir s'il faut repiocher une tuile
    bool auMoinsUneTuileCompatible(Plateau& plateau, Tuile* t);


    //fonction pour ajouter une tuile sur le plateau
    //si ce n'est pas possible de la poser la fonction renvoie false
    bool ajouterPlateauVide(Plateau& plateau, Tuile* t);
    bool ajouterClassique(Plateau& plateau, Tuile* t, unsigned int l, unsigned int c);
    bool ajouterGauche(Plateau& plateau, Tuile* t, unsigned int l);
    bool ajouterDroit(Plateau& plateau, Tuile* t, unsigned int l);
    bool ajouterHaut(Plateau& plateau, Tuile* t, unsigned int c);
    bool ajouterBas(Plateau& plateau, Tuile* t, unsigned int c);


    //pioche
    Tuile* piocherClassique(Plateau & plateau, Pioche& pioche); //anciennement piocher
    Tuile* piocherRiviere(Plateau& plateau, Pioche& pioche);
    Tuile* piocherSource(Plateau& plateau, Pioche& pioche);
    Tuile* piocherLieu(Plateau& plateau, Pioche& pioche,const string lieu);
    virtual Tuile* piocher(Plateau& plateau, Pioche& pioche) =0; //anciennement piocherClassique

    //pour poser un meeple
    virtual bool poserMeeple(Plateau& plateau, Meeple& meeple, Tuile& endroit,Cardinal ca, Compatibilite ct) =0;
    virtual bool recupererMeeple(Plateau& plateau, Meeple& meeple)=0;
    virtual bool posableLieux(Meeple& meeple, Endroit& endroit)=0;

};


class ActionClassique : public Action
{
public:
    ActionClassique()=default;
    virtual ~ActionClassique()=default;

    Tuile* piocher(Plateau& plateau, Pioche& pioche) override;
    bool poserMeeple(Plateau& plateau, Meeple& meeple, Tuile& tuile,Cardinal ca, Compatibilite c) override;
    bool poserTuile(Plateau& plateau, Tuile* t, unsigned int l, unsigned int c) override;
    bool recupererMeeple(Plateau& plateau, Meeple& meeple) override;
    bool posableLieux(Meeple& meeple, Endroit& endroit) override;
};

#endif // ACTION_H
