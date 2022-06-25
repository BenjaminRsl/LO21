#include "action.h"
#include <algorithm>
#include <stdlib.h>
#include <ctime>
#include <cstdlib >
#include <string>
#include <utility>


/* ------------------------------------ ActionClassique  ------------------------------------*/



//pioche et renvoie un pointeur nullptr si ce n'est pas possible
Tuile* ActionClassique::piocher(Plateau& plateau, Pioche& pioche)
{
    Plateau& pl = plateau;
    Pioche& pi = pioche;
    Tuile* t = nullptr;
    bool aPioche = false;
    if (pi.getTaillePioche() == 0) {
        return nullptr;
    }

    if (pi.nbResteSource() == 2) {

        t = piocherSource(plateau,pioche);
        aPioche = true;
    }
    else
    {
        if (pi.nbResteRiviere() > 1)
        {
            t = piocherRiviere(plateau, pioche);
            aPioche = true;
        }
        else
        {
            if (pi.nbResteSource() == 1) {
                t = piocherSource(plateau, pioche);
                aPioche = true;
            }
            if (aPioche == false) {
                t = piocherClassique(plateau, pioche);
            }
      }
    }
    if (auMoinsUneTuileCompatible(plateau,t)) {
        return t;
    }
    else {
        if(!pioche.estvide())
        {
            return piocher(plateau, pioche);
        }
        else
        {
            return nullptr;
        }
    }
}

//  vérifier si on peut poser un meeple dans le lieux voulu
 bool ActionClassique::posableLieux(Meeple& meeple, Endroit& endroit)
 {
     string lieux = endroit.getLieu()->getLieu();
     if(meeple.getNom()=="Simple" || meeple.getNom()=="Double")
     {
         if(lieux=="Cathedrale" || lieux=="Jardin" || lieux=="Riviere" || lieux=="Source")
         {
            return false;
         }
         else
         {
             if(lieux=="Plaine")
             {
                 meeple.getFonction()=Fonctions::Paysan;
             }
             return true;
         }
     }
     if(meeple.getNom()=="Abbe")
     {
         if(lieux=="Abbaye" || lieux=="Jardin" )
         {
            return true;
         }
         else
         {
             return false;
         }
     }
     return false;
 }


//poser un meeple est renvoie s'il est posable
bool ActionClassique::poserMeeple(Plateau& plateau, Meeple& meeple, Tuile& tuile,Cardinal ca, Compatibilite co)
{

    Endroit* endroit = tuile.getEndroitFromACase(ca, co);


    endroit->afficherCases();

    if(posableLieux(meeple,*endroit))
    {
        if (meeple.estPose() != nullptr)
        {
            return false;
        }

        return true;
        /* à ajouter si on gère les extensions
        else
        {
            if (endroit->getEspace()->estPosable())
            {
                *(meeple.estPose()) = *endroit;
                return true;
            }
            else
            {

                return false;
            }
        }
        */
    }
    return false;

}

//permet de récuperer un meeple
bool ActionClassique::recupererMeeple(Plateau& plateau, Meeple& meeple)
{
    //il faudrait vérifier que l'espace est fini mais ceci fait partie de la complétion automatique en bonus
    if(meeple.getFonction()==Fonctions::Paysan)
    {
        return false;
    }

    meeple.getFonction()=Fonctions::Rien;
    return true;
}

// permet de poser une tuile
bool ActionClassique::poserTuile(Plateau& plateau, Tuile* t, unsigned int l, unsigned int c) {
    Plateau& pl = plateau;

    if (pl.getTaileCol() == 0) {
        return ajouterClassique(plateau,t, l, c);
    }
    if (t->tuileAvecRiviere()) {
        if (CompatibiliteRiviere(plateau,t, l, c))
            return ajouterClassique(plateau,t, l, c);
        else
            return false;
    }
    return ajouterClassique(plateau,t, l, c);
}

/* ------------------------------------ Action  ------------------------------------*/


