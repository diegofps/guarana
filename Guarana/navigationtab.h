#ifndef NAVIGATIONTAB_H
#define NAVIGATIONTAB_H

#include <QWidget>
#include <QAbstractTableModel>

#include <widgetmodels/filetablemodel.hpp>

#include "helpers/context.hpp"

namespace Ui {
class NavigationTab;
}

class NavigationTab : public QWidget, WorkspaceReadyListener
{
    Q_OBJECT

private:

    void configureResultTable();

    void configureTagFilter();

    void addFiles(QStringList filepaths);

    void updateFiles();

protected:

    void dragEnterEvent(QDragEnterEvent *event) override;

    void dropEvent(QDropEvent *ev) override;

public:

    explicit NavigationTab(Context & context, int id, QWidget *parent = 0);

    ~NavigationTab();

    void onWorkspaceReady() override;

private slots:

    void showContextMenu(const QPoint &);

private:

    Ui::NavigationTab *ui;

    const int _id;

    FileTableModel _model;

    Context & _context;

    PtrList<Tag> _selectedTags;

};

#endif // NAVIGATIONTAB_H
