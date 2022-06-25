#include "tuile.h"
#include <iostream>
using namespace std;

//fonction qui affiche une tuile sur le terminal
void Tuile::afficherTuile() const {
    cout << "la tuile n:" << getId() << "\n";
    for (Tuile::const_iterator it = cbegin();it != cend();it++) {
        cout << "Endroit: " << (*it)->getLieu()->getLieu() << "\n";
        for (Endroit::const_iterator it_case = (*it)->cbegin();it_case != (*it)->cend();it_case++) {
            switch ((*it_case)->getCardinal())
            {
            case NE:
                cout << "NE, ";
                break;
            case N:
                cout << "N, ";
                break;
            case NO:
                cout << "NO, ";
                break;
            case O:
                cout << "0, ";
                break;
            case SO:
                cout << "SO, ";
                break;
            case S:
                cout << "S, ";
                break;
            case SE:
                cout << "SE, ";
                break;
            case E:
                cout << "E, ";
                break;
            default:
                cout << "C, ";
                break;
            }
            switch ((*it_case)->getCompatibilite())
            {
            case D:
                cout << "D, ";
                break;
            case G:
                cout << "G, ";
                break;
            case H:
                cout << "H, ";
                break;
            case B:
                cout << "B, ";
                break;
            default:
                cout << "R, ";
                break;
            }
            cout << rotation << ", ";
            cout << (*it)->getLieu()->getLieu();
            cout << "\n";
        }
        cout << "\n";
    }
}

//fonction pour obtenir le nombre de case de la tuile en fonction de la compatibilité
unsigned int Endroit::nbCaseCompatibilite(Compatibilite c) const {
    //compteur du nombre de cases
    unsigned int i = 0;
    //iterateur sur les endroits de la tuile
    for (Endroit::const_iterator it = cbegin();it != cend();it++)
        if ((*it)->getCompatibilite() == c)
            i++;
    return i;
}

//fonction pour obtenir le nombre de case de la tuile en fonction de la compatibilité Droite
unsigned int Endroit::nbCaseD() const{
    return Endroit::nbCaseCompatibilite(D);
}

//fonction pour obtenir le nombre de case de la tuile en fonction de la compatibilité Gauche
unsigned int Endroit::nbCaseG() const{
    return Endroit::nbCaseCompatibilite(G);
}

//fonction pour obtenir le nombre de case de la tuile en fonction de la compatibilité Haut
unsigned int Endroit::nbCaseH() const{
    return Endroit::nbCaseCompatibilite(H);
}
//fonction pour obtenir le nombre de case de la tuile en fonction de la compatibilité Bas
unsigned int Endroit::nbCaseB() const {
    return Endroit::nbCaseCompatibilite(B);
}



//fonction qui faire une rotation de la tuile vers la droite
void Tuile::Rotation() {
    rotation = (rotation + 1) % 4;
    //iterateur sur les endroits de la tuile
    for (Tuile::iterator it = begin();it != end();it++) {
        //iterateur sur les cases des endroits de la tuile
        for (Endroit::iterator it2 = (*it)->begin();it2 != (*it)->end();it2++) {
            //enfonction de la cardianalité de la tuile
            //on modifie de la cardianalité/cordonné
            switch ((*it2)->getCardinal()) {
            case N:
                it2.setCase(E,D);
                break;
            case NE:
                (*it2)->setCardinal(SE);
                if ((*it2)->getCompatibilite() == H)
                    (*it2)->setCompatibilite(D);
                else
                    (*it2)->setCompatibilite(B);
                break;
            case E:
                (*it2)->setCardinal(S);
                (*it2)->setCompatibilite(B);
                break;
            case SE:
                (*it2)->setCardinal(SO);
                if ((*it2)->getCompatibilite() == D)
                    (*it2)->setCompatibilite(B);
                else
                    (*it2)->setCompatibilite(G);
                break;
            case S:
                (*it2)->setCardinal(O);
                (*it2)->setCompatibilite(G);
                break;
            case SO:
                (*it2)->setCardinal(NO);
                if ((*it2)->getCompatibilite() == B)
                    (*it2)->setCompatibilite(G);
                else
                    (*it2)->setCompatibilite(H);
                break;
            case O:
                (*it2)->setCardinal(N);
                (*it2)->setCompatibilite(H);
                break;
            case NO:
                (*it2)->setCardinal(NE);
                if ((*it2)->getCompatibilite() == G)
                    (*it2)->setCompatibilite(H);
                else
                    (*it2)->setCompatibilite(D);
                break;
            default:
                break;
            }
        }
    }
}


