#ifndef NAVIGATIONTAB_H
#define NAVIGATIONTAB_H

#include <QWidget>
#include <QAbstractTableModel>

#include "helpers/context.hpp"

class MyModel : public QAbstractTableModel
{
private:

    int _id;

public:

    MyModel(int id, QObject *parent=nullptr) :
        QAbstractTableModel(parent),
        _id(id + 1)
    {

    }

    int rowCount(const QModelIndex & /*parent*/) const
    {
       return _id;
    }

    int columnCount(const QModelIndex & /*parent*/) const
    {
        return 4;
    }

    QVariant data(const QModelIndex &index, int role) const
    {
        const int & row = index.row();
        const int & col = index.column();

        if (role == Qt::DisplayRole)
           return QString("Row%1, Column%2").arg(row + 1).arg(col +1);

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

namespace Ui {
class NavigationTab;
}

class NavigationTab : public QWidget
{
    Q_OBJECT

private:

    void configureResultTable();

    void configureTagFilter();

public:

    explicit NavigationTab(Context & context, int id, QWidget *parent = 0);

    ~NavigationTab();

private slots:

    void showContextMenu(const QPoint &);

private:

    Ui::NavigationTab *ui;

    const int _id;

    MyModel _model;

};

#endif // NAVIGATIONTAB_H
