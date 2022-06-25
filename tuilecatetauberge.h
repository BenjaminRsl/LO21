#pragma once
#include"tuile.h"


// CODE DE LA CLASSE :
//	tuileCatEtAuberge
//	EndroitCatEtAuberge
//  CaseCatEtAuberge

class tuileCatEtAuberge: public Tuile
{
public:
    tuileCatEtAuberge(list<Endroit*> ini, unsigned int i) : Tuile(ini, i)
    {
    };
        ~tuileCatEtAuberge() {};
};

class EndroitCatEtAuberge : public Endroit {
private:
    bool influenceAubergeEndroit;
public:
    EndroitCatEtAuberge(string n, list<Case*> c, Lieu* l, Espace* e, bool b) :
        Endroit(n, c, l, e), influenceAubergeEndroit(b) {};
    bool getInfluenceAubergeEndroit() const { return influenceAubergeEndroit; };
    void checkInfluenceAubergeEndroit();
};



// Spcialisation de la case pour l'extensionAuberge et cathdral afin de savoir si la case est sous l'influence d'une auberge
// c'est  dire si les points de la route devront tre doubls ou non
class CaseCatEtAuberge : public Case {
private:
    bool influenceAubergeCase;
public:
    CaseCatEtAuberge(Cardinal c, Compatibilite comp, bool b) : Case(c, comp), influenceAubergeCase(b) {};
    bool getInfluenceAubergeCase() { return influenceAubergeCase; };
    void setInfluenceAubergeCase(const bool b) { influenceAubergeCase = b; };
    ~CaseCatEtAuberge() {};
};