// piocher des tuiles standards
Tuile* Action::piocherClassique(Plateau& plateau, Pioche& pioche)
{
    Plateau& pl = plateau;
    Pioche& pi = pioche;
    auto it = pi.getListeTuiles().begin();
    //on pioche une tuile au hasard
    //on cherche donc le numero de cette tuile
    // il est compris entre 0 et le nombre de tuile dans la pioche
    srand(time(NULL));
    int choix = rand() % pi.getTaillePioche();

    //iterateur sur le numéro de la tuile a trouver
    int i = 0;

    //tant quon a pas encore piocher la tuile on itérère i
    while (i < choix) {
        it++;
        i++;
    }
        Tuile* tuileRenvoi = *it;
        pi.getListeTuiles().erase(it);
        return tuileRenvoi;
}





Tuile* Action::piocherSource(Plateau& plateau, Pioche& pioche) {
    //on appele la fonction avec le lieu source
    return piocherLieu(plateau, pioche,"Source");
}



//fonction pour savoir si on peut poser au moins une tuile
//permet de savoir s'il faut repiocher une tuile
pair<pair<unsigned int, unsigned int>, unsigned int > Action::choixIA(Plateau& plateau, Tuile* t) {
    Plateau& pl = plateau;

    bool compatible = false;
    unsigned int nligne = pl.getTaileLigne();
    unsigned int ncol = pl.getTaileCol();

    //quand a le plateau vide forcement on peut poser une tuile
    if (nligne == 0 && ncol == 0){
        if (ajouterPlateauVide(plateau,t)) {
            pair<unsigned int, unsigned int> couple(0, 0);
            pair<pair<unsigned int, unsigned int>, unsigned int> triplet(couple, 0);
            return triplet;
        }
        else
            throw "erreur dans ajout plateau vide";
    }



    //on créer une copie de la tuile pour pouvoir faire des
    //rotations sur la tuile sans modifier la tuile de base
    //fait une rotation pour tester toutes les positions de la tuile possible
    for (unsigned int r = 0; r < 4;t->Rotation(),r++) {
        //on parcour les lignes
        for (unsigned int i = 0;i < nligne;i++) {
            //on parcour les colonnes
            for (unsigned int j = 0;j < ncol;j++) {
                //des qu'il y a un emplacement ou l'on peut poser on retourne true
                if (estCompatible(plateau,t, i, j)) {
                    if (t->tuileAvecRiviere()) {
                        if (CompatibiliteRiviere(plateau,t, i, j)) {
                            if (ajouterClassique(plateau,t, i, j)) {
                                pair<unsigned int, unsigned int> couple(i, j);
                                pair<pair<unsigned int, unsigned int>, unsigned int> triplet(couple, r);
                                return triplet;
                            }
                            else
                                throw "probleme ajout IA";

                        }
                    }
                    else {
                        if (ajouterClassique(plateau,t, i, j)) {
                            pair<unsigned int, unsigned int> couple(i, j);
                            pair<pair<unsigned int, unsigned int>, unsigned int> triplet(couple, r);
                            return triplet;
                        }
                        else
                            throw "probleme ajout IA";
                    }
                }
            }
        }
    }
}

