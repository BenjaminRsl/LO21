#pragma once

#include <cstdio>
#include <string>
#include "tuile.h"
#include "lieu.h"

// CODE DE LA CLASSE :
//	Enum  : Couleurs ; Fonctions
//	Meeple
//	TypeMeeple

/* ---------  Enumerate  --------- */
enum class Couleurs
{
    Bleu, Blanc, Rouge, Rose, SansCouleur
};

enum class Fonctions
{
    Moine, Chevalier, Voleur, Rien, Paysan
};

/* ---------  Exception  --------- */



class TypeMeeple
{
public:
    const Fonctions& get_fonction() const { return fonction; } //lecture seule
    Fonctions& get_fonction()  { return fonction; } //écriture
    unsigned short int get_nb_points() const { return nbPoints; } //lecture seule
    unsigned short int get_nb_points() { return nbPoints; } //écriture
    TypeMeeple(Fonctions f=Fonctions::Rien, unsigned short int nb=0) : fonction(f), nbPoints(nb) {};
private:
    Fonctions fonction;
    unsigned short int nbPoints;
};

/* ---------  Meeple  --------- */
class Meeple
{

private:
    // à voir plus tard si nous avons besoin de copier et affecter
    Meeple& operator=(const Meeple& m) = delete;

protected:

    std::string nom; //identifiant du meeple
    Couleurs couleur; // couleur du meeple
    unsigned short int valeur;
    Endroit* poser;
    TypeMeeple type;

public:
    Meeple(const std::string& n, const Couleurs c, const Fonctions f, unsigned short int v = 1, unsigned short int nbPoints = 0);
    Meeple(const std::string& n, unsigned short int v = 1);
    ~Meeple() { std::cout << " #######  DESCTUCTION MEEPLE  ####### \n \n";  delete poser; }

    void poserMeeple(Endroit e) { poser = &e; }
    void retirerMeeple() { poser = nullptr; }

    Meeple(const Meeple& m);
    /* --- get --- */
    const std::string& getNom()const{ return nom;}
    std::string& getNom() { return nom; }
    Couleurs getCouleur() const { return couleur; }
    unsigned short int getValeur() const { return valeur; }
    unsigned short int getNbPoints() const { return type.get_nb_points(); }
    Endroit* estPose() { return poser; }
    Fonctions& getFonction(){return type.get_fonction();}

    void setCouleur(Couleurs c) {couleur = c; }

    void afficher();



};
