#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(MainWindowListener * listener, Context & context, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _context(context),
    _listener(listener)
{
    ui->setupUi(this);

    _navigationForm2 = new NavigationForm2(context, this);
    _favoritesForm = new FavoritesForm(context, this);
    _historyForm = new HistoryForm(context, this);
    _tagsForm = new TagsForm(context, this);
    _thrashForm = new ThrashForm(context, this);
    _settingsForm = new SettingsForm(context, this);

    ui->stackedWidget->addWidget(_navigationForm2);
    ui->stackedWidget->addWidget(_favoritesForm);
    ui->stackedWidget->addWidget(_historyForm);
    ui->stackedWidget->addWidget(_tagsForm);
    ui->stackedWidget->addWidget(_thrashForm);
    ui->stackedWidget->addWidget(_settingsForm);
    ui->stackedWidget->setCurrentIndex(0);

    setWindowTitle("Guarana - " + context.getWorkspace().getLocation());

    context.getLocalBroadcast().registerPageEndedListener(this);
    //context.getLocalBroadcast().sendWorkspaceReady();
    //context.getLocalBroadcast().registerListener();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete _navigationForm2;
    delete _favoritesForm;
    delete _historyForm;
    delete _tagsForm;
    delete _thrashForm;
    delete _settingsForm;
}

void MainWindow::onPageEnded()
{
    close();
}

void MainWindow::on_btMain_clicked()
{
    checkButton(0, ui->btMain);
}

void MainWindow::on_btFavorites_clicked()
{
    checkButton(1, ui->btFavorites);
}

void MainWindow::on_btHistory_clicked()
{
    checkButton(2, ui->btHistory);
}

void MainWindow::on_btTags_clicked()
{
    checkButton(3, ui->btTags);
}

void MainWindow::on_btThrash_clicked()
{
    checkButton(4, ui->btThrash);
}

void MainWindow::on_btSettings_clicked()
{
    checkButton(5, ui->btSettings);
}

void MainWindow::checkButton(int index, QPushButton * bt)
{
    ui->stackedWidget->setCurrentIndex(index);

    ui->btMain->setChecked(false);
    ui->btFavorites->setChecked(false);
    ui->btHistory->setChecked(false);
    ui->btTags->setChecked(false);
    ui->btThrash->setChecked(false);
    ui->btSettings->setChecked(false);

    bt->setChecked(true);
}

void MainWindow::on_actionSwitch_workspace_triggered()
{
    close();
    _listener->onChangeWorkspace();
}

void MainWindow::on_actionQuit_triggered()
{
    close();
}
