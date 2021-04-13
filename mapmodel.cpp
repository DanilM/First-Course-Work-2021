#include "mapmodel.h"
#include "employe.h"
#include <QDebug>
#include <QList>

MapModel::MapModel(QObject *parent) : QAbstractTableModel(parent)
{
    _map = new QMap<QString, Employe>();
    listHead = new QStringList();
}

void MapModel::setMap(QMap<QString, Employe>* map)
{
    if(rowCount() != 0)
    {
        beginRemoveRows(QModelIndex(), 0, rowCount() - 1);
        endRemoveRows();
    }

    deleteAllEntity();

    int i = 0;
    QMap<QString, Employe>::iterator it = map->begin();
    while(it != map->end())
    {
        beginInsertRows(QModelIndex(), i, i);
        _map->insert(it.key(), it.value());
        ++it;
        ++i;
        endInsertRows();
    }
}

void MapModel::setHead(QStringList* head)
{
    if(columnCount() != 0)
    {
        beginRemoveColumns(QModelIndex(), 0, columnCount() - 1);
        endRemoveColumns();
    }

    listHead->clear();

    beginInsertColumns(QModelIndex(), 0, 3);
    for(int i = 0; i < 4; i++)
    {
        listHead->append(head->at(i));
    }
    for(int i = 0; i < listHead->size(); i++)
        setHeaderData(i, Qt::Horizontal, listHead->at(i));
    endInsertColumns();
}

Qt::ItemFlags MapModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable;
}

QVariant MapModel::headerData(int section, Qt::Orientation, int role) const
{
    if (!listHead)
        return QVariant();
    if (section < 0 || section >= listHead->count() || role != Qt::DisplayRole)
    {
        return QVariant();
    }
    return listHead->at(section);
}

bool MapModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (Qt::DisplayRole)
    {
        return false;
    }

    QModelIndex indexKey = QAbstractItemModel::createIndex(index.row(),0);
    QString tmpKey = indexKey.data().toString();

    if(index.column()==0)
    {
        Employe tmpEmp = _map->value(tmpKey);
        _map->insert(value.toString(), tmpEmp);
        _map->remove(indexKey.data().toString());
        return true;
    }

    if(index.column() > 0)
    {
        switch (index.column())
        {
            case 1:
            {

                Employe* tmpEmp = new Employe(value.toString(), _map->value(tmpKey).age, _map->value(tmpKey).position);
                _map->remove(tmpKey);
                _map->insert(tmpKey, *tmpEmp);
                break;
            }
            case 2:
            {
                Employe* tmpEmp = new Employe(_map->value(tmpKey).name, value.toInt(), _map->value(tmpKey).position);
                _map->remove(tmpKey);
                _map->insert(tmpKey, *tmpEmp);
                break;
            }
            case 3:
            {
                Employe* tmpEmp = new Employe(_map->value(tmpKey).name, _map->value(tmpKey).age, value.toString());
                _map->remove(tmpKey);
                _map->insert(tmpKey, *tmpEmp);
                break;
            }
        }
        return true;
    }
}

bool MapModel::insertRow(int row, const QModelIndex &parent)
{
    if(_map->size() == 0)
    {
        return false;
    }

    if(row > rowCount())
        return false;
    beginInsertRows(QModelIndex(), row, row);
    Employe* emp = new Employe("",0,"");
    _map->insert(QString::number(getMaxKey() + 1), *emp);
    endInsertRows();
    return true;
}

void MapModel::removeSelected(const QModelIndexList &indexList)
{
    if (indexList.empty())
        return;
    QModelIndex index = indexList.first();
    QModelIndex indexKey = QAbstractItemModel::createIndex(index.row(),0);
    QString tmpKey = indexKey.data().toString();

    QMap<QString, Employe>::iterator it = _map->begin();
    beginRemoveRows(QModelIndex(), index.row(), index.row());
    endRemoveRows();
    while(it != _map->end())
    {
        if(it.key() == tmpKey)
        {
            _map->erase(it);
            return;
        }
        ++it;
    }
}

int MapModel::rowCount(const QModelIndex& parent) const
{
    if (_map)
        return _map->count();
    return 0;
}

int MapModel::columnCount(const QModelIndex & parent) const
{
    return listHead->size();
}

QVariant MapModel::data(const QModelIndex& index, int role) const
{
    if (!_map)
        return QVariant();
    if (index.row() < 0 || index.row() >= _map->count() || role != Qt::DisplayRole)
    {
        return QVariant();
    }
    if (index.column() == 0)
        return _map->keys().at(index.row());
    if (index.column() == 1)
        return _map->values().at(index.row()).name;
    if (index.column() == 2)
        return _map->values().at(index.row()).age;
    if (index.column() == 3)
        return _map->values().at(index.row()).position;
    return QVariant();
}

QStringList* MapModel::getHead()
{
    return listHead;
}

QMap<QString, Employe>* MapModel::getMap()
{
    return _map;
}

void MapModel::deleteAllEntity()
{
    QMap<QString, Employe>::iterator it = _map->begin();
    while(it != _map->end())
    {
        it = _map->erase(it);
    }
}

int MapModel::getMaxKey()
{
    int maxKey = 0;
    QMap<QString, Employe>::iterator it = _map->begin();
    while(it != _map->end())
    {
        if(it.key().toInt() > maxKey)
        {
            maxKey = it.key().toInt();
        }
        ++it;
    }
    return maxKey;
}

MapModel::~MapModel()
{
    deleteAllEntity();
    delete _map;
    delete listHead;
}