bool Action::CompatibiliteRiviere(Plateau& plateau, Tuile* t, unsigned int l, unsigned int c) {
    Plateau& pl = plateau;
    size_t nbLigne = pl.getTaileLigne();
    size_t nbCol = pl.getTaileCol();
    //cas ou il y a des coordonées non adaptées
    if (l >= nbLigne || c >= nbCol)
        return false;
    //cas ou il n'est pas possible de pose la tuile a cette emplacement
    if (!pl.getTuiles()[l][c].estPosable() || pl.getTuiles()[l][c].tuilePresente())
        return false;
    //cas ou il n'y a pas de rivière dans la tuile
    if (!t->tuileAvecRiviere())
        return false;

    list<Cardinal> listCardi1 = t->getListCardianliteRiviere();
    list<Cardinal> listCardi2;

    for (list<Cardinal>::const_iterator it = listCardi1.begin(); it != listCardi1.end(); it++) {
        switch (*it)
        {
        case (N):
            if (l > 0 && pl.getTuiles()[l - 1][c].tuilePresente()) {
                listCardi2 = pl.getTuiles()[l - 1][c].getTuile()->getListCardianliteRiviere();
                if (find(listCardi2.begin(), listCardi2.end(), S) != listCardi2.end())
                    if (pl.getTuiles()[l - 1][c].getTuile()->estCompatible(t, B))
                        return true;
            }
            break;
        case (S):

            if (l < nbLigne - 2 && pl.getTuiles()[l + 1][c].tuilePresente()) {
                listCardi2 = pl.getTuiles()[l + 1][c].getTuile()->getListCardianliteRiviere();
                if (find(listCardi2.begin(), listCardi2.end(), N) != listCardi2.end())
                    if (pl.getTuiles()[l + 1][c].getTuile()->estCompatible(t, H))
                        return true;
            }
            break;
        case(E):
            if (c < nbCol - 2 && pl.getTuiles()[l][c + 1].tuilePresente()) {
                listCardi2 = pl.getTuiles()[l][c + 1].getTuile()->getListCardianliteRiviere();
                if (find(listCardi2.begin(), listCardi2.end(), O) != listCardi2.end())
                    if (pl.getTuiles()[l][c + 1].getTuile()->estCompatible(t, G))
                        return true;
            }
            break;
        case(O):
            if (c > 0 && pl.getTuiles()[l][c - 1].tuilePresente()) {
                listCardi2 = pl.getTuiles()[l][c - 1].getTuile()->getListCardianliteRiviere();
                if (find(listCardi2.begin(), listCardi2.end(), E) != listCardi2.end())
                    if (pl.getTuiles()[l][c - 1].getTuile()->estCompatible(t, D))
                        return true;
            }
            break;
        default:
            break;
        }
    }
    return false;
}



Tuile* Action::piocherRiviere(Plateau& plateau,Pioche& pioche)
{ //pas de vérification s'il reste des tuiles avec le lieu en question car augmenterait la complexité !!
    Plateau& pl = plateau;
    Pioche& pi = pioche;
    int reste = pi.nbResteRiviere();

    //s'il ne reste pas de rivière on ne pas pas piocher de rivière
    if (reste == 0)
    {
        throw " plus de lieu en question !!!\n"; //excpetion pioche !!
    }
    else
    {
        //on cherche a piocher au hasard une tuile avec le lieu en question
        //on cherche donc un numéro aléatoire de la tuile qui va être piochée
        // le numéro est compris entre 0 et le nombre de tuile avec le lieu en question qui reste dans la pioche
        srand(time(NULL));
        int choix = rand() % reste;

        vector<Tuile*> vecTuile;
        for (auto it = pi.getListeTuiles().begin(); it != pi.getListeTuiles().end(); it++)
        {
            //pour tous les endroits de la tuile
            for (auto it_endroit = (*it)->getListEndroit().begin(); it_endroit != (*it)->getListEndroit().end(); it_endroit++)
            {
                //on veifie le nom du lieu de l'endroit
                if ((*it_endroit)->getLieu()->getLieu() == "Riviere")
                {
                    vecTuile.push_back(*it);
                }
            }
        }

        Tuile* tuileRenvoi = vecTuile[choix];

        if (tuileRenvoi->tuileAvecSource())
            if (choix >= reste - 1)
                tuileRenvoi = vecTuile[0];
            else
                tuileRenvoi = vecTuile[choix + 1];
        // on oublie pas de supprimer la tuile qu'on pioche de la pioche
        pi.supTulie(tuileRenvoi);
        return tuileRenvoi;
    }
}