bool Tuile::estCompatible(Tuile* t, Compatibilite c) {
    //verifie que les paramètres sont cohérents
    if (c != D && c != G && c != H && c != B)
    {
        throw TuileException("La compatibilité se fait avec les valeurs H, B, G ou D");
    }
    //en fonction du paramètre on appele la fonction estCompatiblepos avec d'autres paramètres
    switch (c)
    {
        case H:
            return (Tuile::estCompatiblepos(t, H, B, NO, N, NE, SO, S, SE));
            break;
        case D:
            return (Tuile::estCompatiblepos(t, D, G, NE, E, SE, NO, O, SO));
            break;
        case B:
            return (Tuile::estCompatiblepos(t, B,H, SO, S, SE, NO, N, NE));
            break;
        case G:
            return (Tuile::estCompatiblepos(t, G ,D, NO, O, SO, NE, E, SE));
            break;
        default:
            return (false);
            break;
        }
}


bool Tuile::estCompatiblepos(Tuile* t, const Compatibilite comp1, const Compatibilite comp2, const Cardinal pos1_1, const Cardinal pos1_2, const Cardinal pos1_3, const Cardinal pos2_1, const Cardinal pos2_2, const Cardinal pos2_3) {
    unsigned int nb_case_comp = 0;
    //iterateur sur les endroits de la tuile de la methode
    for (Tuile::const_iterator it_endroit1 = cbegin(); it_endroit1 != cend(); it_endroit1++)
    {
        //iterateur sur les endroits de la tuile en paramètre
        for (Tuile::const_iterator it_endroit2 = t->cbegin(); it_endroit2 != t->cend(); it_endroit2++)
        {
            //iterateur sur les cases de la tuile de la methode
            for (Endroit::const_iterator it1 = (*it_endroit1)->cbegin();it1 != (*it_endroit1)->cend();it1++) {
                //iterateur sur les cases de la tuile en paramètre
                for (Endroit::const_iterator it2 = (*it_endroit2)->cbegin();it2 != (*it_endroit2)->cend();it2++) {
                    //test sur les compatibilités et cardinalités passées en paramètre
                    if ((*it1)->getCompatibilite() == comp1 && (*it1)->getCardinal() == pos1_1) {
                        if ((*it2)->getCompatibilite() == comp2 && (*it2)->getCardinal() == pos2_1) {
                            if ((*it_endroit1)->getLieu()->getLieu() == (*it_endroit2)->getLieu()->getLieu()) {
                                nb_case_comp++;
                            }
                            //quand les lieux sont pas les mêmes on sait directement que les tuiles ne sont pas compatibles
                            else
                                return false;
                        }
                    }
                    //test sur les compatibilités et cardinalités passées en paramètre
                    if ((*it1)->getCompatibilite() == comp1 && (*it1)->getCardinal() == pos1_2)
                        if ((*it2)->getCompatibilite() == comp2 && (*it2)->getCardinal() == pos2_2) {
                            if ((*it_endroit1)->getLieu()->getLieu() == (*it_endroit2)->getLieu()->getLieu()) {
                                nb_case_comp++;
                            }
                            //quand les lieux sont pas les mêmes on sait directement que les tuiles ne sont pas compatibles
                            else
                                return false;
                        }
                    //test sur les compatibilités et cardinalités passées en paramètre
                    if ((*it1)->getCompatibilite() == comp1 && (*it1)->getCardinal() == pos1_3)
                        if ((*it2)->getCardinal() == pos2_3 && (*it2)->getCompatibilite() == comp2) {
                            if ((*it_endroit1)->getLieu()->getLieu() == (*it_endroit2)->getLieu()->getLieu()) {
                                nb_case_comp++;
                            }
                            //quand les lieux sont pas les mêmes on sait directement que les tuiles ne sont pas compatibles
                            else
                                return false;
                        }
                }
            }
        }
    }
    //on s'assure qu'il y eu quand même une case de chaque tuile qui a un lieu de compatible
    return nb_case_comp > 0;
}

