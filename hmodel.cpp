#include "hmodel.h"
#include <QHeaderView>
#include <QWidget>

HModel::HModel(Qt::Orientation orientation, QWidget *parent = nullptr) : QHeaderView(Qt::Orientation orientation, QWidget *parent = nullptr)
{
    _hList = NULL;
}

QVariant HModel::data(const QModelIndex& index, int role) const
{
    if (!_hList)
        return QVariant();
    if (index.row() < 0 || index.row() >= _hList->count() || role != Qt::DisplayRole)
    {
        return QVariant();
    }
    if (index.column() >= 0)
        return _hList->at(index.row());
    return QVariant();
}

int HModel::rowCount(const QModelIndex &parent) const
{
    return 1;
}

int HModel::columnCount(const QModelIndex &parent) const
{
    return _hList->count();
}