Tuile* Action::piocherLieu(Plateau& plateau, Pioche& pioche, const string lieu)
{ //pas de vérification s'il reste des tuiles avec le lieu en question car augmenterait la complexité !!
    Plateau& pl = plateau;
    Pioche& pi = pioche;
    int reste = pi.nbResteLieu(lieu);
    //s'il ne reste pas de rivière on ne pas pas piocher de rivière
    if (reste == 0)
    {
        throw " plus de lieu en question !!!\n"; //excpetion pioche !!
    }
    else
    {
        //on cherche a piocher au hasard une tuile avec le lieu en question
        //on cherche donc un numéro aléatoire de la tuile qui va être piochée
        // le numéro est compris entre 0 et le nombre de tuile avec le lieu en question qui reste dans la pioche
        srand(time(NULL));
        int choix = rand() % reste;
        //compteur sur le numéro de la tuile qui a le lieu et déja trouvée
        int i = 0;
        bool test = false;

        //parcour toutes les tuiles de la pioche
        for (auto it = pi.getListeTuiles().begin(); it != pi.getListeTuiles().end(); it++)
        {
            //parcour tous les endroit de la tuile
            for (auto it_endroit = (*it)->getListEndroit().begin(); it_endroit != (*it)->getListEndroit().end(); it_endroit++)
            {
                //si l'endroit a le lieu en question
                if ((*it_endroit)->getLieu()->getLieu() == lieu)
                {
                    test = true;
                    //le compteur de tuiles avec le lieu est incrémenté
                    i++;
                    break;
                }
            }
            //si on a trouver le bon nombre de tuile avec le lieu en question
            //fin de la recherche
            if (test && (i > choix)) {
                Tuile* tuileRenvoi = *it;
                if (auMoinsUneTuileCompatible(plateau, tuileRenvoi)) {
                    // on oublie pas de supprimer la tuile qu'on pioche de la pioche
                    pi.getListeTuiles().erase(it);
                    return tuileRenvoi;
                }
                else {
                    return nullptr;
                }
            }
        }
    }
}


