#include "fenetrejeu.h"
#include "grilledejeu.h"
#include "matuile.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QProgressBar>
#include <QLCDNumber>
#include <QMessageBox>
#include <QMouseEvent>
#include <QTransform>
#include <chrono>
#include <thread>

MaScene* fenetrejeu::m_scene = nullptr;
Controleur fenetrejeu::controleur;

//Décaler vers le bas les tuiles et des meeples
void fenetrejeu::decaler_bas()
{
    for(auto it=m_scene->plateau.begin();it!= m_scene->plateau.end();it++)
    {
        int x=(*it)->pos().x();
        int y=(*it)->pos().y() + MaScene::taille_case;
        (*it)->setPos(x,y);
    }
    int x,y;
    for (auto it = m_scene->joueurs.begin();it != m_scene->joueurs.end() ; it++)
    {
        for (auto it2 = (*it)->meeples.begin(); it2!=(*it)->meeples.end()  ; it2++)
        {
            x = (*it2)->pos().x();
            y = (*it2)->pos().y();
             if((*it2)->pos().y()<m_scene->taille_bas*m_scene->taille_case)
             {
                (*it2)->setPos(x,y+m_scene->taille_case);
                 m_scene->addItem(*it2);
             }
        }
    }
}

//Décaler vers la droite les tuiles et des meeples
void fenetrejeu::decaler_droite()
{
    for(auto it=m_scene->plateau.begin();it!= m_scene->plateau.end();it++)
    {
        int x=(*it)->pos().x() + MaScene::taille_case;
        int y=(*it)->pos().y();
        (*it)->setPos(x,y);
    }
    int x,y;
    for (auto it = m_scene->joueurs.begin();it != m_scene->joueurs.end() ; it++)
    {
        for (auto it2 = (*it)->meeples.begin(); it2!=(*it)->meeples.end()  ; it2++)
        {
            x = (*it2)->pos().x();
            y = (*it2)->pos().y();
             if((*it2)->pos().y()<m_scene->taille_bas*m_scene->taille_case)
             {
                (*it2)->setPos(x+m_scene->taille_case,y);
                 m_scene->addItem(*it2);
             }
        }
    }
}

//Agrandir le tableau en décalant les objets en dehors du tableau
void fenetrejeu::agrandir_tableau_bas()
{
    MaScene::taille_bas = MaScene::taille_bas +1 ;
    int taille_grille=MaScene::taille_grille;
    int taille_bas = MaScene::taille_bas;
    int taille_case = MaScene::taille_case;

    /* ------ Grille ------  */
    for(int i=0;i<taille_bas;i++)
    {
        m_scene->addLine(0,i*taille_case,taille_case*taille_grille-taille_case,i*taille_case, QPen(Qt::gray));
    }
    for(int i=0;i<taille_grille;i++)
    {
        m_scene->addLine(i*taille_case,0,i*taille_case,taille_bas*taille_case-taille_case,QPen(Qt::gray));
    }

    //affichage des tables joueurs
    m_scene->updateSize(0,(int) MaScene::taille_case/2);
}





//Agrandir le tableau en décalant les objets en dehors du tableau
void fenetrejeu::agrandir_tableau_gauche()
{
    MaScene::taille_grille = MaScene::taille_grille +1 ;
    int taille_grille=MaScene::taille_grille;
    int taille_bas = MaScene::taille_bas;
    int taille_case = MaScene::taille_case;

    /* ------ Grille ------  */
    for(int i=0;i<taille_bas;i++)
    {
        m_scene->addLine(0,i*taille_case,taille_case*taille_grille-taille_case,i*taille_case, QPen(Qt::gray));
    }
    for(int i=0;i<taille_grille;i++)
    {
        m_scene->addLine(i*taille_case,0,i*taille_case,taille_bas*taille_case-taille_case,QPen(Qt::gray));
    }
    //bouger les boutons
    btn_valider_tuile->move(taille_case*taille_grille-taille_case+200,20);
    btn_valider_tour->move(taille_case*taille_grille-taille_case+200,50);
    btn_zoomer->move(taille_case*taille_grille-taille_case+200,80);
    btn_dezoomer->move(taille_case*taille_grille-taille_case+200,110);
}


