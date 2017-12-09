#ifndef NAVIGATIONFORM2_H
#define NAVIGATIONFORM2_H

#include <QWidget>
#include "navigationtab.h"

#include "helpers/context.hpp"

namespace Ui {
class NavigationForm2;
}

class NavigationForm2 : public QWidget, NavigationTabListener
{

    Q_OBJECT

private:

    void createTab();

    void navigateTab(const int relativeIndex);

    void configureShortcuts();

public:

    explicit NavigationForm2(Context & context, QWidget *parent = 0);

    ~NavigationForm2();

    void init(Context context);

    virtual void onTitleChanged(NavigationTab * tab, QString & newTitle);

private slots:

    void newTab();

    void closeTab();

    void on_cbPages_activated(int index);

    void nextTab();

    void previousTab();

private:

    Ui::NavigationForm2 * ui;

    PtrListModel<NavigationTab, &NavigationTab::getTitle> _tabs;

    Context & _context;

    int _id;

    QShortcut * _shortcutNewTab;

    QShortcut * _shortcutCloseTab;

    QShortcut * _shortcutNextTab;

    QShortcut * _shortcutPreviousTab;

};

#endif // NAVIGATIONFORM2_H
