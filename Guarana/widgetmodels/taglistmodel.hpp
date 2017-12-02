#ifndef TAGLISTMODEL_HPP
#define TAGLISTMODEL_HPP

#include <QAbstractTableModel>

#include <helpers/ptrlist.hpp>

#include <dal/models/tag.hpp>

class TagListModel : public QAbstractListModel
{
private:

    PtrList<Tag> _tags;

public:

    TagListModel() : _tags(false)
    {

    }

    PtrList<Tag> & getModel()
    {
        return _tags;
    }

    int rowCount(const QModelIndex & /*parent*/) const
    {
        return _tags.size();
    }

    bool contains(QString & tagName) const
    {
        for (Tag * tag : _tags)
            if (tagName == tag->getName())
                return true;
        return false;
    }

    QVariant data(const QModelIndex &index, int role) const
    {
        const int & row = index.row();

        if (role == Qt::DisplayRole)
            return QString(_tags.at(row)->getName());

        return QVariant();
    }

    void refresh()
    {
        emit dataChanged(createIndex(0, 0), createIndex(_tags.size(), 1));
        emit layoutChanged();
    }

    Tag * getOrDefault(const QString & name)
    {
        for (Tag * tag : _tags)
            if (name == tag->getName())
                return tag;
        return nullptr;
    }

};

#endif // TAGLISTMODEL_HPP
