#include "employe.h"
#include <QStringList>
#include <QString>


Employe::Employe()
{
}

Employe::Employe(QStringList list)
{
    this->name = list[0];
    this->age = list[1].toInt();
    this->position = list[2];
}

Employe::Employe(QString Name, int Age, QString Position)
{
    this->name = Name;
    this->age = Age;
    this->position = Position;
}
