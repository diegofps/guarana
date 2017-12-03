#ifndef FILETABLEMODEL_HPP
#define FILETABLEMODEL_HPP

#include <QAbstractTableModel>
#include <helpers/ptrlist.hpp>
#include <viewmodels/fileviewmodel.hpp>

class FileTableModel : public QAbstractTableModel
{
private:

    PtrList<FileViewModel> _models;

public:

    FileTableModel(QObject *parent=nullptr) :
        QAbstractTableModel(parent)
    {

    }

    void refresh()
    {
        emit dataChanged(createIndex(0, 0), createIndex(_models.size()-1, 3));
        emit layoutChanged();
    }

    PtrList<FileViewModel> & getModel()
    {
        return _models;
    }

    int rowCount(const QModelIndex & /*parent*/) const
    {
       return _models.size();
    }

    int columnCount(const QModelIndex & /*parent*/) const
    {
        return 4;
    }

    QVariant data(const QModelIndex &index, int role) const
    {
        const int & row = index.row();
        const int & col = index.column();

        FileViewModel & model = *_models.at(row);

        if (role == Qt::DisplayRole)
        {
            switch (col) {
            case 0: return model.getFilename();
            case 1: return model.getSize();
            case 2: return model.getModificationDate();
            case 3: return model.getCreationDate();
            default: return QVariant();
            }
        }

        return QVariant();
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role) const
    {
        if (orientation == Qt::Horizontal)
        {
            if (role == Qt::DisplayRole)
            {
                switch (section)
                {
                case 0:
                    return QString("Filename");
                case 1:
                    return QString("Size");
                case 2:
                    return QString("Modified");
                case 3:
                    return QString("Created");
                }
            }

            if (role == Qt::ForegroundRole)
            {
                return QColor(Qt::white);
            }

            if (role == Qt::BackgroundRole)
            {
                return QColor("#3875b8");
            }
        }

        return QVariant();
    }

};

#endif