//outil pour savoir le joueur courrant
int fenetrejeu::joueurCourrant=-1;

//Constructeur de fenetre jeu
fenetrejeu::fenetrejeu(QWidget *parent): QWidget()//ma fenetre de jeu ne doit pas être liée à la parent
{
    setWindowTitle("LO21_Projet");
    setMinimumSize(1000,500);

    // Initialisation des données de la fenetre parent
    FenetrePrincipale * main = dynamic_cast<FenetrePrincipale*>(parent);
    if(main)
       monparent=main;

    // Initialisation des extensions
    if(parent)
    {
        controleur=monparent->listeExt;

        for(list<Joueur*>::iterator it_j = monparent->listeJoueurs.begin() ;
            it_j != monparent->listeJoueurs.end() ; it_j++)
             controleur.ajouterJoueur((**it_j));
      }

    // Initialisation de mes joueurs
    QList<MesJoueurs*> maliste;
    int i =0;
    for(auto it = controleur.getListJoueur().begin();it!=controleur.getListJoueur().end();it++)
    {
        maliste.push_back(new MesJoueurs((*it),i));
        i++;
    }

    // Initialisation des vues
    m_view= new QGraphicsView(this);
    m_scene = new MaScene(maliste,m_view);

    m_view->setScene(m_scene);
    m_view->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    m_view->centerOn(0,0);


    m_view->verticalScrollBar();
    m_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    m_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    // Création des boutons

    btn_valider_tuile = new MesBoutons(this);
    btn_valider_tuile->setText("Valider Tuile");

    btn_valider_tour= new MesBoutons(this);
    btn_valider_tour->setText("Valider Tour");

    btn_zoomer=new MesBoutons(this);
    btn_zoomer->setText("Zoomer");

    btn_dezoomer=new MesBoutons(this);
    btn_dezoomer->setText("Dezoomer");


    // Pacement des boutons
    btn_valider_tuile->move(250,20);
    btn_valider_tour->move(250,50);
    btn_zoomer->move(250,80);
    btn_dezoomer->move(250,110);


    //Alignement des boutons qui ne fut pas concluant
   /*
    Qt::Alignment a = Qt::AlignLeft | Qt::AlignTop;

     m_scene->boutons = new QGridLayout(m_scene->test);

    m_scene->boutons->addWidget(btn_valider_tuile,0,0,a);
    m_scene->boutons->addWidget(btn_valider_tour,1,0,a);
    m_scene->boutons->addWidget(btn_zoomer,2,0,a);
    m_scene->boutons->addWidget(btn_dezoomer,3,0,a);

    m_scene->addWidget(m_scene->test);
    */

    connect(btn_valider_tuile,SIGNAL(clicked(bool)),this,SLOT(valider_tuile(bool)));
    connect(btn_valider_tour,SIGNAL(clicked(bool)),this,SLOT(valider_tour(bool)));
    connect(btn_zoomer,SIGNAL(clicked(bool)),this,SLOT(zoomIn(bool)));
    connect(btn_dezoomer,SIGNAL(clicked(bool)),this,SLOT(zoomOut(bool)));

    m_scene->piocher_classique(controleur);

}

//réactiver la tuile de la pioche si on aurait voulu un bouton annuler
void fenetrejeu::valider_tuile(bool b)
{
    int x = m_scene->pioche->pos().x();
    int y = m_scene->pioche->pos().y();
    int pos_x=x/MaScene::taille_case;
    int pos_y=y/MaScene::taille_case;
    if(controleur.getAction()->poserTuile(controleur.getPlateau(),&(m_scene->pioche->getTuile()),pos_y,pos_x))//on essaie d'ajouter une tuile à notre plateau
    {

        //bloquer la tuile de pioche
        m_scene->pioche->setFlag(QGraphicsPixmapItem::ItemIsMovable,false);
        m_scene->pioche->setFlag(QGraphicsPixmapItem::ItemIsSelectable,false);
        m_scene->plateau.push_back(m_scene->pioche);
        //si cette tuile est sur les bords nous ajoutons des décalages
        if(pos_x == 0)
        {
            agrandir_tableau_gauche();
            decaler_droite();
        }
        x = m_scene->pioche->pos().x();
        y = m_scene->pioche->pos().y();
        pos_x=x/MaScene::taille_case;
        pos_y=y/MaScene::taille_case;
        if(pos_y ==0)
        {
            agrandir_tableau_bas();
            decaler_bas();

        }
        x = m_scene->pioche->pos().x();
        y = m_scene->pioche->pos().y();
        pos_x=x/MaScene::taille_case;
        pos_y=y/MaScene::taille_case;
        if(pos_x == MaScene::taille_grille -2)
        {
            agrandir_tableau_gauche();
        }
        x = m_scene->pioche->pos().x();
        y = m_scene->pioche->pos().y();
        pos_x=x/MaScene::taille_case;
        pos_y=y/MaScene::taille_case;
        if(pos_y == MaScene::taille_bas -2)
        {
            agrandir_tableau_bas();
        }
        m_scene->pioche=nullptr;
    }
    else
    {
        QMessageBox::information(
                    this,
                    tr("(!)  Erreur  (!)"),
                    tr("(!)  Tuile non compatible  (!)"));
    }

}

