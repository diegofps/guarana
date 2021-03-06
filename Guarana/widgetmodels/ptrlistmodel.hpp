#ifndef TAGLISTMODEL_HPP
#define TAGLISTMODEL_HPP

#include<QDebug>
#include <QAbstractTableModel>

#include <helpers/ptrlist.hpp>

template <typename ItemType, QString (ItemType::*StrFunc)() const>
class PtrListModel : public virtual QAbstractListModel, public virtual PtrList<ItemType>
{
public:

    PtrListModel(bool ownsData=false) :
        PtrList<ItemType>(ownsData)
    {

    }

    int rowCount(const QModelIndex & /*parent*/) const
    {
        return this->size();
    }

    int columnCount(const QModelIndex & /*parent*/)
    {
        return 1;
    }

    bool contains(QString & name) const
    {
        for (ItemType * item : *this)
            if (name == (item->*StrFunc)())
                return true;
        return false;
    }

    QVariant data(const QModelIndex &index, int role) const
    {
        const int & row = index.row();

        if (role == Qt::DisplayRole)
            return (this->at(row)->*StrFunc)();
        else
            return QVariant();
    }

    void notifyContentChanged()
    {
        emit dataChanged(createIndex(0, 0), createIndex(this->size(), 1));
        emit layoutChanged();
    }

    void clear()
    {
        PtrList<ItemType>::clear();
        notifyContentChanged();
    }

    void removeAt(int i)
    {
        PtrList<ItemType>::removeAt(i);
        notifyContentChanged();
    }

    ItemType * getOrNull(const QString & name)
    {
        for (ItemType * item : *this)
        {
            QString str = (item->*StrFunc)();
            if (str == name)
                return item;
        }

        return nullptr;
    }

};

#endif // TAGLISTMODEL_HPP