//fonction pour ajouter une tuile sur le plateau
//si ce n'est pas possible de la poser la fonction renvoie false
//la fonction crée les espaces et les fuisonnes
bool Action::ajouterClassique(Plateau& plateau, Tuile* t, unsigned int l, unsigned int c) {
    Plateau& pl = plateau;

    unsigned int nligne = pl.getTaileLigne();
    unsigned int ncol = pl.getTaileCol();
    bool compatible = true;

    //cas ou le plateau est vide
    if (nligne == 0 && ncol == 0) {
        //dans 	tous les cas quand un plateau est vide il n'y a pas de verification particulière a faire
        return ajouterPlateauVide(plateau,t);
    }

    //cas ou il y a des coordonées non adaptées
    if (l >= nligne || c >= ncol)
        return false;
    //throw PlateauException("les coordonées sont pas adapté");

//cas ou il n'est pas possible de pose la tuile a cette emplacement
    if (!pl.getTuiles()[l][c].estPosable() || pl.getTuiles()[l][c].tuilePresente())
        return false;
    //throw PlateauException("On ne peut pas posser de tuile sur cette case");

//cas ou l'on pose une tuile sur le bord haut du plateau
//on doit alors ajouter un colonne en haut du plateau
    if (l == 0) {
        return ajouterHaut(plateau,t, c);
    }
    //cas ou l'on pose une tuile sur le bord bas du plateau
    //on doit alors ajouter un colone en bas du plateau
    if (l == nligne - 1) {
        return ajouterBas(plateau,t, c);
    }

    //cas ou l'on pose une tuile sur le bord gauche du plateau
    //on doit alors ajouter un colone a gauche du plateau
    if (c == 0) {
        return ajouterGauche(plateau,t, l);
    }
    //cas ou l'on pose une tuile sur le bord droit du plateau
    //on doit alors ajouter un colone a droite du plateau
    if (c == ncol - 1) {
        return ajouterDroit(plateau,t, l);
    }

    //cas ou l'on a pas besoin d'agrandir le tableau
    //dans ce cas il faut vérifier toutes les cases adjacentes à cette emplacement
    //pour savoir si l'on peut poser la tuile à cet emplacement
    if (c > 0 && l > 0 && c < ncol - 1 && l < nligne - 1) {

        unsigned int nbverf = 0;
        //on verifie qu'il y a une tuile adjacente
        if (pl.getTuiles()[l - 1][c].tuilePresente()) {
            //on verifie que la compatibilité
            if (pl.getTuiles()[l - 1][c].getTuile()->estCompatible(t, B))
                nbverf++;
            else
                compatible = false;
        }
        //on verifie qu'il y a une tuile adjacente
        if (pl.getTuiles()[l + 1][c].tuilePresente()) {
            //on verifie que la compatibilité
            if (pl.getTuiles()[l + 1][c].getTuile()->estCompatible(t, H))
                nbverf++;
            else
                compatible = false;
        }
        //on verifie qu'il y a une tuile adjacente
        if (pl.getTuiles()[l][c - 1].tuilePresente()) {
            //on verifie que la compatibilité
            if (pl.getTuiles()[l][c - 1].getTuile()->estCompatible(t, D))
                nbverf++;
            else
                compatible = false;
        }
        //on verifie qu'il y a une tuile adjacente
        if (pl.getTuiles()[l][c + 1].tuilePresente()) {
            //on verifie que la compatibilité
            if (pl.getTuiles()[l][c + 1].getTuile()->estCompatible(t, G))
                nbverf++;
            else
                compatible = false;
        }
        //on verifie qu'il y a au moins une tuile adjacente qui est compatible
        if (nbverf > 0 && compatible)
        {
            //on inser la tuile à l'endroit souhaité
            vector<Plateau::TuilePlateau>::iterator it = pl.getTuiles()[l].begin();
            for (unsigned int i = 0; i < c; i++)
                it++;
            pl.getTuiles()[l].insert(it, Plateau::TuilePlateau(t));
            vector<Plateau::TuilePlateau>::iterator it2 = pl.getTuiles()[l].begin();
            for (unsigned int i = 0; i < c + 1; i++)
                it2++;
            pl.getTuiles()[l].erase(it2);

            //on ajoute les endroits ou les tuiles sont posables
            pl.getTuiles()[l][c + 1].devientPosable();
            pl.getTuiles()[l + 1][c].devientPosable();
            pl.getTuiles()[l][c - 1].devientPosable();
            pl.getTuiles()[l - 1][c].devientPosable();

            /* Utile si on utiliser les espaces
            //creation et fusion des espaces suites a la pose de la tuile
            //t->creationEspace();
            if (pl.getTuiles()[l][c + 1].tuilePresente())
                if (t->estCompatible((pl.getTuiles()[l][c + 1].getTuile()), D))
                    //t->fusionEspace(pl.getTuiles()[l][c + 1].getTuile(), D);

                    if (pl.getTuiles()[l][c - 1].tuilePresente())
                        if (t->estCompatible((pl.getTuiles()[l][c - 1].getTuile()), G))
                            //t->fusionEspace(pl.getTuiles()[l][c - 1].getTuile(), G);

                            if (pl.getTuiles()[l - 1][c].tuilePresente())
                                if (t->estCompatible((pl.getTuiles()[l - 1][c].getTuile()), H))
                                    //t->fusionEspace(pl.getTuiles()[l-1][c].getTuile(), H);

                                    if (pl.getTuiles()[l + 1][c].tuilePresente())
                                        if (t->estCompatible((pl.getTuiles()[l + 1][c].getTuile()), B));
                                            //t->fusionEspace(pl.getTuiles()[l+1][c].getTuile(), B);
              */

        }
    }
    return compatible;
}