//bouton pour valider un tour
void fenetrejeu::valider_tour(bool b)
{
    if(m_scene->pioche==nullptr)
    {
       if(controleur.getPioche().getTaillePioche()>0)
        {
            m_scene->piocher_classique(controleur);
            m_scene->pioche->setPos(MaScene::taille_case*MaScene::taille_grille-MaScene::taille_case+50,130);
        }
        else
        {
            QMessageBox::information(
                        this,
                        tr("(!)  Erreur  (!)"),
                        tr(" Fin de la pioche \nVoici l'ajout des points pour la fin de la partie"));

            //Ajout des points pour chaque joueur
            for (auto it = m_scene->joueurs.begin();it != m_scene->joueurs.end() ; it++)
            {
                joueurCourrant= (joueurCourrant+1) % m_scene->joueurs.size();
                fenetrepoint* fenetre=new fenetrepoint(joueurCourrant,this);
                fenetre->show();
             }
        }
        if(m_scene->joueurs.size()!=0)
        {
            //Ajout des points
            joueurCourrant= (joueurCourrant+1) % m_scene->joueurs.size();
            fenetrepoint* fenetre=new fenetrepoint(joueurCourrant,this);
            fenetre->show();

            //vérification si on a pas une IA
            IA* ia = dynamic_cast<IA*>(m_scene->trouver_joueur( (joueurCourrant+1) % m_scene->joueurs.size())->joueur);
            Tuile* tuile = new Tuile();
            unsigned int x,y,rot;
            int posx,posy;
            pair<pair<unsigned int,unsigned int>,unsigned int> paire;

            //tant qu'on a des IA qui doivent jouer
            while(ia)
            {
                //récupération d'où l'IA veut poser la tuile
                paire=controleur.getAction()->choixIA(controleur.getPlateau(),&(m_scene->pioche->getTuile()));
                y= paire.first.first;
                x=paire.first.second;
                rot=paire.second;
                posx = m_scene->taille_case * x;
                posy =m_scene->taille_case * y;

                for(size_t i = 0 ; i < rot ; i++)
                {
                    QTransform trans;
                    trans=trans.rotate(90);
                    m_scene->pioche->setPixmap(m_scene->pioche->pixmap().transformed(trans));
                }

                m_scene->pioche->setPos(posx,posy);
                int x = m_scene->pioche->pos().x();
                int y = m_scene->pioche->pos().y();
                int pos_x=x/MaScene::taille_case;
                int pos_y=y/MaScene::taille_case;

                //bloquer la tuile de pioche
                m_scene->pioche->setFlag(QGraphicsPixmapItem::ItemIsMovable,false);
                m_scene->pioche->setFlag(QGraphicsPixmapItem::ItemIsSelectable,false);
                m_scene->plateau.push_back(m_scene->pioche);

                //si cette tuile est sur les bords nous ajoutons des décalages
                if(pos_x == 0)
                {
                    agrandir_tableau_gauche();
                    decaler_droite();
                }
                x = m_scene->pioche->pos().x();
                y = m_scene->pioche->pos().y();
                pos_x=x/MaScene::taille_case;
                pos_y=y/MaScene::taille_case;
                if(pos_y ==0)
                {
                    agrandir_tableau_bas();
                    decaler_bas();

                }
                x = m_scene->pioche->pos().x();
                y = m_scene->pioche->pos().y();
                pos_x=x/MaScene::taille_case;
                pos_y=y/MaScene::taille_case;
                if(pos_x == MaScene::taille_grille -2)
                {
                    agrandir_tableau_gauche();
                }
                x = m_scene->pioche->pos().x();
                y = m_scene->pioche->pos().y();
                pos_x=x/MaScene::taille_case;
                pos_y=y/MaScene::taille_case;
                if(pos_y == MaScene::taille_bas -2)
                {
                    agrandir_tableau_bas();
                }
                if(controleur.getPioche().getTaillePioche()>0)
                {
                    joueurCourrant= (joueurCourrant+1) % m_scene->joueurs.size();
                    fenetrepoint* fenetre=new fenetrepoint(joueurCourrant,this);
                    fenetre->show();
                    ia = dynamic_cast<IA*>(m_scene->trouver_joueur( (joueurCourrant+1) % m_scene->joueurs.size())->joueur);
                    m_scene->piocher_classique(controleur);
                    m_scene->pioche->setPos(MaScene::taille_case*MaScene::taille_grille-MaScene::taille_case+50,130);
                }
                else
                {
                    QMessageBox::information(
                                this,
                                tr("(!)  Erreur  (!)"),
                                tr(" Fin de la pioche \nVoici l'ajout des points pour la fin de la partie"));

                    //Ajout des points pour chaque joueur
                    for (auto it = m_scene->joueurs.begin();it != m_scene->joueurs.end() ; it++)
                    {
                        joueurCourrant= (joueurCourrant+1) % m_scene->joueurs.size();
                        fenetrepoint* fenetre=new fenetrepoint(joueurCourrant,this);
                        fenetre->show();
                     }

                }

            }
        }
        }
    else
    {
        QMessageBox::information(
                    this,
                    tr("(!)  Erreur  (!)"),
                    tr(" Impossible valider"));
    }
}




    //action pour zoomer