bool Endroit::estCompatibleEspace_sens(Endroit e, Compatibilite compatibilite) const {
    //en fonction du paramètre on appele estCompatibleEspace avec des paramètres différents
    switch (compatibilite)
    {
    case H:
        if (nbCaseH() > 0 && e.nbCaseB() <= nbCaseH())
            return estCompatibleEspace(e, H, B, NO, N, NE, SO, S, SE);
        else
            return false;
        break;
    case B:
        if (nbCaseB() > 0 && e.nbCaseH() <= nbCaseB())
            return estCompatibleEspace(e, B, H, SO, S, SE, NO, N, NE);
        else
            return false;
        break;
    case G:
        if (nbCaseG() > 0 && e.nbCaseD() <= nbCaseG())
            return estCompatibleEspace(e, G, D, NO, O, SO, NE, E, SE);
        else
            return false;
        break;
    case D:
        if (nbCaseD() > 0 && e.nbCaseG() <= nbCaseD())
            return estCompatibleEspace(e, D, G, NE, E, SE, NO, O, SO);
        else
            return false;
        break;
    default:
        return false;
        break;
    }
}

bool Endroit::estCompatibleEspace(Endroit e, Compatibilite c1, Compatibilite c2, Cardinal pos1_1, Cardinal pos1_2, Cardinal pos1_3, Cardinal pos2_1, Cardinal pos2_2, Cardinal pos2_3) const  {
    //compteur sur le nombre de case compatible entre les 2 endroits
    unsigned int i = 0;

    //iterator sur les cases de l'endroit avec lequel la methode est appelée
    for (Endroit::const_iterator it = cbegin();it != cend();it++)
        //on s'asssure que la compatibilite de la case est en accord avec le paramètre de la fonction
        if ((*it)->getCompatibilite() == c1)
            //iterator sur les cases de l'endroit en paramètre
            for (Endroit::const_iterator it2 = e.cbegin();it2 != e.cend();it2++) {
                //on test la cardianalité et compatibilite des case sont en accord avec les paramètres de la fonction
                if ((*it)->getCardinal() == pos1_1 && (*it2)->getCardinal() == pos2_1)
                    i++;
                if ((*it)->getCardinal() == pos1_2 && (*it2)->getCompatibilite() == c2 && (*it2)->getCardinal() == pos2_2 )
                    i++;
                if ((*it)->getCardinal() == pos1_3 && (*it2)->getCompatibilite() == c2 && (*it2)->getCardinal() == pos2_3 )
                    i++;
            }
    //on verifie que le compteur est coherent avec de renvoyer un true
    switch (c1)
    {
    case H:
        return i >0;
        break;
    case B:
        return i >0;
        break;
    case G:
        return i >0;
        break;
    case D:
        return i>0;
        break;
    default:
        return false;
        break;
    };
}


