#ifndef MESBOUTONS_H
#define MESBOUTONS_H

#include <QObject>
#include <QPushButton>

//  QT
//  CODE DE LA CLASSE :
//	MesBoutons


//Créaction du classe avec des boutons personnalisés
//nous ne les avons pas utilisé d'attribut particulier
//mais il s'agir d'une bonne pratique
class MesBoutons : public QPushButton
{
    Q_OBJECT
public:
    MesBoutons(QWidget * parent=nullptr);
    virtual ~MesBoutons()=default; //supprimer par le parent
};

#endif // MESBOUTONS_H
