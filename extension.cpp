#include "extension.h"
#include "tuilecatetauberge.h"





/*
------------------------   Extension ----------------------
*/

/* ---------- Ajout dans les listes ----------*/

void Extension::ajouterMeeple(Meeple* meeple)
{
    ensembleMeeples.push_back(meeple);
}

void Extension::ajouterLieu(Lieu* lieu)
{
    ensembleLieux.push_back(lieu);
}

void Extension::ajouterTuile(Tuile* tuile)
{	ensembleTuiles.push_back(tuile);
}



/*
------------------------   Classique  ----------------------
*/

Classique::Classique() {


    //Meeples
    for(int i=0; i!=8;i++)
    {
        ajouterMeeple(new Meeple("Simple", 1));
    }

    //implementer la liste Regle

    unsigned int i = 1;
    Lieu* lieu_ville = new Ville(1);
    Lieu* lieu_plaine = new Plaine(1);
    Lieu* lieu_route = new Route(1);
    Lieu* lieu_abbaye = new Abbaye(1);
    Lieu* lieu_riviere = new Riviere(1);
    Lieu* lieu_auberge = new Auberge(1);
    Lieu* lieu_source = new Source(1);

    ajouterLieu(lieu_ville);
    ajouterLieu(lieu_plaine);
    ajouterLieu(lieu_route);
    ajouterLieu(lieu_abbaye);
    ajouterLieu(lieu_riviere);
    ajouterLieu(lieu_auberge);
    ajouterLieu(lieu_source);


    list<Case*> villeHaut;
    villeHaut.push_back(new Case(NO, H));
    villeHaut.push_back(new Case(N, H));
    villeHaut.push_back(new Case(NE, H));
    Endroit VHaut("villeH", villeHaut, lieu_ville, nullptr);


    list<Case*> villeBas;
    villeBas.push_back(new Case(SE, B));
    villeBas.push_back(new Case(S, B));
    villeBas.push_back(new Case(SO,B));
    Endroit VBas("villeB", villeBas, lieu_ville, nullptr);

    list<Case*> villeDroite;
    villeDroite.push_back(new Case(NE, D));
    villeDroite.push_back(new Case(E, D));
    villeDroite.push_back(new Case(SE, D));
    Endroit VDroite("villeD", villeDroite, lieu_ville, nullptr);

    list<Case*> villeHautDroite;
    villeHautDroite.push_back(new Case(NO, H));
    villeHautDroite.push_back(new Case(N, H));
    villeHautDroite.push_back(new Case(NE, H));
    villeHautDroite.push_back(new Case(NE, D));
    villeHautDroite.push_back(new Case(E, D));
    villeHautDroite.push_back(new Case(SE, D));
    Endroit VHautDroite("villeHD", villeHautDroite, lieu_ville, nullptr);

    list<Case*> villeSaufBas;
    villeSaufBas.push_back(new Case(NO, G));
    villeSaufBas.push_back(new Case(NO, H));
    villeSaufBas.push_back(new Case(N, H));
    villeSaufBas.push_back(new Case(NE, H));
    villeSaufBas.push_back(new Case(NE, D));
    villeSaufBas.push_back(new Case(E, D));
    villeSaufBas.push_back(new Case(SE, D));
    villeSaufBas.push_back(new Case(SO, G));
    villeSaufBas.push_back(new Case(O, G));
    villeSaufBas.push_back(new Case(C, nul));
    Endroit VSBas("villeSB", villeSaufBas, lieu_ville, nullptr);


    list<Case*> villeTriancleHautDroit;
    villeTriancleHautDroit.push_back(new Case(NO, H));
    villeTriancleHautDroit.push_back(new Case(N, H));
    villeTriancleHautDroit.push_back(new Case(NE, H));
    villeTriancleHautDroit.push_back(new Case(NE, D));
    villeTriancleHautDroit.push_back(new Case(E, D));
    villeTriancleHautDroit.push_back(new Case(SE, D));
    Endroit VTHautDroit("villeTHD", villeTriancleHautDroit, lieu_ville, nullptr);


    list<Case*> plaineTriangleBasGauche;
    plaineTriangleBasGauche.push_back(new Case(NO, G));
    plaineTriangleBasGauche.push_back(new Case(O, G));
    plaineTriangleBasGauche.push_back(new Case(SO, G));
    plaineTriangleBasGauche.push_back(new Case(SO,B));
    plaineTriangleBasGauche.push_back(new Case(S, B));
    plaineTriangleBasGauche.push_back(new Case(SE, B));
    plaineTriangleBasGauche.push_back(new Case(C, nul));
    Endroit PTBasGauche("plaineTBasGauche", plaineTriangleBasGauche, lieu_plaine, nullptr);


    list<Case*> plaineBas;
    plaineBas.push_back(new Case(SE, B));
    plaineBas.push_back(new Case(S, B));
    plaineBas.push_back(new Case(SO,B));
    Endroit PBas("plaineB", plaineBas, lieu_plaine, nullptr);

    list<Case*> plaineRectangleBas;
    plaineRectangleBas.push_back(new Case(SO, G));
    plaineRectangleBas.push_back(new Case(SO,B));
    plaineRectangleBas.push_back(new Case(S, B));
    plaineRectangleBas.push_back(new Case(SE, B));
    plaineRectangleBas.push_back(new Case(SE, D));
    Endroit PRBas("plaineB", plaineRectangleBas, lieu_plaine, nullptr);

    list<Case*> plaineRectangleHaut;
    plaineRectangleHaut.push_back(new Case(NO, G));
    plaineRectangleHaut.push_back(new Case(NO, H));
    plaineRectangleHaut.push_back(new Case(N, H));
    plaineRectangleHaut.push_back(new Case(NE, H));
    plaineRectangleHaut.push_back(new Case(NE, D));
    Endroit PRHaut("plaineB", plaineRectangleHaut, lieu_plaine, nullptr);

    list<Case*> plaineCoinBasDroit;
    plaineCoinBasDroit.push_back(new Case(SE, D));
    plaineCoinBasDroit.push_back(new Case(SE, B));
    Endroit PCBasDroit("plaineBSC", plaineCoinBasDroit, lieu_plaine, nullptr);

    list<Case*> plaineCoinBasGauche;
    plaineCoinBasGauche.push_back(new Case(SO, G));
    plaineCoinBasGauche.push_back(new Case(SO,B));
    Endroit PCBasGauche("plaineBSC", plaineCoinBasGauche, lieu_plaine, nullptr);

    list<Case*> plaineGaucheHBasD;
    plaineGaucheHBasD.push_back(new Case(NO, G));
    plaineGaucheHBasD.push_back(new Case(C, nul));
    plaineGaucheHBasD.push_back(new Case(SE, B));
    Endroit PGaucheHBasD("plaineBSC", plaineGaucheHBasD, lieu_plaine, nullptr);

    list<Case*> routeBas;
    routeBas.push_back(new Case(S, B));
    Endroit RBas("plaineB", routeBas, lieu_route, nullptr);

    list<Case*> routeGauche_Bas;
    routeGauche_Bas.push_back(new Case(S, B));
    routeGauche_Bas.push_back(new Case(O, G));
    Endroit RGauche_Bas("plaineB", routeGauche_Bas, lieu_route, nullptr);

    list<Case*> routeGauche_Droite;
    routeGauche_Droite.push_back(new Case(E, D));
    routeGauche_Droite.push_back(new Case(O, G));
    routeGauche_Droite.push_back(new Case(C, nul));
    Endroit RGauche_Droite("plaineB", routeGauche_Droite, lieu_route, nullptr);


    list<Case*> routeDroite;
    routeDroite.push_back(new Case(E, D));
    Endroit RDroite("routeD", routeDroite, lieu_route, nullptr);

    list<Case*> routeGauche;
    routeGauche.push_back(new Case(O, G));
    Endroit RGauche("routeG", routeGauche, lieu_route, nullptr);

    list<Case*> riviereGauche_Droite;
    riviereGauche_Droite.push_back(new Case(E, D));
    riviereGauche_Droite.push_back(new Case(C, nul));
    riviereGauche_Droite.push_back(new Case(O, G));
    Endroit RiGauche_Droite("riviereGD", riviereGauche_Droite, lieu_riviere, nullptr);


    list<Case*> riviereGauche_Bas;
    riviereGauche_Bas.push_back(new Case(S, B));
    riviereGauche_Bas.push_back(new Case(O, G));
    Endroit RiGauche_Bas("riviereGB", riviereGauche_Bas, lieu_riviere, nullptr);

    list<Case*> abbayeCentre;
    abbayeCentre.push_back(new Case(C, nul));
    Endroit ACentre("plaineB", abbayeCentre, lieu_abbaye, nullptr);

    list<Case*> aubergeCentre;
    aubergeCentre.push_back(new Case(C, nul));
    Endroit AuCentre("plaineB", aubergeCentre, lieu_auberge, nullptr);

    list<Endroit*> listEndroit;

    list<Case*> lcases1;
    list<Case*> lcases2;
    list<Case*> lcases3;
    list<Case*> lcases4;
    list<Case*> lcases5;

    //tuile 1
    lcases1.push_back(new Case(NO, G));
    lcases1.push_back(new Case(NE, D));
    lcases1.push_back(new Case(E, D));
    lcases1.push_back(new Case(SE, D));
    lcases1.push_back(new Case(SO, G));
    lcases1.push_back(new Case(O, G));
    lcases1.push_back(new Case(C, nul));


    listEndroit.push_back(new Endroit("plaineSHB", lcases1, lieu_plaine, nullptr));
    listEndroit.push_back(new Endroit(VHaut));
    listEndroit.push_back(new Endroit(VBas));


    Tuile T1(listEndroit, i++);
    listEndroit.clear();
    lcases1.clear();

    //tuile2
    listEndroit.push_back(new Endroit(PBas));
    listEndroit.push_back(new Endroit(VSBas));

    Tuile T2(listEndroit, i++);
    listEndroit.clear();

    //tuile3
    lcases1.push_back(new Case(NO, G));
    lcases1.push_back(new Case(NO, H));
    lcases1.push_back(new Case(N, H));
    lcases1.push_back(new Case(NE, H));
    lcases1.push_back(new Case(NE, D));
    lcases1.push_back(new Case(E, D));
    lcases1.push_back(new Case(SE, D));
    lcases1.push_back(new Case(SE, B));
    lcases1.push_back(new Case(S, B));
    lcases1.push_back(new Case(SO,B));
    lcases1.push_back(new Case(SO, G));
    lcases1.push_back(new Case(O, G));
    lcases1.push_back(new Case(C, nul));

    listEndroit.push_back(new Endroit("villeE", lcases1, lieu_ville, nullptr));

    Tuile T3(listEndroit, i++);
    listEndroit.clear();
    lcases1.clear();

    //tuile4
    lcases1.push_back(new Case(SO,B));
    lcases2.push_back(new Case(SE, B));

    listEndroit.push_back(new Endroit(VSBas));
    listEndroit.push_back(new Endroit("plaineCoinSO_B", lcases1, lieu_plaine, nullptr));
    listEndroit.push_back(new Endroit("plaineCoinSE_B", lcases2, lieu_plaine, nullptr));
    listEndroit.push_back(new Endroit(RBas));

    Tuile T4(listEndroit, i++);
    listEndroit.clear();
    lcases1.clear();
    lcases2.clear();

    //Tuile5
    listEndroit.push_back(new Endroit(VHaut));
    listEndroit.push_back(new Endroit(VDroite));
    listEndroit.push_back(new Endroit(PTBasGauche));


    Tuile T5(listEndroit, i++);
    listEndroit.clear();
    lcases1.clear();

    //Tuile6
    lcases1.push_back(new Case(NO, G));
    lcases1.push_back(new Case(NO, H));
    lcases1.push_back(new Case(N, H));
    lcases1.push_back(new Case(NE, H));
    lcases1.push_back(new Case(NE, D));
    lcases1.push_back(new Case(E, D));
    lcases1.push_back(new Case(SE, D));
    lcases1.push_back(new Case(SE, B));
    lcases1.push_back(new Case(SO,B));
    lcases1.push_back(new Case(SO, G));
    lcases1.push_back(new Case(O, G));

    listEndroit.push_back(new Endroit(ACentre));
    listEndroit.push_back(new Endroit(RBas));
    listEndroit.push_back(new Endroit("plaineSCB", lcases1, lieu_plaine, nullptr));

    Tuile T6(listEndroit, i++);
    listEndroit.clear();
    lcases1.clear();

    //Tuile 7
    listEndroit.push_back(new Endroit(VHautDroite));
    listEndroit.push_back(new Endroit(PCBasGauche));
    listEndroit.push_back(new Endroit(PGaucheHBasD));
    listEndroit.push_back(new Endroit(RGauche_Bas));

    Tuile T7(listEndroit, i++);
    listEndroit.clear();

    //Tuile 8
    listEndroit.push_back(new Endroit(RGauche_Droite));
    listEndroit.push_back(new Endroit(PRBas));
    listEndroit.push_back(new Endroit(PRHaut));

    Tuile T8(listEndroit, i++);
    listEndroit.clear();

    //Tuile 9
    lcases1.push_back(new Case(NO, G));
    lcases1.push_back(new Case(NO, H));
    lcases1.push_back(new Case(N, H));
    lcases1.push_back(new Case(NE, H));
    lcases1.push_back(new Case(NE, D));
    lcases1.push_back(new Case(E, D));
    lcases1.push_back(new Case(SE, D));
    lcases1.push_back(new Case(SE, B));
    lcases1.push_back(new Case(C, nul));

    listEndroit.push_back(new Endroit(RGauche_Bas));
    listEndroit.push_back(new Endroit(PCBasGauche));
    listEndroit.push_back(new Endroit("plainelibre", lcases1, lieu_plaine, nullptr));

    Tuile T9(listEndroit, i++);
    listEndroit.clear();
    lcases1.clear();

    //Tuile 10
    lcases1.push_back(new Case(NO, G));
    lcases1.push_back(new Case(NE, D));
    lcases1.push_back(new Case(E, D));
    lcases1.push_back(new Case(SE, D));
    lcases1.push_back(new Case(SE, B));
    lcases1.push_back(new Case(C, nul));

    listEndroit.push_back(new Endroit(RGauche_Bas));
    listEndroit.push_back(new Endroit(PCBasGauche));
    listEndroit.push_back(new Endroit("plainelibre", lcases1, lieu_plaine, nullptr));
    listEndroit.push_back(new Endroit(VHaut));

    Tuile T10(listEndroit, i++);
    listEndroit.clear();
    lcases1.clear();

    //tuile 11
    lcases1.push_back(new Case(NE, D));
    lcases1.push_back(new Case(NO, G));
    lcases1.push_back(new Case(O, G));
    lcases1.push_back(new Case(SO, G));
    lcases1.push_back(new Case(SO,B));
    lcases1.push_back(new Case(C, nul));

    lcases2.push_back(new Case(E, D));
    lcases2.push_back(new Case(S, B));


    listEndroit.push_back(new Endroit(PCBasDroit));
    listEndroit.push_back(new Endroit("plainelibre", lcases1, lieu_plaine, nullptr));
    listEndroit.push_back(new Endroit("routeBasDroite", lcases2, lieu_route, nullptr));
    listEndroit.push_back(new Endroit(VHaut));

    Tuile T11(listEndroit, i++);
    listEndroit.clear();
    lcases1.clear();
    lcases2.clear();

    //tuile 12
    lcases1.push_back(new Case(NE, D));
    lcases1.push_back(new Case(NO, G));
    listEndroit.push_back(new Endroit(RGauche_Droite));
    listEndroit.push_back(new Endroit(PRBas));
    listEndroit.push_back(new Endroit("plainelibre", lcases1, lieu_plaine, nullptr));
    listEndroit.push_back(new Endroit(VHaut));

    Tuile T12(listEndroit, i++);
    listEndroit.clear();
    lcases1.clear();

    //tuile 13
    lcases1.push_back(new Case(NO, G));
    lcases1.push_back(new Case(NE, D));
    lcases1.push_back(new Case(E, D));
    lcases1.push_back(new Case(SE, D));
    lcases1.push_back(new Case(SO, G));
    lcases1.push_back(new Case(O, G));
    lcases1.push_back(new Case(C, nul));

    lcases2.push_back(new Case(NO, H));
    lcases2.push_back(new Case(N, H));
    lcases2.push_back(new Case(NE, H));

    listEndroit.push_back(new Endroit(PBas));
    listEndroit.push_back(new Endroit("villelibre", lcases1, lieu_ville, nullptr));
    listEndroit.push_back(new Endroit("plaineH", lcases2, lieu_plaine, nullptr));

    Tuile T13(listEndroit, i++);
    listEndroit.clear();
    lcases1.clear();
    lcases2.clear();


    //tuile 14
    listEndroit.push_back(new Endroit(PTBasGauche));
    listEndroit.push_back(new Endroit(VTHautDroit));

    Tuile T14(listEndroit, i++);
    listEndroit.clear();

    //tuile 15
    lcases1.push_back(new Case(NO, G));
    lcases1.push_back(new Case(NO, H));
    lcases1.push_back(new Case(N, H));
    lcases1.push_back(new Case(NE, H));
    lcases1.push_back(new Case(NE, D));
    lcases1.push_back(new Case(E, D));
    lcases1.push_back(new Case(SE, D));
    lcases1.push_back(new Case(SE, B));
    lcases1.push_back(new Case(S, B));
    lcases1.push_back(new Case(SO,B));
    lcases1.push_back(new Case(SO, G));
    lcases1.push_back(new Case(O, G));

    listEndroit.push_back(new Endroit(ACentre));
    listEndroit.push_back(new Endroit("plainelibre", lcases1, lieu_plaine, nullptr));

    Tuile T15(listEndroit, i++);
    listEndroit.clear();
    lcases1.clear();

    //Tuile 16
    lcases1.push_back(new Case(NO, G));
    lcases1.push_back(new Case(NE, D));
    lcases1.push_back(new Case(E, D));
    lcases1.push_back(new Case(SE, D));
    lcases1.push_back(new Case(SE, B));
    lcases1.push_back(new Case(S, B));
    lcases1.push_back(new Case(SO,B));
    lcases1.push_back(new Case(SO, G));
    lcases1.push_back(new Case(O, G));
    lcases1.push_back(new Case(C, nul));

    listEndroit.push_back(new Endroit(VHaut));
    listEndroit.push_back(new Endroit("plainelibre", lcases1, lieu_plaine, nullptr));

    Tuile T16(listEndroit, i++);
    listEndroit.clear();
    lcases1.clear();

    //tuile 17

    listEndroit.push_back(new Endroit(AuCentre));
    listEndroit.push_back(new Endroit(PRHaut));
    listEndroit.push_back(new Endroit(RBas));
    listEndroit.push_back(new Endroit(RDroite));
    listEndroit.push_back(new Endroit(RGauche));
    listEndroit.push_back(new Endroit(PCBasDroit));
    listEndroit.push_back(new Endroit(PCBasGauche));

    Tuile T17(listEndroit, i++);
    listEndroit.clear();
    lcases1.clear();

    //tuile 18
    lcases1.push_back(new Case(NO, G));
    lcases1.push_back(new Case(NE, D));


    listEndroit.push_back(new Endroit(AuCentre));
    listEndroit.push_back(new Endroit(RBas));
    listEndroit.push_back(new Endroit(RDroite));
    listEndroit.push_back(new Endroit(RGauche));
    listEndroit.push_back(new Endroit(PCBasDroit));
    listEndroit.push_back(new Endroit(PCBasGauche));
    listEndroit.push_back(new Endroit(VHaut));
    listEndroit.push_back(new Endroit("plainelibre", lcases1, lieu_plaine, nullptr));

    Tuile T18(listEndroit, i++);
    listEndroit.clear();
    lcases1.clear();

    //tuile 19
    lcases1.push_back(new Case(NO, G));
    lcases1.push_back(new Case(NO, H));

    lcases2.push_back(new Case(NE, H));
    lcases2.push_back(new Case(NE, D));

    lcases3.push_back(new Case(N, H));

    listEndroit.push_back(new Endroit("plaineCHG", lcases1, lieu_plaine, nullptr));
    listEndroit.push_back(new Endroit("plaineCHD", lcases2, lieu_plaine, nullptr));
    listEndroit.push_back(new Endroit("RH", lcases3, lieu_route, nullptr));
    listEndroit.push_back(new Endroit(AuCentre));
    listEndroit.push_back(new Endroit(RBas));
    listEndroit.push_back(new Endroit(RDroite));
    listEndroit.push_back(new Endroit(RGauche));
    listEndroit.push_back(new Endroit(PCBasDroit));
    listEndroit.push_back(new Endroit(PCBasGauche));


    Tuile T19(listEndroit, i++);
    listEndroit.clear();
    lcases1.clear();
    lcases2.clear();
    lcases3.clear();

    //tuile 20
    listEndroit.push_back(new Endroit(PCBasGauche));
    listEndroit.push_back(new Endroit(VTHautDroit));
    listEndroit.push_back(new Endroit(PGaucheHBasD));
    listEndroit.push_back(new Endroit(RiGauche_Bas));


    Tuile T20(listEndroit, i++);
    listEndroit.clear();

    //tuile 21
    lcases1.push_back(new Case(C, nul));

    lcases2.push_back(new Case(S, B));

    lcases3.push_back(new Case(NO, G));
    lcases3.push_back(new Case(NO, H));
    lcases3.push_back(new Case(N, H));
    lcases3.push_back(new Case(NE, H));
    lcases3.push_back(new Case(NE, D));
    lcases3.push_back(new Case(E, D));
    lcases3.push_back(new Case(SE, D));
    lcases3.push_back(new Case(SE, B));
    lcases3.push_back(new Case(SO,B));
    lcases3.push_back(new Case(SO, G));
    lcases3.push_back(new Case(O, G));

    listEndroit.push_back(new Endroit("source", lcases1, lieu_source, nullptr));
    listEndroit.push_back(new Endroit("riviereB", lcases2, lieu_riviere, nullptr));
    listEndroit.push_back(new Endroit("Plainelibre", lcases3, lieu_plaine, nullptr));

    Tuile T21(listEndroit, i++);
    listEndroit.clear();
    lcases1.clear();
    lcases2.clear();
    lcases3.clear();

    //tuile 22
    listEndroit.push_back(new Endroit(RiGauche_Droite));
    listEndroit.push_back(new Endroit(PRBas));
    listEndroit.push_back(new Endroit(PRHaut));

    Tuile T22(listEndroit, i++);
    listEndroit.clear();


    //tuile 23
    lcases1.push_back(new Case(C, nul));
    lcases1.push_back(new Case(NO, G));
    lcases1.push_back(new Case(NO, H));
    lcases1.push_back(new Case(N, H));
    lcases1.push_back(new Case(NE, H));
    lcases1.push_back(new Case(NE, D));
    lcases1.push_back(new Case(E, D));
    lcases1.push_back(new Case(SE, D));
    lcases1.push_back(new Case(SE, B));


    listEndroit.push_back(new Endroit(RiGauche_Bas));
    listEndroit.push_back(new Endroit(PCBasGauche));
    listEndroit.push_back(new Endroit("Plainelibre", lcases1, lieu_plaine, nullptr));

    Tuile T23(listEndroit, i++);
    listEndroit.clear();
    lcases1.clear();



    //tuile 24
    lcases1.push_back(new Case(NE, D));
    lcases1.push_back(new Case(NO, G));

    lcases2.push_back(new Case(SE, D));
    lcases2.push_back(new Case(SO, G));



    listEndroit.push_back(new Endroit(RiGauche_Droite));
    listEndroit.push_back(new Endroit(VHaut));
    listEndroit.push_back(new Endroit(VBas));
    listEndroit.push_back(new Endroit("Plainelibre", lcases1, lieu_plaine, nullptr));
    listEndroit.push_back(new Endroit("Plainelibre", lcases2, lieu_plaine, nullptr));

    Tuile T24(listEndroit, i++);
    listEndroit.clear();
    lcases1.clear();
    lcases2.clear();


    //tuile 25
    lcases1.push_back(new Case(E, D));
    lcases1.push_back(new Case(O, G));

    listEndroit.push_back(new Endroit(PRHaut));
    listEndroit.push_back(new Endroit(PCBasDroit));
    listEndroit.push_back(new Endroit(PCBasGauche));
    listEndroit.push_back(new Endroit(ACentre));
    listEndroit.push_back(new Endroit("riviere", lcases1, lieu_riviere, nullptr));
    listEndroit.push_back(new Endroit(RBas));

    Tuile T25(listEndroit, i++);
    listEndroit.clear();
    lcases1.clear();

    //tuile 26
    lcases1.push_back(new Case(N,H));
    lcases1.push_back(new Case(C, nul));
    lcases1.push_back(new Case(S, B));

    lcases2.push_back(new Case(E, D));
    lcases2.push_back(new Case(O, G));

    lcases3.push_back(new Case(NO, H));
    lcases3.push_back(new Case(NO, G));

    lcases4.push_back(new Case(NE, D));
    lcases4.push_back(new Case(NE, H));

    listEndroit.push_back(new Endroit(PCBasDroit));
    listEndroit.push_back(new Endroit(PCBasGauche));
    listEndroit.push_back(new Endroit("routeHB", lcases1, lieu_route, nullptr));
    listEndroit.push_back(new Endroit("riviere", lcases2, lieu_riviere, nullptr));
    listEndroit.push_back(new Endroit("plaineCoin", lcases3, lieu_plaine, nullptr));
    listEndroit.push_back(new Endroit("plaineCoin", lcases4, lieu_plaine, nullptr));

    Tuile T26(listEndroit, i++);
    listEndroit.clear();
    lcases1.clear();
    lcases2.clear();
    lcases3.clear();
    lcases4.clear();

    //tuile 27
    lcases1.push_back(new Case(NO, H));
    lcases1.push_back(new Case(NO, G));
    lcases1.push_back(new Case(SE, B));
    lcases1.push_back(new Case(SE, D));
    lcases1.push_back(new Case(C, nul));

    lcases2.push_back(new Case(NE, D));
    lcases2.push_back(new Case(NE, H));

    lcases3.push_back(new Case(N, H));
    lcases3.push_back(new Case(E, D));

    listEndroit.push_back(new Endroit(RiGauche_Bas));
    listEndroit.push_back(new Endroit(PCBasGauche));
    listEndroit.push_back(new Endroit("plaineautre", lcases1, lieu_plaine, nullptr));
    listEndroit.push_back(new Endroit("route", lcases3, lieu_route, nullptr));
    listEndroit.push_back(new Endroit("plaine", lcases2, lieu_plaine, nullptr));

    Tuile T27(listEndroit, i++);
    listEndroit.clear();
    lcases1.clear();
    lcases2.clear();
    lcases3.clear();


    //tuile 28
    lcases1.push_back(new Case(C, nul));
    lcases1.push_back(new Case(S, B));

    lcases2.push_back(new Case(E, D));
    lcases2.push_back(new Case(O, G));

    lcases3.push_back(new Case(NO, G));

    lcases4.push_back(new Case(NE, D));

    listEndroit.push_back(new Endroit(VHaut));
    listEndroit.push_back(new Endroit(PCBasDroit));
    listEndroit.push_back(new Endroit(PCBasGauche));
    listEndroit.push_back(new Endroit("route", lcases1, lieu_route, nullptr));
    listEndroit.push_back(new Endroit("riviere", lcases2, lieu_riviere, nullptr));
    listEndroit.push_back(new Endroit("plainelibre", lcases3, lieu_plaine, nullptr));
    listEndroit.push_back(new Endroit("plainelibre", lcases4, lieu_plaine, nullptr));

    Tuile T28(listEndroit, i++);
    listEndroit.clear();
    lcases1.clear();
    lcases2.clear();
    lcases3.clear();
    lcases4.clear();

    unsigned int nbt = 0;
    Tuile* tInitialisation;

    for (nbt = 0;nbt < 3;nbt++) {
        tInitialisation = new Tuile;
        *tInitialisation = T1;
        ajouterTuile(tInitialisation);
    }
    for (nbt = 0;nbt <4 ;nbt++)
    {
        tInitialisation = new Tuile;
        *tInitialisation = T2;
        ajouterTuile(tInitialisation);
    }
    for (nbt = 0;nbt <1 ;nbt++)
    {
        tInitialisation = new Tuile;
        *tInitialisation = T3;
        ajouterTuile(tInitialisation);
    }

    for (nbt = 0;nbt <3 ;nbt++)
    {
        tInitialisation = new Tuile;
        *tInitialisation = T4;
        ajouterTuile(tInitialisation);
    }
    for (nbt = 0;nbt < 2;nbt++)
    {
        tInitialisation = new Tuile;
        *tInitialisation = T5;
        ajouterTuile(tInitialisation);
    }

    for (nbt = 0;nbt < 2;nbt++)
    {
        tInitialisation = new Tuile;
        *tInitialisation = T6;
        ajouterTuile(tInitialisation);
    }
    for (nbt = 0;nbt < 5;nbt++)
    {
        tInitialisation = new Tuile;
        *tInitialisation = T7;
        ajouterTuile(tInitialisation);
    }
    for (nbt = 0;nbt < 8;nbt++)
    {
        tInitialisation = new Tuile;
        *tInitialisation = T8;
        ajouterTuile(tInitialisation);
    }
    for (nbt = 0;nbt < 9;nbt++)
    {
        tInitialisation = new Tuile;
        *tInitialisation = T9;
        ajouterTuile(tInitialisation);
    }
    for (nbt = 0;nbt < 3;nbt++)
    {
        tInitialisation = new Tuile;
        *tInitialisation = T10;
        ajouterTuile(tInitialisation);
    }

    for (nbt = 0;nbt < 3;nbt++)
    {
        tInitialisation = new Tuile;
        *tInitialisation = T11;
        ajouterTuile(tInitialisation);
    }
    for (nbt = 0;nbt < 4;nbt++)
    {
        tInitialisation = new Tuile;
        *tInitialisation = T12;
        ajouterTuile(tInitialisation);
    }
    for (nbt = 0;nbt < 3;nbt++)
    {
        tInitialisation = new Tuile;
        *tInitialisation = T13;
        ajouterTuile(tInitialisation);
    }
    for (nbt = 0;nbt < 5;nbt++)
    {
        tInitialisation = new Tuile;
        *tInitialisation = T14;
        ajouterTuile(tInitialisation);
    }
    for (nbt = 0;nbt < 4;nbt++)
    {
        tInitialisation = new Tuile;
        *tInitialisation = T15;
        ajouterTuile(tInitialisation);
    }
    for (nbt = 0;nbt < 5;nbt++)
    {
        tInitialisation = new Tuile;
        *tInitialisation = T16;
        ajouterTuile(tInitialisation);
    }
    for (nbt = 0;nbt < 4;nbt++)
    {
        tInitialisation = new Tuile;
        *tInitialisation = T17;
        ajouterTuile(tInitialisation);
    }
    for (nbt = 0;nbt < 3;nbt++) {
        tInitialisation = new Tuile;
        *tInitialisation = T18;
        ajouterTuile(tInitialisation);
    }

    for (nbt = 0;nbt < 1;nbt++) {
        tInitialisation = new Tuile;
        *tInitialisation = T19;
        ajouterTuile(tInitialisation);
    }
    for (nbt = 0;nbt < 1;nbt++) {
        tInitialisation = new Tuile;
        *tInitialisation = T20;
        ajouterTuile(tInitialisation);
    }

    for (nbt = 0;nbt < 2;nbt++) {
        tInitialisation = new Tuile;
        *tInitialisation = T21;
        ajouterTuile(tInitialisation);
    }

    for (nbt = 0;nbt < 2;nbt++) {
        tInitialisation = new Tuile;
        *tInitialisation = T22;
        ajouterTuile(tInitialisation);
    }

    for (nbt = 0;nbt < 2;nbt++) {
        tInitialisation = new Tuile;
        *tInitialisation = T23;
        ajouterTuile(tInitialisation);
    }

    for (nbt = 0;nbt < 1;nbt++) {
        tInitialisation = new Tuile;
        *tInitialisation = T24;
        ajouterTuile(tInitialisation);
    }
    for (nbt = 0;nbt < 1;nbt++) {
        tInitialisation = new Tuile;
        *tInitialisation = T25;
        ajouterTuile(tInitialisation);
    }
    for (nbt = 0;nbt < 1;nbt++) {
        tInitialisation = new Tuile;
        *tInitialisation = T26;
        ajouterTuile(tInitialisation);
    }

    for (nbt = 0;nbt < 1;nbt++) {
        tInitialisation = new Tuile;
        *tInitialisation = T27;
        ajouterTuile(tInitialisation);
    }
    for (nbt = 0;nbt < 1;nbt++) {
        tInitialisation = new Tuile;
        *tInitialisation = T28;
        ajouterTuile(tInitialisation);
    }
}



