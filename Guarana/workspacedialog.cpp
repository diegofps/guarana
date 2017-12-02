#include "workspacedialog.h"
#include "ui_workspacedialog.h"
#include "mainwindow.h"

#include <QFileDialog>

WorkspaceDialog::WorkspaceDialog(Context & context, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WorkspaceDialog),
    _context(context),
    _candidateList(_context.getConfigManager().getWorkspaceLocations()),
    _mainWindow(nullptr)
{
    ui->setupUi(this);

    if (_context.getConfigManager().hasLastWorkspaceLocation())
    {
        showMainWindow();
    }
    else
    {
        show();
        ui->cbDataFolders->addItems(_context.getConfigManager().getWorkspaceLocations());
    }
}

WorkspaceDialog::~WorkspaceDialog()
{
    delete ui;
    if (_mainWindow != nullptr)
        delete _mainWindow;
}

void WorkspaceDialog::on_btBrowse_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Select folder"),
                                                 EnvHelper::getHomeFolder(),
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);

    if (selectItem(dir))
        return;

    _candidateList.append(dir);
    ui->cbDataFolders->addItem(dir);
    ui->cbDataFolders->setCurrentIndex(_candidateList.size()-1);
}

bool WorkspaceDialog::selectItem(QString & dir)
{
    for (int i=0;i<_candidateList.size(); ++i)
    {
        if (_candidateList[i] == dir)
        {
            ui->cbDataFolders->setCurrentIndex(i);
            return true;
        }
    }

    return false;
}

void WorkspaceDialog::showMainWindow()
{
    hide();
    QString path = _context.getConfigManager().getLastWorkspaceLocation();
    _context.openWorkspace(path);
    _mainWindow = new MainWindow(_context);
    _mainWindow->show();
}

void WorkspaceDialog::on_btAccept_clicked()
{
    QString dir = ui->cbDataFolders->currentText();
    QDir tmp;

    if (tmp.exists(dir) || tmp.mkpath(dir))
    {
        _context.getConfigManager().setLastWorkspaceLocation(dir);
        _context.getConfigManager().saveSettings();

        showMainWindow();
    }
    else
    {
        ui->msgLabel->setText("Could not access this folder");
    }
}
