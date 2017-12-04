#ifndef NAVIGATIONTAB_H
#define NAVIGATIONTAB_H

#include <QWidget>
#include <QAbstractTableModel>
#include <QCompleter>
#include <QMenu>

#include <widgetmodels/filetablemodel.hpp>
#include <widgetmodels/taglistmodel.hpp>

#include "helpers/context.hpp"


namespace Ui {
class NavigationTab;
}

class ReceiverListener
{
public:
    virtual void newFromTemplate(QString & filepath) = 0;
};

class Receiver : public QObject
{

    Q_OBJECT

private:

    ReceiverListener * _listener;

    QString & _filepath;

public:

    Receiver(ReceiverListener * listener, QString & filepath) :
        _listener(listener),
        _filepath(filepath)
    {

    }

public slots:

    void triggered()
    {
        _listener->newFromTemplate(_filepath);
    }

};

class NavigationTab : public QWidget, ReceiverListener
{
    Q_OBJECT

private:

    void configureResultTable();

    void configureTagFilter();

    void configureTagList();

    void addFiles(QStringList & filepaths);

    void addFolders(QStringList & folderpaths);

    void updateFiles();

    void updateTagOptions();

    void createActions(QMenu &parentMenu, FileMap &file, PtrList<QAction> & actionsList, PtrList<QMenu> & menuList,
                       PtrList<Receiver> & receiversList);

    void updateClipboardWithSelectedFiles(bool cut);

    void cast(QList<QUrl> & urls, QMap<QString, QList<int>*> & workspaces);

protected:

    void dragEnterEvent(QDragEnterEvent *event) override;

    void dropEvent(QDropEvent *ev) override;

public:

    explicit NavigationTab(Context & context, int id, QWidget *parent = 0);

    ~NavigationTab();

    virtual void newFromTemplate(QString &filepath);

private slots:

    void showContextMenu(const QPoint &);

    void on_tagFilter_returnPressed();

    void on_btClearTagFilter_clicked();

    void on_btClearTextFilter_clicked();

    void on_textFilter_returnPressed();

    void on_tagsList_doubleClicked(const QModelIndex &index);

    void refresh();

    void editTags();

    void renameElements();

    void cutElements();

    void copyElements();

    void pasteElements();

    void removeElements();

    void on_resultTable_doubleClicked(const QModelIndex &index);

private:

    Ui::NavigationTab *ui;

    FileTableModel _model;

    TagListModel _selectedTags;

    TagListModel _tagOptions;

    Context & _context;

    const int _id;

    QCompleter _tagCompleter;

};

#endif // NAVIGATIONTAB_H