/*
------------------------   AubergesEtCathedrales ----------------------
*/

AubergesEtCathedrales::AubergesEtCathedrales() {

    ajouterMeeple(new Meeple("Double", 1));
    ajouterMeeple(new Meeple("Abbe", 1));

        list<Case*> lcase1;
        list<Case*> lcase2;
        list<Case*> lcase3;
        list<Case*> lcase4;
        list<Case*> lcase5;

        list<Endroit*> lendroit1;

        Lieu* lieu_plaine = new Plaine(1);
        Lieu* lieu_route = new Route(1);
        Lieu* lieu_ville = new Ville(1);

        Lieu* lieu_abbaye = new Abbaye(1);
        Lieu* lieu_buisson = new Buisson(1);
        Lieu* lieu_village = new Village(1);
        Lieu* lieu_cathedrale = new Cathedrale(1);

        Tuile* tInitialisation;

        unsigned int i = 29;

        //Tuile 1
        Case* c = new CaseCatEtAuberge(O, G, 1);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(C, nul, 1);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(S, B, 1);
        lcase1.push_back(c);

        Endroit* e = new EndroitCatEtAuberge("route_bas_gauche", lcase1, lieu_route, nullptr, 1);
        lendroit1.push_back(e);
        lcase1.clear();


        c = new CaseCatEtAuberge(N, H, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(NE, H, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(NE, D, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(E, D, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(SE, D, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(SE, B, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(NO, G, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(NO, H, 0);
        lcase1.push_back(c);

        e = new EndroitCatEtAuberge("plaine_sans_route_bas_gauche", lcase1, lieu_plaine, nullptr, 0);
        lendroit1.push_back(e);
        lcase1.clear();


        c = new CaseCatEtAuberge(SO, B, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(SO, G, 0);
        lcase1.push_back(c);

        e = new EndroitCatEtAuberge("plaine_bas_gauche", lcase1, lieu_plaine, nullptr, 0);
        lendroit1.push_back(e);
        lcase1.clear();


        tInitialisation = new tuileCatEtAuberge(lendroit1, i++);
        ajouterTuile(tInitialisation);
        lendroit1.clear();

        //Tuile 2

        c = new CaseCatEtAuberge(E, D, 1);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(C, nul, 1);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(O, G, 1);
        lcase1.push_back(c);

        e = new EndroitCatEtAuberge("route_traversant_G_D", lcase1, lieu_route, nullptr, 1);
        lendroit1.push_back(e);
        lcase1.clear();


        c = new CaseCatEtAuberge(N, H, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(NE, H, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(NE, D, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(NO, G, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(NO, H, 0);
        lcase1.push_back(c);

        e = new EndroitCatEtAuberge("plaine_haut", lcase1, lieu_plaine, nullptr, 0);
        lendroit1.push_back(e);
        lcase1.clear();


        c = new CaseCatEtAuberge(SE, D, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(SE, B, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(S, B, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(SO, B, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(SO, G, 0);
        lcase1.push_back(c);

        e = new EndroitCatEtAuberge("plaine_bas", lcase1, lieu_plaine, nullptr, 0);
        lendroit1.push_back(e);
        lcase1.clear();

        /*e = new EndroitCatEtAuberge("plaine_sans_route_traversante", lcase1, lieu_plaine, nullptr, 0);
        lendroit1.push_back(e);*/

        tInitialisation = new tuileCatEtAuberge(lendroit1, i++);
        ajouterTuile(tInitialisation);
        lendroit1.clear();



        //Tuile 3

        c = new CaseCatEtAuberge(E, D, 0);
        lcase1.push_back(c);

        e = new EndroitCatEtAuberge("route_O", lcase1, lieu_route, nullptr, 1);
        lendroit1.push_back(e);
        lcase1.clear();


        c = new CaseCatEtAuberge(O, G, 0);
        lcase1.push_back(c);

        e = new EndroitCatEtAuberge("route_E", lcase1, lieu_route, nullptr, 1);
        lendroit1.push_back(e);
        lcase1.clear();


        c = new CaseCatEtAuberge(S, B, 0);
        lcase1.push_back(c);

        e = new EndroitCatEtAuberge("route_S", lcase1, lieu_route, nullptr, 0);
        lendroit1.push_back(e);
        lcase1.clear();


        c = new CaseCatEtAuberge(N, H, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(NE, H, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(NE, D, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(NO, G, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(NO, H, 0);
        lcase1.push_back(c);

        e = new EndroitCatEtAuberge("plaine_N", lcase1, lieu_plaine, nullptr, 0);
        lendroit1.push_back(e);
        lcase1.clear();


        c = new CaseCatEtAuberge(SE, D, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(SE, B, 0);
        lcase1.push_back(c);

        e = new EndroitCatEtAuberge("plaine_SE", lcase1, lieu_plaine, nullptr, 0);
        lendroit1.push_back(e);
        lcase1.clear();


        c = new CaseCatEtAuberge(SO, B, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(SO, G, 0);
        lcase1.push_back(c);

        e = new EndroitCatEtAuberge("plaine_SO", lcase1, lieu_plaine, nullptr, 0);
        lendroit1.push_back(e);
        lcase1.clear();



        c = new CaseCatEtAuberge(C, nul, 0);
        lcase1.push_back(c);

        e = new EndroitCatEtAuberge("buisson_C", lcase1, lieu_buisson, nullptr, 0);
        lendroit1.push_back(e);
        lcase1.clear();

        tInitialisation = new tuileCatEtAuberge(lendroit1, i++);
        ajouterTuile(tInitialisation);
        lendroit1.clear();


        //Tuile 4

        c = new CaseCatEtAuberge(E, D, 0);
        lcase1.push_back(c);

        e = new EndroitCatEtAuberge("route_E", lcase1, lieu_route, nullptr, 0);
        lendroit1.push_back(e);
        lcase1.clear();


        c = new CaseCatEtAuberge(O, G, 0);
        lcase1.push_back(c);

        e = new EndroitCatEtAuberge("route_O", lcase1, lieu_route, nullptr, 0);
        lendroit1.push_back(e);
        lcase1.clear();


        c = new CaseCatEtAuberge(C, nul, 0);
        lcase1.push_back(c);

        e = new EndroitCatEtAuberge("monastere", lcase1, lieu_abbaye, nullptr, 0);
        lendroit1.push_back(e);
        lcase1.clear();


        c = new CaseCatEtAuberge(N, H, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(NE, H, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(NE, D, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(NO, G, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(NO, H, 0);
        lcase1.push_back(c);

        e = new EndroitCatEtAuberge("plaine_haut", lcase1, lieu_plaine, nullptr, 0);
        lendroit1.push_back(e);
        lcase1.clear();


        c = new CaseCatEtAuberge(SE, D, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(SE, B, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(S, B, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(SO, B, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(SO, G, 0);
        lcase1.push_back(c);

        e = new EndroitCatEtAuberge("plaine_bas", lcase1, lieu_plaine, nullptr, 0);
        lendroit1.push_back(e);
        lcase1.clear();

        tInitialisation = new tuileCatEtAuberge(lendroit1, i++);
        ajouterTuile(tInitialisation);
        lendroit1.clear();



        //Tuile 5

        c = new CaseCatEtAuberge(N, H, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(O, G, 0);
        lcase1.push_back(c);

        e = new EndroitCatEtAuberge("route_O_to_N", lcase1, lieu_route, nullptr, 0);
        lendroit1.push_back(e);
        lcase1.clear();


        c = new CaseCatEtAuberge(S, B, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(E, D, 0);
        lcase1.push_back(c);

        e = new EndroitCatEtAuberge("route_S_to_E", lcase1, lieu_route, nullptr, 0);
        lendroit1.push_back(e);
        lcase1.clear();




        c = new CaseCatEtAuberge(SO, B, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(SO, G, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(NE, G, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(NE, H, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(C, nul, 0);
        lcase1.push_back(c);

        e = new EndroitCatEtAuberge("plaine_diago_SO_NE", lcase1, lieu_plaine, nullptr, 0);
        lendroit1.push_back(e);
        lcase1.clear();


        c = new CaseCatEtAuberge(NO, H, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(NO, D, 0);
        lcase1.push_back(c);

        e = new EndroitCatEtAuberge("plaine_NO", lcase1, lieu_plaine, nullptr, 0);
        lendroit1.push_back(e);
        lcase1.clear();



        c = new CaseCatEtAuberge(SE, D, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(SE, B, 0);
        lcase1.push_back(c);

        e = new EndroitCatEtAuberge("plaine_SE", lcase1, lieu_plaine, nullptr, 0);
        lendroit1.push_back(e);
        lcase1.clear();


        tInitialisation = new tuileCatEtAuberge(lendroit1, i++);
        ajouterTuile(tInitialisation);
        lendroit1.clear();



        //Tuile 6

        c = new CaseCatEtAuberge(N, H, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(NE, H, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(SO, G, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(O, G, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(NO, G, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(NO, H, 0);
        lcase1.push_back(c);

        e = new EndroitCatEtAuberge("ville_haut_gauche", lcase1, lieu_ville, nullptr, 0);
        lendroit1.push_back(e);
        lcase1.clear();


        c = new CaseCatEtAuberge(E, D, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(C, nul, 0);
        lcase1.push_back(c);

        e = new EndroitCatEtAuberge("route_C_et_E", lcase1, lieu_route, nullptr, 0);
        lendroit1.push_back(e);
        lcase1.clear();


        c = new CaseCatEtAuberge(NE, D, 0);
        lcase1.push_back(c);

        e = new EndroitCatEtAuberge("plaine_NE_D", lcase1, lieu_plaine, nullptr, 0);
        lendroit1.push_back(e);
        lcase1.clear();


        c = new CaseCatEtAuberge(SE, D, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(SE, B, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(S, B, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(SO, B, 0);
        lcase1.push_back(c);
        e = new EndroitCatEtAuberge("plaine_bas_sans_SO_G", lcase1, lieu_plaine, nullptr, 0);
        lendroit1.push_back(e);
        lcase1.clear();

        tInitialisation = new tuileCatEtAuberge(lendroit1, i++);
        ajouterTuile(tInitialisation);
        lendroit1.clear();

        //Tuile 7

        c = new CaseCatEtAuberge(NE, D, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(E, D, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(C, nul, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(SE, D, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(SE, B, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(S, B, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(SO, B, 0);
        lcase1.push_back(c);

        e = new EndroitCatEtAuberge("plaine_bas_droit", lcase1, lieu_plaine, nullptr, 0);
        lendroit1.push_back(e);
        lcase1.clear();


        c = new CaseCatEtAuberge(NO, H, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(N, H, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(NE, H, 0);
        lcase1.push_back(c);

        e = new EndroitCatEtAuberge("plaine_haut", lcase1, lieu_plaine, nullptr, 0);
        lendroit1.push_back(e);
        lcase1.clear();



        c = new CaseCatEtAuberge(SO, G, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(O, G, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(NO, G, 0);
        lcase1.push_back(c);


        e = new EndroitCatEtAuberge("ville_haut_gauche", lcase1, lieu_ville, nullptr, 0);
        lendroit1.push_back(e);
        lcase1.clear();

        tInitialisation = new tuileCatEtAuberge(lendroit1, i++);
        ajouterTuile(tInitialisation);
        lendroit1.clear();


        //Tuile 8

        c = new CaseCatEtAuberge(C, nul, 0);
        lcase1.push_back(c);

        e = new EndroitCatEtAuberge("plaine_centre", lcase1, lieu_plaine, nullptr, 0);
        lendroit1.push_back(e);
        lcase1.clear();


        c = new CaseCatEtAuberge(NO, H, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(N, H, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(NE, H, 0);
        lcase1.push_back(c);

        e = new EndroitCatEtAuberge("ville_haut", lcase1, lieu_ville, nullptr, 0);
        lendroit1.push_back(e);
        lcase1.clear();



        c = new CaseCatEtAuberge(NE, D, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(E, D, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(SE, D, 0);
        lcase1.push_back(c);

        e = new EndroitCatEtAuberge("ville_droite", lcase1, lieu_ville, nullptr, 0);
        lendroit1.push_back(e);
        lcase1.clear();



        c = new CaseCatEtAuberge(SE, B, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(S, B, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(SO, B, 0);
        lcase1.push_back(c);

        e = new EndroitCatEtAuberge("ville_bas", lcase1, lieu_ville, nullptr, 0);
        lendroit1.push_back(e);
        lcase1.clear();



        c = new CaseCatEtAuberge(SO, G, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(O, G, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(NO, G, 0);
        lcase1.push_back(c);

        e = new EndroitCatEtAuberge("ville_gauche", lcase1, lieu_ville, nullptr, 0);
        lendroit1.push_back(e);
        lcase1.clear();

        tInitialisation = new tuileCatEtAuberge(lendroit1, i++);
        ajouterTuile(tInitialisation);
        lendroit1.clear();


        //Tuile 9

        c = new CaseCatEtAuberge(SE, B, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(S, B, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(SO, B, 0);
        lcase1.push_back(c);

        e = new EndroitCatEtAuberge("ville_bas", lcase1, lieu_ville, nullptr, 0);
        lendroit1.push_back(e);
        lcase1.clear();


        c = new CaseCatEtAuberge(NO, H, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(N, H, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(NE, H, 0);
        lcase1.push_back(c);

        e = new EndroitCatEtAuberge("ville_haut", lcase1, lieu_ville, nullptr, 0);
        lendroit1.push_back(e);
        lcase1.clear();


        c = new CaseCatEtAuberge(C, nul, 0);
        lcase1.push_back(c);

        e = new EndroitCatEtAuberge("village_C", lcase1, lieu_village, nullptr, 0);
        lendroit1.push_back(e);
        lcase1.clear();


        c = new CaseCatEtAuberge(E, D, 0);
        lcase1.push_back(c);

        e = new EndroitCatEtAuberge("route_E", lcase1, lieu_route, nullptr, 0);
        lendroit1.push_back(e);
        lcase1.clear();


        c = new CaseCatEtAuberge(O, G, 0);
        lcase1.push_back(c);

        e = new EndroitCatEtAuberge("route_O", lcase1, lieu_route, nullptr, 0);
        lendroit1.push_back(e);
        lcase1.clear();


        c = new CaseCatEtAuberge(NE, D, 0);
        lcase1.push_back(c);

        e = new EndroitCatEtAuberge("plaine_NE", lcase1, lieu_plaine, nullptr, 0);
        lendroit1.push_back(e);
        lcase1.clear();


        c = new CaseCatEtAuberge(SE, D, 0);
        lcase1.push_back(c);

        e = new EndroitCatEtAuberge("plaine_SE", lcase1, lieu_plaine, nullptr, 0);
        lendroit1.push_back(e);
        lcase1.clear();


        c = new CaseCatEtAuberge(SO, G, 0);
        lcase1.push_back(c);

        e = new EndroitCatEtAuberge("plaine_SO", lcase1, lieu_plaine, nullptr, 0);
        lendroit1.push_back(e);
        lcase1.clear();


        c = new CaseCatEtAuberge(NO, G, 0);
        lcase1.push_back(c);

        e = new EndroitCatEtAuberge("plaine_NO", lcase1, lieu_plaine, nullptr, 0);
        lendroit1.push_back(e);
        lcase1.clear();

        tInitialisation = new tuileCatEtAuberge(lendroit1, i++);
        ajouterTuile(tInitialisation);
        lendroit1.clear();

        //Tuile 10

        c = new CaseCatEtAuberge(NO, H, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(N, H, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(NE, H, 0);
        lcase1.push_back(c);

        e = new EndroitCatEtAuberge("ville_haut", lcase1, lieu_ville, nullptr, 0);
        lendroit1.push_back(e);
        lcase1.clear();



        c = new CaseCatEtAuberge(S, B, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(C, nul, 0);
        lcase1.push_back(c);

        e = new EndroitCatEtAuberge("route_centre_bas", lcase1, lieu_route, nullptr, 0);
        lendroit1.push_back(e);
        lcase1.clear();


        c = new CaseCatEtAuberge(NE, D, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(E, D, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(SE, D, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(SE, B, 0);
        lcase1.push_back(c);

        e = new EndroitCatEtAuberge("plaine_droite", lcase1, lieu_plaine, nullptr, 0);
        lendroit1.push_back(e);
        lcase1.clear();


        c = new CaseCatEtAuberge(SO, B, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(SO, G, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(O, G, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(NO, G, 0);
        lcase1.push_back(c);

        e = new EndroitCatEtAuberge("plaine_gauche", lcase1, lieu_plaine, nullptr, 0);
        lendroit1.push_back(e);
        lcase1.clear();

        tInitialisation = new tuileCatEtAuberge(lendroit1, i++);
        ajouterTuile(tInitialisation);
        lendroit1.clear();


        //Tuile 11

        c = new CaseCatEtAuberge(NO, H, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(N, H, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(NE, H, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(NE, D, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(E, D, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(SE, D, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(SE, B, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(S, B, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(SO, B, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(SO, G, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(O, G, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(NO, G, 0);
        lcase1.push_back(c);

        e = new EndroitCatEtAuberge("Ville", lcase1, lieu_ville, nullptr, 0);
        lendroit1.push_back(e);
        lcase1.clear();

        c = new CaseCatEtAuberge(C, nul, 0);
        lcase1.push_back(c);

        e = new EndroitCatEtAuberge("Cathedrale", lcase1, lieu_cathedrale, nullptr, 0);
        lendroit1.push_back(e);
        lcase1.clear();

        tInitialisation = new tuileCatEtAuberge(lendroit1, i++);
        ajouterTuile(tInitialisation);
        lendroit1.clear();

        //Tuile 12

        c = new CaseCatEtAuberge(NO, H, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(N, H, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(NE, H, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(NE, D, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(E, D, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(SE, D, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(SE, B, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(S, B, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(SO, B, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(SO, G, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(O, G, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(NO, G, 0);
        lcase1.push_back(c);

        e = new EndroitCatEtAuberge("Ville", lcase1, lieu_ville, nullptr, 0);
        lendroit1.push_back(e);
        lcase1.clear();

        c = new CaseCatEtAuberge(C, nul, 0);
        lcase1.push_back(c);

        e = new EndroitCatEtAuberge("Cathedrale", lcase1, lieu_cathedrale, nullptr, 0);
        lendroit1.push_back(e);
        lcase1.clear();

        tInitialisation = new tuileCatEtAuberge(lendroit1, i++);
        ajouterTuile(tInitialisation);
        lendroit1.clear();

        //Tuile 13

        c = new CaseCatEtAuberge(N, H, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(NE, H, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(SO, G, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(O, G, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(NO, G, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(NO, H, 0);
        lcase1.push_back(c);

        e = new EndroitCatEtAuberge("ville_haut_gauche", lcase1, lieu_ville, nullptr, 0);
        lendroit1.push_back(e);
        lcase1.clear();


        c = new CaseCatEtAuberge(SO, B, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(NE, D, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(C, nul, 0);
        lcase1.push_back(c);

        e = new EndroitCatEtAuberge("plaine_NE_C_SO", lcase1, lieu_plaine, nullptr, 0);
        lendroit1.push_back(e);
        lcase1.clear();


        c = new CaseCatEtAuberge(SE, D, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(SE, B, 0);
        lcase1.push_back(c);

        e = new EndroitCatEtAuberge("plaine_SE", lcase1, lieu_plaine, nullptr, 0);
        lendroit1.push_back(e);
        lcase1.clear();


        c = new CaseCatEtAuberge(E, D, 1);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(S, B, 1);
        lcase1.push_back(c);

        e = new EndroitCatEtAuberge("route_E_S", lcase1, lieu_route, nullptr, 1);
        lendroit1.push_back(e);
        lcase1.clear();


        tInitialisation = new tuileCatEtAuberge(lendroit1, i++);
        ajouterTuile(tInitialisation);
        lendroit1.clear();


        //Tuile 14

        c = new CaseCatEtAuberge(NO, H, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(N, H, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(NE, H, 0);
        lcase1.push_back(c);

        e = new EndroitCatEtAuberge("ville_haut", lcase1, lieu_ville, nullptr, 0);
        lendroit1.push_back(e);
        lcase1.clear();


        c = new CaseCatEtAuberge(SO, D, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(SO, B, 0);
        lcase1.push_back(c);

        e = new EndroitCatEtAuberge("plaine_SO", lcase1, lieu_plaine, nullptr, 0);
        lendroit1.push_back(e);
        lcase1.clear();


        c = new CaseCatEtAuberge(C, nul, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(NO, G, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(NE, D, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(E, D, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(SE, D, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(SE, B, 0);
        lcase1.push_back(c);

        e = new EndroitCatEtAuberge("plaine_SE_E_NE_C_NO", lcase1, lieu_plaine, nullptr, 0);
        lendroit1.push_back(e);
        lcase1.clear();


        c = new CaseCatEtAuberge(S, B, 1);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(O, G, 1);
        lcase1.push_back(c);

        e = new EndroitCatEtAuberge("route_S_O", lcase1, lieu_route, nullptr, 1);
        lendroit1.push_back(e);
        lcase1.clear();

        tInitialisation = new tuileCatEtAuberge(lendroit1, i++);
        ajouterTuile(tInitialisation);
        lendroit1.clear();


        //Tuile 15

        c = new CaseCatEtAuberge(C, nul, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(N, H, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(NE, H, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(SO, G, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(O, G, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(NO, G, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(NO, H, 0);
        lcase1.push_back(c);

        e = new EndroitCatEtAuberge("ville_haut_gauche", lcase1, lieu_ville, nullptr, 0);
        lendroit1.push_back(e);
        lcase1.clear();


        c = new CaseCatEtAuberge(NE, D, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(E, D, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(SE, D, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(SE, B, 0);
        lcase1.push_back(c);

        e = new EndroitCatEtAuberge("plaine_SE_E_NE", lcase1, lieu_plaine, nullptr, 0);
        lendroit1.push_back(e);
        lcase1.clear();


        c = new CaseCatEtAuberge(S, B, 1);
        lcase1.push_back(c);

        e = new EndroitCatEtAuberge("route_S", lcase1, lieu_route, nullptr, 1);
        lendroit1.push_back(e);
        lcase1.clear();


        c = new CaseCatEtAuberge(SO, B, 0);
        lcase1.push_back(c);

        e = new EndroitCatEtAuberge("plaine_SO_B", lcase1, lieu_plaine, nullptr, 1);
        lendroit1.push_back(e);
        lcase1.clear();

        tInitialisation = new tuileCatEtAuberge(lendroit1, i++);
        ajouterTuile(tInitialisation);
        lendroit1.clear();

        //Tuile 16

        c = new CaseCatEtAuberge(NO, H, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(N, H, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(NE, H, 0);
        lcase1.push_back(c);

        e = new EndroitCatEtAuberge("ville_haut", lcase1, lieu_ville, nullptr, 0);
        lendroit1.push_back(e);
        lcase1.clear();



        c = new CaseCatEtAuberge(NE, D, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(E, D, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(SE, D, 0);
        lcase1.push_back(c);

        e = new EndroitCatEtAuberge("ville_droite", lcase1, lieu_ville, nullptr, 0);
        lendroit1.push_back(e);
        lcase1.clear();


        c = new CaseCatEtAuberge(SO, G, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(O, G, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(NO, G, 0);
        lcase1.push_back(c);

        e = new EndroitCatEtAuberge("ville_gauche", lcase1, lieu_ville, nullptr, 0);
        lendroit1.push_back(e);
        lcase1.clear();



        c = new CaseCatEtAuberge(C, nul, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(SE, B, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(S, B, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(SO, B, 0);
        lcase1.push_back(c);

        e = new EndroitCatEtAuberge("plaine_CEt_Bas", lcase1, lieu_plaine, nullptr, 0);
        lendroit1.push_back(e);
        lcase1.clear();

        tInitialisation = new tuileCatEtAuberge(lendroit1, i++);
        ajouterTuile(tInitialisation);
        lendroit1.clear();


        //Tuile 17

        c = new CaseCatEtAuberge(N, H, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(NE, H, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(SO, G, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(O, G, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(NO, G, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(NO, H, 0);
        lcase1.push_back(c);

        e = new EndroitCatEtAuberge("ville_haut_gauche", lcase1, lieu_ville, nullptr, 0);
        lendroit1.push_back(e);
        lcase1.clear();


        c = new CaseCatEtAuberge(SE, B, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(S, B, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(SO, B, 0);
        lcase1.push_back(c);

        e = new EndroitCatEtAuberge("ville_bas", lcase1, lieu_ville, nullptr, 0);
        lendroit1.push_back(e);
        lcase1.clear();


        c = new CaseCatEtAuberge(C, nul, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(NE, D, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(E, D, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(SE, D, 0);
        lcase1.push_back(c);

        e = new EndroitCatEtAuberge("plaine_C_E", lcase1, lieu_plaine, nullptr, 0);
        lendroit1.push_back(e);
        lcase1.clear();

        tInitialisation = new tuileCatEtAuberge(lendroit1, i++);
        ajouterTuile(tInitialisation);
        lendroit1.clear();

        //Tuile 18

        c = new CaseCatEtAuberge(N, H, 0);
        lcase1.push_back(c);

        e = new EndroitCatEtAuberge("route_N", lcase1, lieu_route, nullptr, 0);
        lendroit1.push_back(e);
        lcase1.clear();


        c = new CaseCatEtAuberge(S, B, 0);
        lcase1.push_back(c);

        e = new EndroitCatEtAuberge("route_S", lcase1, lieu_route, nullptr, 0);
        lendroit1.push_back(e);
        lcase1.clear();


        c = new CaseCatEtAuberge(NE, H, 0);
        lcase1.push_back(c);

        e = new EndroitCatEtAuberge("plaine_NE_H", lcase1, lieu_plaine, nullptr, 0);
        lendroit1.push_back(e);
        lcase1.clear();


        c = new CaseCatEtAuberge(SE, B, 0);
        lcase1.push_back(c);

        e = new EndroitCatEtAuberge("plaine_SE_B", lcase1, lieu_plaine, nullptr, 0);
        lendroit1.push_back(e);
        lcase1.clear();


        c = new CaseCatEtAuberge(SO, B, 0);
        lcase1.push_back(c);

        e = new EndroitCatEtAuberge("plaine_SO_B", lcase1, lieu_plaine, nullptr, 0);
        lendroit1.push_back(e);
        lcase1.clear();


        c = new CaseCatEtAuberge(NO, H, 0);
        lcase1.push_back(c);

        e = new EndroitCatEtAuberge("plaine_NO_H", lcase1, lieu_plaine, nullptr, 0);
        lendroit1.push_back(e);
        lcase1.clear();

        c = new CaseCatEtAuberge(C, nul, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(NE, D, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(E, D, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(SE, D, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(SO, G, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(O, G, 0);
        lcase1.push_back(c);
        c = new CaseCatEtAuberge(NO, G, 0);
        lcase1.push_back(c);

        e = new EndroitCatEtAuberge("ville_centre_droite_gauche", lcase1, lieu_ville, nullptr, 0);
        lendroit1.push_back(e);
        lcase1.clear();

        tInitialisation = new tuileCatEtAuberge(lendroit1, i++);
        ajouterTuile(tInitialisation);
        lendroit1.clear();


}
