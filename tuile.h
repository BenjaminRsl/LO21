#pragma once
#include<list>
#include<vector>
#include<iostream>
#include<string>
#include "lieu.h"
#include "espace.h"

// CODE DE LA CLASSE :
//	TuileException
//	Case
//  Endroit
//	Tuile


/* ---------  Enumerate  --------- */
enum  Cardinal { NO, N, NE, O, C, E, SO, S, SE, nulle };
enum  Compatibilite { H, B, G, D, nul };

/* ---------  Exception  --------- */
class TuileException : public exception {
    string info;
public:
    TuileException(const string& i) noexcept :info(i) {}
    virtual ~TuileException() noexcept {}
    const char* what() const noexcept { return info.c_str(); }
};




/* ---------  Case  --------- */

class Case
{
public:
    /* --- C.D.  --- */
    Case(Cardinal c,  Compatibilite comp) : coord(c), compatibilite(comp) {};
    Case(const Case&) = default;

    //surcharger l'opperateur de recopie?

    virtual ~Case() {}

    //les getteurs comme seteurs n'ont pas besoins d'être redéfinies
    //pendant les spécialisations de la classe
    /* --- geteur --- */
    Cardinal getCardinal() const { return coord; };
    Compatibilite getCompatibilite() const { return compatibilite; };

    /* --- seteur --- */
    void setCardinal(Cardinal c) { coord=c ; };
    void setCompatibilite(Compatibilite c) { compatibilite = c; };

private:
    Cardinal coord;
    Compatibilite compatibilite;
};




class Espace;

/*--------- Endroit --------- */

class Endroit
{
public:
    /* --- C.D.  --- */
    Endroit(string n, list<Case*> c, Lieu* l, Espace* e):nom(n),cases(c), lieu(l), espace(e) {};
    Endroit(string n, list<Case*> c, Lieu* l) :nom(n), cases(c), lieu(l), espace(nullptr) {};
    Endroit(const Endroit& e){
        nom = e.getNom();
        lieu = e.getLieu();
        espace = nullptr;
        cases.clear();
        for (auto it = e.cbegin();it != e.cend();it++) {
            cases.push_back(new Case(**it));
        }
    }
    virtual ~Endroit();

    /* --- geteur --- */
    //pas besoin de les avoir virtual
    string getNom() const { return nom; };
    const list<Case*>& getCases() const { return cases; };
    Lieu* getLieu() const { return lieu; };
    Espace* getEspace() { return espace; };

    /* --- seteur --- */
    //pas besoin de les avoir virtual
    list<Case*> setCases() { return cases; };
    void setEspace(Espace* e)  { espace=e; };

    //retourne le nombre de cases en fonction d'une compatibilité
    virtual unsigned int nbCaseCompatibilite(Compatibilite c) const;

    unsigned int nbCaseD() const;
    unsigned int nbCaseG() const;
    unsigned int nbCaseH() const;
    unsigned int nbCaseB() const;

    void afficherCases()const;

    //test la compatibilité entre 2 espaces en fonction d'une compatibilité
    virtual bool estCompatibleEspace_sens(Endroit e, Compatibilite compatibilite) const;

    //iterateur sur les cases de l'endroit
    class iterator : public list<Case*>::iterator
    {
    public:
        Case* operator*() const {return list<Case*>::iterator::operator*();	}

        void operator++(int){list<Case*>::iterator::operator++();}

        void setCase(Cardinal ca, Compatibilite co){
            list<Case*>::iterator::operator*()->setCardinal(ca);
            list<Case*>::iterator::operator*()->setCompatibilite(co);
        }
    private:
        friend class Endroit;
        iterator(const list<Case*>::iterator& it) :
            list<Case*>::iterator(it) {};
    };

    //iterateur constant sur les cases de l'endroit
    class const_iterator : public list<Case*>::const_iterator
    {
    public:
        const Case* operator*() const
        {
            return list<Case*>::const_iterator::operator*();
        }
        void operator++(int)
        {
            list<Case*>::const_iterator::operator++();
        }
    private:
        friend class Endroit;
        const_iterator(const list<Case*>::const_iterator& it) :
            list<Case*>::const_iterator(it) {};
    };

    iterator begin() { return iterator(cases.begin()); }

    iterator end() { return iterator(cases.end()); }

    const_iterator cbegin() const { return const_iterator(cases.cbegin()); }

    const_iterator cend() const { return const_iterator(cases.cend()); }

private:
    string nom;
    Lieu* lieu;
    Espace* espace;
    list<Case*> cases;

