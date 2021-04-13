#include "parser.h"

Parser::Parser(QFile* textFile, MapModel* model)
{
    _textFile = textFile;
    _model = model;
}

void Parser::writeInFile()
{
    _textFile->open(QIODevice::WriteOnly);
    QStringList* list = _model->getHead();
    for(int i = 0; i < list->size(); i++)
    {
        _textFile->write(list->at(i).toStdString().c_str());
        if(i != list->size()-1)
            _textFile->write(";");
    }
    _textFile->write("\n");
    QMap<QString, Employe>* map = _model->getMap();

    QMap<QString, Employe>::iterator it = map->begin();

    while(it != map->end())
    {
        QString key = it.key();
        QString name = it.value().name;
        QString position = it.value().position;

        QRegularExpression* reg = new QRegularExpression(";");
        key.replace(*reg, "\\;");
        name.replace(*reg, "\\;");
        position.replace(*reg, "\\;");
        delete reg;

        QString stringValue = (key + ";" + name + ";" + QString::number(it.value().age) + ";" + position + "\n");
        _textFile->write(stringValue.toStdString().c_str());
        ++it;
    }
    _textFile->close();
}

void Parser::readInFile()
{
    QTextStream textReader(_textFile);
    textReader.setCodec("UTF-8");
    _textFile->open(QIODevice::ReadOnly);

    QMap<QString, Employe>* tmpMap = new QMap<QString, Employe>();
    QString s = textReader.readLine();
    QRegularExpression* ref = new QRegularExpression("(?<!\\\\);");
    QStringList row = s.split(*ref);
    _model->setHead(&row);

    while(!textReader.atEnd())
    {
        s = textReader.readLine();
        row = s.split(*ref);
        for(int i = 0; i < row.size(); i++)
        {
            while(row.at(i).indexOf("\\") != -1 )
            {
                row[i].remove(row.at(i).indexOf("\\"), 1);
            }
        }
        QStringList tmpList;
        for(int i = 1; i < row.size(); i++)
        {
            tmpList.append(row.at(i));
        }

        Employe* emp = new Employe(tmpList);
        tmpMap->insert(row.at(0), *emp);
    }

    _model->setMap(tmpMap);
    _textFile->close();
    delete tmpMap;
}
