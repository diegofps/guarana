#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

#include "helpers/context.hpp"
#include "navigationform2.h"
#include "favoritesform.h"
#include "historyform.h"
#include "tagsform.h"
#include "thrashform.h"
#include "settingsform.h"

namespace Ui {
class MainWindow;
}

class MainWindowListener
{
public:
    virtual void onChangeWorkspace() = 0;
};

class MainWindow : public QMainWindow, PagesEndedListener
{

    Q_OBJECT

private:

    void checkButton(int index, QPushButton * bt);

public:

    explicit MainWindow(MainWindowListener * listener, Context & context, QWidget *parent = 0);

    ~MainWindow();

    virtual void onPageEnded();


private slots:

    void on_btMain_clicked();

    void on_btFavorites_clicked();

    void on_btHistory_clicked();

    void on_btTags_clicked();

    void on_btThrash_clicked();

    void on_btSettings_clicked();

    void on_actionSwitch_workspace_triggered();

    void on_actionQuit_triggered();

private:

    Ui::MainWindow *ui;

    Context & _context;

    NavigationForm2 * _navigationForm2;

    FavoritesForm * _favoritesForm;

    HistoryForm * _historyForm;

    TagsForm * _tagsForm;

    ThrashForm * _thrashForm;

    SettingsForm * _settingsForm;

    MainWindowListener * _listener;

};

#endif // MAINWINDOW_H
