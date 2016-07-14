#ifndef PROCESSMODEL_H
#define PROCESSMODEL_H
#include "main.h"
#include "processinfolist.h"
class ProcessModel : public QAbstractTableModel
{
    Q_OBJECT

private:
    QList<ProcessInfo *> list;

public:
    QStringList headerLabelList;
    explicit ProcessModel(QObject *parent = 0);

    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

    int rowCount(const QModelIndex &parent=QModelIndex()) const;
    int columnCount(const QModelIndex &parent) const;

    QVariant headerData(int section,Qt::Orientation orientation, int role=Qt::DisplayRole) const;

    Qt::ItemFlags flags(const QModelIndex &index) const;

    bool insertRows(int position, int rows, const QModelIndex &index);
    bool removeRows(int position, int rows, const QModelIndex &index);

signals:

public slots:

};


#endif // PROCESSMODEL_H