void fenetrejeu::zoomIn(bool b)
{
   m_view->scale(1.1, 1.1);
}

//action de dézoomer
void fenetrejeu::zoomOut(bool b)
{
    m_view->scale(0.8, 0.8);
}

//Destruction des pointeurs
fenetrejeu::~fenetrejeu()
{
    delete m_view;
    delete m_scene;
    delete btn_valider_tour;
}


//constructeur de la fenêtre pour les points
fenetrepoint::fenetrepoint(int c, QWidget *parent) : courrant(c)
{
    setFixedSize(500,200);
    fenetrejeu* main = dynamic_cast<fenetrejeu*>(parent);
    int nbTuile;
    monparent=main;
    if(monparent){
        nom = QString::fromStdString(monparent->m_scene->trouver_joueur(courrant)->joueur->getNom());
        nbTuile = monparent->controleur.getPioche().getTaillePioche();
    }
    //Infos du Joueur
    Points = new QLineEdit;
    btn_valider = new QPushButton("Valider", this);
    btn_valider->setToolTip("Permet d'enregistrer la modification des points");
    btn_valider->setCursor(Qt::PointingHandCursor);
    btn_valider->move(150,100);


    nbT = new QLabel("Nombre de Tuiles qui reste  :  "+ QString::number(nbTuile));
    QString test("Nombre de Tuiles qui reste  :  "+ QString::number(nbTuile));

    Donnee = new QFormLayout;
    QString add("Nombre de points à ajouter à " + nom + "  : ");
    Donnee->addRow(add, Points);
    Donnee->addRow(nbT);
    setLayout(Donnee);
    connect(btn_valider,SIGNAL(clicked(bool)),this,SLOT(valider(bool)));
}

//valider les points
void fenetrepoint::valider(bool b)
{
    if(monparent){ //si j'ai bien la fenetrejeu alors j'ajoute les points à mes joueurs
        int a = (monparent->m_scene->trouver_joueur(courrant))->joueur->getPoints() += Points->displayText().toInt();
        //et je modifie mon affichage
        (monparent->m_scene->trouver_joueur(courrant))->points.setPlainText(
                    "Nombre de point :   " + QString::number(a));


        close();
    }
}