/*

//fonction qui crée les espaces d'une tuile quand cette dernière est posée sur le plateau
//un espace est créé pour chaque endroit
list<Espace*>& Tuile::creationEspace() {
    //on stocke avec une liste les espaces crées
    list<Espace*>* le = new list<Espace*>;
    Espace* e;
    //iterateur sur les endroits de la tuile
    for (Tuile::iterator it = begin();it != end();it++) {
        //alocation dynamqieu de mémoire: on cré un nouvel espace pour cet endroit
        e = new Espace();
        le->push_back(e);
        //espace ajouter dans l'endroit
        (*it)->setEspace(e);
        //tuile ajouter dans espace
        e->addPaire(pair<Tuile*,Endroit*>(this,(*it)));
    }
    return *le;
}


void Tuile::additionEspace(Tuile* t, const Compatibilite c)
{
    Endroit* e1;
    Endroit* e2;
    list<Espace*> espaceASup;

    unsigned int test = 0;
    switch (c)
    {
    case B:
        e1 = getEndroitFromACase(NO, H);
        e2 = t->getEndroitFromACase(SO, B);
        if (e1->getLieu()->getLieu() == e2->getLieu()->getLieu()) {
            espaceASup.push_back(e1->transfertEspace(e2));
            test++;
        }


        e1 = getEndroitFromACase(N, H);
        e2 = t->getEndroitFromACase(S, B);
        if (e1->getLieu()->getLieu() == e2->getLieu()->getLieu()) {
            espaceASup.push_back(e1->transfertEspace(e2));
            test++;
        }

        e1 = getEndroitFromACase(NE, H);
        e2 = t->getEndroitFromACase(SE, B);
        if (e1->getLieu()->getLieu() == e2->getLieu()->getLieu()) {
            espaceASup.push_back(e1->transfertEspace(e2));
            test++;
        }

        break;
    case H:
        e1 = getEndroitFromACase(SO, B);
        e2 = t->getEndroitFromACase(NO, H);
        if (e1->getLieu()->getLieu() == e2->getLieu()->getLieu()) {
            espaceASup.push_back(e1->transfertEspace(e2));
        }


        e1 = getEndroitFromACase(S, B);
        e2 = t->getEndroitFromACase(N, H);
        if (e1->getLieu()->getLieu() == e2->getLieu()->getLieu()) {
            espaceASup.push_back(e1->transfertEspace(e2));
            test++;
        }

        e1 = getEndroitFromACase(SE, B);
        e2 = t->getEndroitFromACase(NE, H);
        if (e1->getLieu()->getLieu() == e2->getLieu()->getLieu()) {
            espaceASup.push_back(e1->transfertEspace(e2));
            test++;
        }
        break;
    case D:
        e1 = getEndroitFromACase(NO, G);
        e2 = t->getEndroitFromACase(NE, D);
        if (e1->getLieu()->getLieu() == e2->getLieu()->getLieu()) {
            espaceASup.push_back(e1->transfertEspace(e2));
            test++;
        }

        e1 = getEndroitFromACase(O, G);
        e2 = t->getEndroitFromACase(E, D);
        if (e1->getLieu()->getLieu() == e2->getLieu()->getLieu()) {
            espaceASup.push_back(e1->transfertEspace(e2));
            test++;
        }

        e1 = getEndroitFromACase(SO, G);
        e2 = t->getEndroitFromACase(SE, D);
        if (e1->getLieu()->getLieu() == e2->getLieu()->getLieu()) {
            espaceASup.push_back(e1->transfertEspace(e2));
            test++;
        }
        break;
    case G:
        e1 = getEndroitFromACase(NE, D);
        e2 = t->getEndroitFromACase(NO, G);
        if (e1->getLieu()->getLieu() == e2->getLieu()->getLieu()) {
            espaceASup.push_back(e1->transfertEspace(e2));
            test++;
        }


        e1 = getEndroitFromACase(E, D);
        e2 = t->getEndroitFromACase(O, G);
        if (e1->getLieu()->getLieu() == e2->getLieu()->getLieu()) {
            espaceASup.push_back(e1->transfertEspace(e2));
            test++;
        }

        e1 = getEndroitFromACase(SE, D);
        e2 = t->getEndroitFromACase(SO, G);
        if (e1->getLieu()->getLieu() == e2->getLieu()->getLieu()) {
            espaceASup.push_back(e1->transfertEspace(e2));
            test++;
        }
        break;
    default:
        break;
    }
    cout << "le nombre de tests :" << test << "\n";
}


Espace* Endroit::transfertEspace(Endroit* e) {
    Espace* old = e->getEspace();
    //on change l'espace de la tuile ajdacente avec le nouvelle espace de la tuile posée
    e->setEspace(this->getEspace());
    //on ajoute les tuiles de l'espace a fusioné a l'espace de la tuile posée
    this->getEspace()->addPaires(e->getEspace()->getListPaire());
    //on libere la mémoire de l'espace de la tuile en paramètre qui a été fuisoné
    return old;
}


bool testFusion(Endroit& e1, Endroit& e2)
{
    if((e1.getLieu()->getLieu() == e2.getLieu()->getLieu())  && (e1.getEspace() != e2.getEspace()))
    {//si j'ai le même lieu dans des espaces différents, on vérifie si on ne peut pas fusionner

        for( auto it_endroit = e1.getEspace()->getListEndroit().begin() ; it_endroit != e1.getEspace()->getListEndroit().end() ; it_endroit ++ )
        {
            for( auto it_endroit2 = e2.getEspace()->getListEndroit().begin() ; it_endroit2 != e2.getEspace()->getListEndroit().end() ; it_endroit2 ++ )
            {
                if( (*it_endroit) == (*it_endroit2))
                {
                    return true;
                }
            }
        }
    }
    return false;
}


Espace* fusion(Espace* e1, Espace* e2)
{
    Espace* result = new Espace();
    list<pair<Tuile*,Endroit*>>* courrant = new list<pair<Tuile*,Endroit*>>;

    for(auto it = e1->getPaire().begin() ; it != e1->getPaire().end() ; it++  )
    {
        for(auto it2 = e2->getPaire().begin() ; it2 != e2->getPaire().end() ; it2++  )
        {
            if( (*it).second == (*it2).second )
            {
                courrant->push_back((*it));
            }
            else
            {
                courrant->push_back((*it));
                courrant->push_back((*it2));
            }
        }
    }
    result->getPaire()=*courrant;
    return result;
}

void Tuile::fusionEspace(const Compatibilite c)
{
    //un boucle sur la liste des endroits et fusion quand il a des endroits avec des espaces en communs
    for(auto it =begin() ; it!=end() ; it++)
    { // 1e parcour des endroits de ma tuile
        for(auto it2 = begin(); it2!=end() ; it2++)
        { // second parcours des endroits de ma tuile
             if(testFusion((**it), (**it2))) // si j'ai une fusion à faire
             {
                Espace* espace = fusion((*it)->getEspace(), (*it2)->getEspace());

                Espace* old1 = (*it)->getEspace();
                Espace* old2 = (*it2)->getEspace();

                *((*it)->getEspace()) = *espace;
                *(*it2)->getEspace() = *espace ;
                delete old1;
                delete old2;
             }
        }
    }
}






//fonction qui fusione les espace d'une tuile qui a été posé avec une tuile adjacente
void Tuile::fusionEspace(Tuile* t, const Compatibilite c)
{
    cout << "entre fusionEspace\n";
    //iterateur sur les endroits de la tuile passée en paramètre
    for (Tuile::iterator it = begin();it != end();it++) {

        //iterateur sur les endroits de la tuile qui appèle la méthode
        for (Tuile::iterator it2 = t->begin();it2 != t->end();it2++) {
            //on verifie que les deux tuiles ne font pas partie du même espace
            if ((*it)->getEspace() != (*it2)->getEspace()) {
                //on verifie la compatibilité entre les 2 espaces
                if ((*it)->estCompatibleEspace_sens(**it2, c)) {
                    cout << "fusion en place\n";
                    cout << "endroit1:\n";
                    (*it)->afficherCases();
                    cout << "endroit2:\n";
                    (*it2)->afficherCases();

                    Espace* old = (*it)->getEspace();

                    //on ajoute les tuiles de l'espace a fusioné a l'espace de la tuile posée
                    (*it2)->getEspace()->addTuiles((*it)->getEspace()->getListTuiles());

                    //on change l'espace de la tiule ajdacente avec le nouvelle espace de la tuile posée
                    (*it)->setEspace((*it2)->getEspace());

                    //on libere la mémoire de l'espace de la tuile en paramètre qui a été fuisoné
                    delete old;
                }
            }
        }
    }
}



//fonction qui crée les espaces d'une tuile quand cette dernière est posée sur le plateau
//un espace est créé pour chaque endroit
list<Espace*> Tuile::creationEspace() {
    //on stocke avec une liste les espaces crées
    list<Espace*> le;
    Espace* e;
    //iterateur sur les endroits de la tuile
    for (Tuile::iterator it = begin();it != end();it++) {
        //alocation dynamqieu de mémoire: on cré un nouvel espace pour cet endroit
        e = new Espace();
        le.push_back(e);
        //espace ajouter dans l'endroit
        (*it)->setEspace(e);
        //tuile ajouter dans espace
        e->addTuile(this);
    }
    return le;
}


//fonction qui fusione les espace d'une tuile qui a été posé avec une tuile adjacente
void Tuile::fusionEspace(Tuile* t, const Compatibilite c)
{
    cout << "entre fusionEspace\n";
    //iterateur sur les endroits de la tuile passée en paramètre
    for (Tuile::iterator it = begin();it != end();it++) {

        //iterateur sur les endroits de la tuile qui appèle la méthode
        for (Tuile::iterator it2 = t->begin();it2 != t->end();it2++) {
            //on verifie que les deux tuiles ne font pas partie du même espace
            if ((*it)->getEspace() != (*it2)->getEspace()) {
                //on verifie la compatibilité entre les 2 espaces
                if ((*it)->estCompatibleEspace_sens(**it2, c)) {
                    cout << "fusion en place\n";
                    cout << "endroit1:\n";
                    (*it)->afficherCases();
                    cout << "endroit2:\n";
                    (*it2)->afficherCases();

                    Espace* old = (*it)->getEspace();

                    //on ajoute les tuiles de l'espace a fusioné a l'espace de la tuile posée
                    (*it2)->getEspace()->addTuiles((*it)->getEspace()->getListTuiles());

                    //on change l'espace de la tiule ajdacente avec le nouvelle espace de la tuile posée
                    (*it)->setEspace((*it2)->getEspace());

                    //on libere la mémoire de l'espace de la tuile en paramètre qui a été fuisoné
                    delete old;
                }
            }
        }
    }
}

*/