bool Action::ajouterPlateauVide(Plateau& plateau, Tuile* t) {
    Plateau& pl = plateau;


    //on fait des insertion pour avoir un plateau de dimention 3*3
    vector<Plateau::Plateau::TuilePlateau> vec;
    vec.push_back(Plateau::Plateau::TuilePlateau(t));
    pl.getTuiles().push_back(vec);
    pl.getTuiles()[0].push_back(Plateau::TuilePlateau());
    pl.getTuiles()[0].insert(pl.getTuiles()[0].begin(), Plateau::TuilePlateau());
    pl.getTuiles().insert(pl.getTuiles().begin(), vector<Plateau::TuilePlateau>(3, Plateau::TuilePlateau()));
    pl.getTuiles().push_back(vector<Plateau::TuilePlateau>(3, Plateau::TuilePlateau()));

    //on ajoute les endroits ou les tuiles sont posables
    pl.getTuiles()[0][1].devientPosable();
    pl.getTuiles()[1][0].devientPosable();
    pl.getTuiles()[1][2].devientPosable();
    pl.getTuiles()[2][1].devientPosable();
    //t->creationEspace();

    return true;
}


bool Action::ajouterGauche(Plateau& plateau, Tuile* t, unsigned int l) {
    Plateau& pl = plateau;
    unsigned int nligne = pl.getTaileLigne();
    //on verifie la compatibilité de la tuile
    if (pl.getTuiles()[l][1].getTuile()->estCompatible(t, G)) {
        vector<Plateau::TuilePlateau>::iterator it = pl.getTuiles()[0].begin();
        unsigned int i = 0;

        //on insere des emplacement vide
        for (; i < l; i++)
            pl.getTuiles()[i].insert(pl.getTuiles()[i].begin(), Plateau::TuilePlateau());

        //on insere la tuile
        pl.getTuiles()[i].insert(++pl.getTuiles()[i].begin(), Plateau::TuilePlateau(t));

        //on insere des emplacement vide
        for (i++; i < nligne; i++)
            pl.getTuiles()[i].insert(pl.getTuiles()[i].begin(), Plateau::TuilePlateau());

        //on ajoute les endroits ou les tuiles sont posables
        pl.getTuiles()[l - 1][1].devientPosable();
        pl.getTuiles()[l + 1][1].devientPosable();

        //creation et fusion des espaces suites a la pose de la tuile
        //t->creationEspace();
        //t->fusionEspace(pl.getTuiles()[l][2].getTuile(), D);
        return true;
    }
    else
        return false;
}


bool Action::ajouterDroit(Plateau& plateau, Tuile* t, unsigned int l)
{
    Plateau& pl = plateau;
    unsigned int ncol = pl.getTaileCol();
    unsigned int nligne = pl.getTaileLigne();
    //on verifie la compatibilité de la tuile
    if (pl.getTuiles()[l][ncol - 2].getTuile()->estCompatible(t, D)) {
        vector<Plateau::TuilePlateau>::iterator it = pl.getTuiles()[0].begin();
        unsigned int i = 0;

        //on insere des emplacement vide
        for (; i < l; i++)
            pl.getTuiles()[i].push_back(Plateau::TuilePlateau());

        //on insere la tuile
        pl.getTuiles()[i].insert(--pl.getTuiles()[i].end(), Plateau::TuilePlateau(t));

        //on insere des emplacement vide
        for (i++; i < nligne; i++)
            pl.getTuiles()[i].push_back(Plateau::TuilePlateau());

        //on ajoute les endroits ou les tuiles sont posables
        pl.getTuiles()[l - 1][ncol - 1].devientPosable();
        pl.getTuiles()[l + 1][ncol - 1].devientPosable();

        //creation et fusion des espaces suites a la pose de la tuile
        //t->creationEspace();
        //t->fusionEspace(pl.getTuiles()[l][ncol - 2].getTuile(), G);
        return true;
    }
    else
        return false;
}


