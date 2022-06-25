#pragma once
#include "meeple.h"
#include <string>
#include <vector>

//  CODE DE LA CLASSE :
//	Joueur
// IA

class Joueur
{
protected:
    string nom;
    Couleurs couleur;
    int points;
    vector<Meeple*> meeples;

public:
    string& getNom() { return nom; }
    const int& getPoints() const { return points; }
    int& getPoints() { return points; }
    void ajouter_meeple(Meeple& meeple);
    vector<Meeple*>& getMeeplesJoueur() { return meeples; }
    Joueur(const std::string& n, Couleurs c= Couleurs::SansCouleur):nom(n), couleur(c), points(0) {};
    virtual ~Joueur();
    void setCouleur_meeple(Couleurs couleur);
    void afficher();
    Couleurs getCouleur(){return couleur;}
};

class IA : public Joueur
{
public:
    IA(const std::string& n, const Couleurs c = Couleurs::SansCouleur) :Joueur(n,c) {};
    ~IA()=default;
};
