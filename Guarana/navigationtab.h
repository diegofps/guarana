#ifndef NAVIGATIONTAB_H
#define NAVIGATIONTAB_H

#include <QWidget>
#include <QAbstractTableModel>
#include <QCompleter>

#include <widgetmodels/filetablemodel.hpp>
#include <widgetmodels/taglistmodel.hpp>

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

    void configureTagList();

    void addFiles(QStringList filepaths);

    void updateFiles();

    void updateTagOptions();

protected:

    void dragEnterEvent(QDragEnterEvent *event) override;

    void dropEvent(QDropEvent *ev) override;

public:

    explicit NavigationTab(Context & context, int id, QWidget *parent = 0);

    ~NavigationTab();

    void onWorkspaceReady() override;

private slots:

    void showContextMenu(const QPoint &);

    void on_tagFilter_returnPressed();

    void on_btClearTagFilter_clicked();

    void on_btClearTextFilter_clicked();

    void on_textFilter_returnPressed();

    void on_tagsList_doubleClicked(const QModelIndex &index);

private:

    Ui::NavigationTab *ui;

    const int _id;

    FileTableModel _model;

    Context & _context;

    TagListModel _selectedTags;

    TagListModel _tagOptions;

    QCompleter _tagCompleter;

};

#endif // NAVIGATIONTAB_H