bool Action::ajouterHaut(Plateau& plateau, Tuile* t, unsigned int c)
{
    Plateau& pl = plateau;
    unsigned int ncol = pl.getTaileCol();
    //on verifie la compatibilité de la tuile
    if (pl.getTuiles()[1][c].getTuile()->estCompatible(t, H)) {

        //on ajoute la tuile à l'emplacement souhaité
        vector<Plateau::TuilePlateau>::iterator it = pl.getTuiles()[0].begin();
        for (unsigned int i = 0; i < c; i++)
            it++;
        pl.getTuiles()[0].insert(it, Plateau::TuilePlateau(t));

        //on suprime la tuile suivante a celle insérée
        vector<Plateau::TuilePlateau>::iterator it2 = pl.getTuiles()[0].begin();
        for (unsigned int i = 0; i < c + 1; i++)
            it2++;
        pl.getTuiles()[0].erase(it2);

        //on ajoute la ligne en haut
        pl.getTuiles().insert(pl.getTuiles().begin(), vector<Plateau::TuilePlateau>(ncol, Plateau::TuilePlateau()));

        //on ajoute les endroits ou les tuiles sont posables
        pl.getTuiles()[0][c].devientPosable();
        pl.getTuiles()[1][c + 1].devientPosable();
        pl.getTuiles()[1][c - 1].devientPosable();

        //creation et fusion des espaces suites a la pose de la tuile
        //t->creationEspace();
        //t->fusionEspace(pl.getTuiles()[2][c].getTuile(), B);
        return true;
    }
    else
        return false;
}


bool Action::ajouterBas(Plateau& plateau, Tuile* t, unsigned int c) {
    Plateau& pl = plateau;
    unsigned int nligne = pl.getTaileLigne();
    unsigned int ncol = pl.getTaileCol();

    unsigned int l = nligne - 1;
    //on verifie la compatibilité de la tuile
    if (pl.getTuiles()[l - 1][c].getTuile()->estCompatible(t, B)) {
        //on ajoute la tuile à l'emplacement souhaité
        vector<Plateau::TuilePlateau>::iterator it = pl.getTuiles()[l].begin();
        for (unsigned int i = 0; i < c; i++)
            it++;
        pl.getTuiles()[l].insert(it, Plateau::TuilePlateau(t));

        vector<Plateau::TuilePlateau>::iterator it2 = pl.getTuiles()[l].begin();
        for (unsigned int i = 0; i < c + 1; i++)
            it2++;
        //on suprime la tuile suivante a celle insérée
        pl.getTuiles()[l].erase(it2);

        //on ajoute la ligne en bas
        pl.getTuiles().push_back(vector<Plateau::TuilePlateau>(ncol, Plateau::TuilePlateau()));

        //on ajoute les endroits ou les tuiles sont posables
        pl.getTuiles()[l + 1][c].devientPosable();
        pl.getTuiles()[l][c + 1].devientPosable();
        pl.getTuiles()[l][c - 1].devientPosable();

        //creation et fusion des espaces suites a la pose de la tuile
        //t->creationEspace();

        //t->fusionEspace(pl.getTuiles()[l - 1][c].getTuile(), H);
        //pl.getTuiles()[l - 1][c].getTuile()->fusionEspace(t, H);
        return true;
    }
    else
        return false;
}


