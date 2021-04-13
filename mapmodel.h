#ifndef MAPMODEL_H
#define MAPMODEL_H

#include <QAbstractTableModel>
#include <QHeaderView>
#include <QMap>
#include "employe.h"
#include <QFile>

class MapModel: public QAbstractTableModel
{
    Q_OBJECT
public:
    MapModel(QObject *parent = 0);
    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    void setMap(QMap<QString, Employe>* map);
    void setHead(QStringList* head);
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    bool insertRow(int row, const QModelIndex &parent = QModelIndex());
    void removeSelected(const QModelIndexList &indexList);
    QStringList* getHead();
    QMap<QString, Employe>* getMap();
    void deleteAllEntity();
    int getMaxKey();
    ~MapModel();

private:
    QMap<QString, Employe>* _map;
    QStringList* listHead;
};

#endif // MAPMODEL_H
