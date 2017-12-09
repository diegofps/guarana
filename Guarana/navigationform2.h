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

public:

    explicit NavigationForm2(Context & context, QWidget *parent = 0);

    ~NavigationForm2();

    void init(Context context);

    virtual void onTitleChanged(NavigationTab * tab, QString & newTitle);

private slots:

    void on_btNewPage_clicked();

    void on_btClosePage_clicked();

    void on_cbPages_activated(int index);

private:

    Ui::NavigationForm2 * ui;

    PtrListModel<NavigationTab, &NavigationTab::getTitle> _tabs;

    Context & _context;

    int _id;

};

#endif // NAVIGATIONFORM2_H