//fonction pour savoir si on peut poser au moins une tuile
//permet de savoir s'il faut repiocher une tuile
bool Action::auMoinsUneTuileCompatible(Plateau& plateau,  Tuile* t) {
    Plateau& pl = plateau;

    unsigned int nligne = pl.getTaileLigne();
    unsigned int ncol = pl.getTaileCol();

    //quand a le plateau vide forcement on peut poser une tuile
    if (nligne == 0 && ncol == 0) {
        return true;
    }
    //on créer une copie de la tuile pour pouvoir faire des
    //rotations sur la tuile sans modifier la tuile de base
   Tuile* tcopie =new Tuile(*t);

    //fait une rotation pour tester toutes les positions de la tuile possible
    for (unsigned int r = 0; r < 4; r++) {
        tcopie->Rotation();
        //on parcour les lignes
        for (unsigned int i = 0; i < nligne; i++) {
            //on parcour les colonnes
            for (unsigned int j = 0; j < ncol; j++) {
                //des qu'il y a un emplacement ou l'on peut poser on retourne true
                if (t->tuileAvecRiviere()) {
                    if (CompatibiliteRiviere(plateau,tcopie, i, j) && estCompatible(plateau, tcopie, i, j))
                        return true;
                }
                else {
                    if (estCompatible(plateau, tcopie, i, j))
                        return true;
                }
            }
        }
    }
    //si aucun emplacement n'est copatible malgre les rotattion de la tuile on renvoie false
    return false;
}


//on verifie que la tuile est compatible (notamment pour savoir ou l'on doit fusioner les espaces)
bool Action::estCompatible(Plateau& plateau, Tuile* t, unsigned int l, unsigned int c) {
    Plateau& pl = plateau;
    unsigned int nligne = pl.getTaileLigne();
    unsigned int ncol = pl.getTaileCol();
    bool compatible = true;
    //cas ou il y a un plateau vide la tuile est forcement compatible
    if (nligne == 0 && ncol == 0) {
        return true;
    }
    //cas ou les dimention sont non adaptées on renvoie false
    if (l >= nligne || c >= ncol)
        return false;

    //cas ou on ne peut pas poser de tuile on revoire false
    if (!pl.getTuiles()[l][c].estPosable())
        return false;

    //cas ou la tuile ajouté est en haut
    if (l == 0) {
        //on verifie la compatibilité de la tuile en bas
        if (pl.getTuiles()[1][c].getTuile()->estCompatible(t, H))
            return true;
        else
            return false;
    }

    //cas ou la tuile ajouté est en bas
    if (l == nligne - 1) {
        //on verifie la compatibilité de la tuile en haut
        if (pl.getTuiles()[l - 1][c].getTuile()->estCompatible(t, B))
            return true;

        else
            return false;
    }
    //cas ou la tuile ajouté est à gauche
    if (c == 0) {
        //on verifie la compatibilité de la tuile à gauche
        if (pl.getTuiles()[l][1].getTuile()->estCompatible(t, G))
            return true;
        else
            return false;
    }

    //cas ou la tuile ajouté est à droite
    if (c == ncol - 1) {
        //on verifie la compatibilité de la tuile à droite
        if (pl.getTuiles()[l][c - 1].getTuile()->estCompatible(t, D))
            return true;
        else
            return false;
    }

    //si l'on est pas passé par les cas précédent on a forcement un emplacement
    //qui n'est pas sur un bord du plateau

    //on veut voir s'il y a au moins une tuile qui est compatible grace a ce compteur
    unsigned int nbverf = 0;

    //si on se rend compte d'une incompatibilité on renvoie directement false
    if (pl.getTuiles()[l - 1][c].tuilePresente()) {
        if (pl.getTuiles()[l - 1][c].getTuile()->estCompatible(t, B))
            nbverf++;
        else
            return false;
    }

    if (pl.getTuiles()[l + 1][c].tuilePresente()) {
        if (pl.getTuiles()[l + 1][c].getTuile()->estCompatible(t, H))
            nbverf++;
        else
            return false;
    }

    if (pl.getTuiles()[l][c - 1].tuilePresente()) {
        if (pl.getTuiles()[l][c - 1].getTuile()->estCompatible(t, D))
            nbverf++;
        else
            return false;
    }

    if (pl.getTuiles()[l][c + 1].tuilePresente()) {
        if (pl.getTuiles()[l][c + 1].getTuile()->estCompatible(t, G))
            nbverf++;
        else
            return false;
    }
    //on sassur qu'au moins une tuile est compatible
    return (nbverf > 0);
}