    //fonction en privé car est utilisée par d'autres fonctions
    bool estCompatibleEspace(Endroit e, Compatibilite c1, Compatibilite c2, Cardinal pos1_1, Cardinal pos1_2, Cardinal pos1_3, Cardinal pos2_1, Cardinal pos2_2, Cardinal pos2_3) const;
};


Espace* fusion(Espace* e1, Espace* e2);
bool testFusion(Endroit& e1, Endroit& e2);

/* ---------  Tuile  --------- */

class Tuile
{
public:
    /* --- Constructeur de tuile --- */
    Tuile(list<Endroit*> ini) :rotation(0), id(0), place(ini) { std::cout << "tuile crée"; }; //dans jeu, vector de list<Endroit> de taille nb de tuile
    Tuile(list<Endroit*> ini,unsigned int i) :rotation(0), id(i), place(ini) { std::cout << "tuile crée"; }; //dans jeu, vector de list<Endroit> de taille nb de tuile
    Tuile() :rotation(0), id(0) {};

    virtual ~Tuile();
    Tuile(const Tuile& t)
    {
        rotation = t.getRotation();
        id = t.getId();
        place.clear();
        for (auto it = t.cbegin(); it != t.cend();it++) {
            place.push_back(new Endroit(**it));
        }
    }

    Tuile& operator=(const Tuile& t);

    /* --- geteur --- */
    //pas besoin de les avoir en virtual
    const list<Endroit*>& getListEndroit() const { return place; }
    list<Endroit*>& getListEndroit() { return place; }
    unsigned int getId() const { return id; };
    unsigned int getRotation() const { return rotation; };


    //on peut faire une rotation à gauche ou à droite
    void Rotation();

    //on peut comparer la tuille par rapport à une autre tuille sur les positions haut, bas, droite ou gauche
    virtual bool estCompatible(Tuile* t, Compatibilite c) ;

    //affiche une tuile
    //fonction deja virtuel de la classe Tuile
    void afficherTuile() const;

    //quand on pose une tuile on doit créer les espaces associé aux endroits de la tuile
    //virtual list<Espace*>& creationEspace();

    //virtual void additionEspace(Tuile* tuile, const Compatibilite c );

    //fonction pour fusionner les espaces après avoir posé une tuile
    //virtual void fusionEspace(const Compatibilite c);

    list<Cardinal> getListCardianliteLieu(const string s) const;

    list<Cardinal> getListCardianliteRiviere() const {
        return getListCardianliteLieu("Riviere");
    }

    //iterator sur les endroits de la tuile
    class iterator : public list<Endroit *>::iterator
    {
    public:
        Endroit* operator*() const
        {
            return list<Endroit *>::iterator::operator*();
        }

        void operator++(int)
        {
            list<Endroit *>::iterator::operator++();
        }
    private:
        friend class Tuile;
        iterator(const list<Endroit *>::iterator& it) :
            list<Endroit *>::iterator(it) {};
    };

    //iterator constant sur les endroits de la tuile
    class const_iterator : public list<Endroit *>::const_iterator
    {
    public:
        const Endroit* operator*() const
        {
            return list<Endroit*>::const_iterator::operator*();
        }
        void operator++(int)
        {
            list<Endroit*>::const_iterator::operator++();
        }
    private:
        friend class Tuile;
        const_iterator(const list<Endroit *>::const_iterator& it) :
            list<Endroit*>::const_iterator(it) {};
    };


    iterator begin() { return iterator(place.begin()); }

    iterator end() { return iterator(place.end()); }

    const_iterator cbegin() const { return const_iterator(place.cbegin());	}

    const_iterator cend() const { return const_iterator(place.cend()); }

    bool tuileAvecLieu(const string lieu);

    bool tuileAvecRiviere() {
        return tuileAvecLieu("Riviere");
    }
    bool tuileAvecSource() {
        return tuileAvecLieu("Source");
    }
    void afficherEspace();

    Endroit* getEndroitFromACase(Cardinal ca, Compatibilite co);
private:
    list<Endroit*> place;
    //rotation peut prendre une valeur entre 0 et 3
    // 0 la tuile na pas subit de rotation, 1 une rotation a droite, 2 deux rotations  a droite, 3 trois rotations a droite (ou une a gauche)
    unsigned int rotation;
    unsigned int id;
    //la fonction est en privé car on l'utilise dans d'autre fonction
    bool estCompatiblepos(Tuile* t, const Compatibilite comp1, const Compatibilite comp2, const Cardinal pos1_1, const Cardinal pos1_2, const Cardinal pos1_3, const Cardinal pos2_1, const Cardinal pos2_2, const Cardinal pos2_3) ;

};



