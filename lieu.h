#pragma once
#include <iostream>
#include<string>
#include<stdexcept>
using namespace std;


//  CODE DE LA CLASSE :
//	LieuException
//  Lieu
// les classes filles de lieux


class LieuException : public exception {
    std::string info;
public:
    LieuException(const string& i) noexcept :info(i) {}
    virtual ~LieuException() noexcept {}
    const char* what() const noexcept { return info.c_str(); }
};


class Lieu
{
protected:
    int nbpoint; //nb de point de base dans les règles, dans l'implémentation standard c'est 1
    string nom;
public:
    int getNbPoint() const { return nbpoint; };
    string getLieu() const { return nom; };
    Lieu(const int p, string s) :nbpoint(p), nom(s) {};
    virtual ~Lieu() = default;
    bool operator==(const Lieu& l) { return nom == l.nom; };
    bool operator!=(const Lieu& l) { return nom != l.nom; };
    virtual void afficher() = 0;
};

class Village : public Lieu {
public:
    explicit Village(const int p) : Lieu(p, "Village")  { std::cout << "- Le lieu " << nom << " a ete créé \n"; };
    void afficher() override{
        cout << "Ce lieu est un village\n";
    };
    ~Village() = default;
};

class Abbaye : public Lieu{
public:
    explicit Abbaye(const int p) : Lieu(p,"Abbaye") { std::cout << "- Le lieu " << nom << " a ete créé \n"; };
    void afficher() override {
        cout << "Ce lieu est une Abbaye\n";
    };
    ~Abbaye() = default;
};

class Ville : public Lieu {
public:
    explicit Ville(const int p) : Lieu(p,"Ville") { std::cout << "- Le lieu " << nom << " a ete créé \n"; };
    void afficher() override {
        cout << "Ce lieu est une Ville\n";
    };
    ~Ville() = default;
};

class Route : public Lieu {
public:
    explicit Route(const int p) : Lieu(p,"Route") { std::cout << "- Le lieu " << nom << " a ete créé \n"; };
    void afficher() override {
        cout << "Ce lieu est une Route\n";
    };
    ~Route() = default;
};

class Plaine : public Lieu {
public:
    explicit Plaine(const int p) : Lieu(p,"Plaine") { std::cout << "- Le lieu " << nom << " a ete créé \n"; };
    void afficher() override {
        cout << "Ce lieu est une Plaine\n";
    };
    ~Plaine() = default;
};

class Auberge : public Lieu {
public:
    explicit Auberge(const int p) : Lieu(p,"Auberge") { std::cout << "- Le lieu " << nom << " a ete créé \n"; };
    void afficher() override {
        cout << "Ce lieu est une Auberge\n";
    };
    ~Auberge() = default;
};

class Cathedrale : public Lieu {
public:
    explicit Cathedrale(const int p) : Lieu(p,"Cathedrale") { std::cout << "- Le lieu " << nom << " a ete créé \n"; };
    void afficher() override {
        cout << "Ce lieu est une Abbaye\n";
    };
    ~Cathedrale() = default;
};

class Riviere : public Lieu {
public:
    explicit Riviere(const int p) : Lieu(p,"Riviere") { std::cout << "- Le lieu " << nom << " a ete créé \n"; };
    void afficher() override {
        cout << "Ce lieu est une Riviere\n";
    };
    ~Riviere() = default;
};

class Source : public Lieu {
public:
    explicit Source(const int p) : Lieu(p, "Source") { std::cout << "- Le lieu " << nom << " a ete créé \n"; };
    void afficher() override {
        cout << "Ce lieu est une Source\n";
    };
    ~Source() = default;
};

class Jardin : public Plaine {
public:
    explicit Jardin(const int p) : Plaine(p) { nom = "Plaine"; { std::cout << "- Le lieu " << nom << " a ete créé \n"; };
    };
    void afficher() override {
        cout << "Ce lieu est une Jardin\n";
    };
    ~Jardin() = default;
};


class Buisson : public Lieu {
public:
    explicit Buisson(const int p) : Lieu(p, "Buisson")  { std::cout << "- Le lieu " << nom << " a ete créé \n"; };
    void afficher() override {
        cout << "Ce lieu est une Buisson \n";
    };
    ~Buisson() = default;
};
