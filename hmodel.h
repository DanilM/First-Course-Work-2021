#ifndef HMODEL_H
#define HMODEL_H

#include<QHeaderView>
class HModel : public QHeaderView
{
    Q_OBJECT
public:
    HModel(Qt::Orientation orientation, QWidget *parent = nullptr);
    QVariant data(const QModelIndex& index, int role) const;
    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;
private:
    QStringList* _hList;
};

#endif // HMODEL_H
