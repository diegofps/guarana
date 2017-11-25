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

class MainWindow : public QMainWindow, PagesEndedListener
{

    Q_OBJECT

private:

    void checkButton(int index, QPushButton * bt);

public:

    explicit MainWindow(Context & context, QWidget *parent = 0);

    ~MainWindow();

    void configureFor(QString & dataFolder);

    virtual void onPageEnded();

private slots:

    void on_btMain_clicked();

    void on_btFavorites_clicked();

    void on_btHistory_clicked();

    void on_btTags_clicked();

    void on_btThrash_clicked();

    void on_btSettings_clicked();

private:

    Ui::MainWindow *ui;

    Context & _context;

    NavigationForm2 * _navigationForm2;

    FavoritesForm * _favoritesForm;

    HistoryForm * _historyForm;

    TagsForm * _tagsForm;

    ThrashForm * _thrashForm;

    SettingsForm * _settingsForm;

};

#endif // MAINWINDOW_H