Endroit* Tuile::getEndroitFromACase(Cardinal ca, Compatibilite co) {
    for (Tuile::iterator it = begin(); it != end();it++) {
        for (Endroit::iterator it2 = (*it)->begin(); it2 != (*it)->end(); it2++) {
            if ((*it2)->getCardinal() == ca && (*it2)->getCompatibilite() == co) {
                return *it;
            }
        }
    }
    return nullptr;
}


bool Tuile::tuileAvecLieu(const string lieu)
{
    bool defaut = true;
    //parcour tous les endroit de la tuile
    for (auto it_endroit = cbegin(); it_endroit != cend(); it_endroit++)
    {
        //si l'endroit a le lieu en question
        if ((*it_endroit)->getLieu()->getLieu() == lieu)
        {
            return true;
        }
    }
    return false;
}


list<Cardinal> Tuile::getListCardianliteLieu(const string s) const {
    list<Cardinal> listCardi;
    for (Tuile::const_iterator it = cbegin();it != cend();it++) {
        if ((*it)->getLieu()->getLieu()==s){
            for (Endroit::const_iterator it2 = (*it)->cbegin();it2 != (*it)->cend();it2++)
                listCardi.push_back((*it2)->getCardinal());
        }
    }
    return listCardi;
}

Tuile& Tuile::operator=(const Tuile& t) {
    if (this == &t) {
        throw TuileException("problème avec l'opérateur = de tuile");
    }
    rotation = t.getRotation();
    id = t.getId();
    place.clear();
    for (auto it = t.cbegin(); it != t.cend();it++) {
        place.push_back(new Endroit(**it));
    }
    return *this;
}

