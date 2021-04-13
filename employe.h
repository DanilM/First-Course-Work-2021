#ifndef EMPLOYE_H
#define EMPLOYE_H

#include <QString>



class Employe
{
public:
    Employe();
    Employe(QStringList list);
    Employe(QString Name, int Age, QString Position);
    QString name;
    int age;
    QString position;
};

#endif // EMPLOYE_H
