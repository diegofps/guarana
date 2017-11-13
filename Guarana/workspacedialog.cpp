#include "workspacedialog.h"
#include "ui_workspacedialog.h"
#include "mainwindow.h"

#include <QFileDialog>

WorkspaceDialog::WorkspaceDialog(Context & context, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WorkspaceDialog),
    _cm(context.getConfigManager()),
    _candidateList(_cm.getDataFolders()),
    _mainWindow(context)
{
    ui->setupUi(this);

    if (_cm.hasDefaultDataFolder())
    {
        hide();

        _mainWindow.configureFor(_cm.getDefaultDataFolder());
        _mainWindow.show();
    }
    else
    {
        show();
        ui->cbDataFolders->addItems(_cm.getDataFolders());
    }
}

WorkspaceDialog::~WorkspaceDialog()
{
    delete ui;
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

void WorkspaceDialog::on_btAccept_clicked()
{
    QString dir = ui->cbDataFolders->currentText();
    QDir tmp;

    if (tmp.exists(dir) || tmp.mkdir(dir))
    {
        hide();

        _cm.setDefaultDataFolder(dir);
        _cm.save();

        _mainWindow.configureFor(_cm.getDefaultDataFolder());
        _mainWindow.show();
    }
    else
    {
        ui->msgLabel->setText("Could not access this folder");
    }
}