Tuile::~Tuile() {
    while (!place.empty()){
        delete place.front();
        place.pop_front();
    }
    cout << "destruction tuile\n";
}

Endroit::~Endroit() {
    while (!cases.empty()) {
        delete cases.front();
        cases.pop_front();
    }
}

void Tuile::afficherEspace() {
    unsigned int i=0;
    for (Tuile::iterator it = begin();it != end();it++) {
        cout << "espace " << i++<<"\n";
        Espace* e = (*it)->getEspace();
        if (e == nullptr)
            throw TuileException("erreur de pointeur vide");
        cout << "erreur iciccc\n";
        if (e->getListTuiles().empty()) {
            throw TuileException("erreur liste tuile vide");
        }
        //for (auto it2 = e->getListTuiles().begin();it2 != e->getListTuiles().end();it2++)
            //cout << "tuile: " << (*it2)->getId() << "\n";
        cout << "\n\n\n";
    }

}


void Endroit::afficherCases() const {
    cout << "Endroit: " << getLieu()->getLieu() << "\n";
    for (Endroit::const_iterator it_case = cbegin();it_case != cend();it_case++) {
        switch ((*it_case)->getCardinal())
        {
        case NE:
            cout << "NE, ";
            break;
        case N:
            cout << "N, ";
            break;
        case NO:
            cout << "NO, ";
            break;
        case O:
            cout << "0, ";
            break;
        case SO:
            cout << "SO, ";
            break;
        case S:
            cout << "S, ";
            break;
        case SE:
            cout << "SE, ";
            break;
        case E:
            cout << "E, ";
            break;
        default:
            cout << "C, ";
            break;
        }
        switch ((*it_case)->getCompatibilite())
        {
        case D:
            cout << "D, ";
            break;
        case G:
            cout << "G, ";
            break;
        case H:
            cout << "H, ";
            break;
        case B:
            cout << "B, ";
            break;
        default:
            cout << "R, ";
            break;
        }
        cout << "\n";
    }
    cout << "\n";
    }
