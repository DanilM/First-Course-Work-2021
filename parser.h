#ifndef PARSER_H
#define PARSER_H

#include <QFile>
#include <QStringList>
#include <mapmodel.h>
#include <QTextStream>

class Parser
{
public:
    Parser(QFile* textFile, MapModel* model);
    void writeInFile();
    void readInFile();
private:
    QFile* _textFile;
    MapModel* _model;
};

#endif // PARSER_H
