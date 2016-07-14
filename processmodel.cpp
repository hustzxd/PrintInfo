#include "processmodel.h"

ProcessModel::ProcessModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    ProcessInfoList proList = new ProcessInfoList;
    list = proList.processList;
    headerLabelList << "进程号" << "进程名" << "状态" << "优先级" << "内存" << "运行时间";
}
QVariant ProcessModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= list.size())
        return QVariant();

    if (role == Qt::DisplayRole || role == Qt::EditRole){
        if (index.column() == 0 )
            return list.at(index.row())->processID;
        if (index.column() == 1 )
            return list.at(index.row())->processName;
        if (index.column() == 2 )
            return list.at(index.row())->processState;
        if (index.column() == 3 )
            return list.at(index.row())->processNice;
        if (index.column() == 4 )
            return list.at(index.row())->processVmRss;
        if (index.column() == 5 )
            return list.at(index.row())->processRunningTime;
    }
    return QVariant();
}

bool ProcessModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::DisplayRole) {
        //
        if(index.column()==0){
            list.at(index.row())->processID = value.toString();
            emit dataChanged(index, index);
        }
        if(index.column()==1){
            list.at(index.row())->processName = value.toString();
            emit dataChanged(index, index);
        }
        if(index.column()==2){
            list.at(index.row())->processState = value.toString();
            emit dataChanged(index, index);
        }
        if(index.column()==3){
            list.at(index.row())->processNice = value.toString();
            emit dataChanged(index, index);
        }
        if(index.column()==4){
//            list.at(index.row())->processVmRss = value.toString();
            emit dataChanged(index, index);
        }
        if(index.column()==5){
//            list.at(index.row())->processRunningTime= value.toString();
            emit dataChanged(index, index);
        }
        return true;
    }
    return false;
}

bool ProcessModel::insertRows(int position, int rows, const QModelIndex &parent)
{
    if(parent.isValid()) return false;

    beginInsertRows(parent, position, position+rows-1);

    for (int row = 0; row < rows; ++row) {
        list.insert(position, new ProcessInfo());
    }

    endInsertRows();

    return true;
}

bool ProcessModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    if(parent.isValid()) return false;

    beginRemoveRows(QModelIndex(), position, position+rows-1);

    for (int row=0; row < rows; ++row) {
        list.removeAt(position);
    }

    endRemoveRows();

    return true;
}

int ProcessModel::rowCount(const QModelIndex &parent) const
{
    return list.size();
}

int ProcessModel::columnCount(const QModelIndex &parent) const
{
    return headerLabelList.size();
}

QVariant ProcessModel::headerData(int section, Qt::Orientation orientation, int role) const
{
   if(role != Qt::DisplayRole)
           return QAbstractTableModel::headerData(section, orientation, role);
   if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
   {
       return headerLabelList.at(section); // заголовки столбцов
   }
   else
   {
       return QString("%1").arg( section + 1 ); // возвращаем номера строк
   }
}

Qt::ItemFlags ProcessModel::flags(const QModelIndex &index) const
{
   if (!index.isValid())
        return Qt::ItemIsEnabled;

   return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}
