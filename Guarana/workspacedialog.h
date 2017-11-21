#ifndef WORKSPACEDIALOG_H
#define WORKSPACEDIALOG_H

#include <QDialog>

#include "mainwindow.h"
#include "helpers/context.hpp"

namespace Ui {
class WorkspaceDialog;
}

class WorkspaceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WorkspaceDialog(Context & context, QWidget *parent = 0);
    ~WorkspaceDialog();

private slots:

    void on_btBrowse_clicked();

    void on_btAccept_clicked();

private:

    Ui::WorkspaceDialog * ui;

    Context & _context;

    QStringList _candidateList;

    MainWindow * _mainWindow;

    bool selectItem(QString & dir);

    void showMainWindow();

};

#endif // WORKSPACEDIALOG_H
