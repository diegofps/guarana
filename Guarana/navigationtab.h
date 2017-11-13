#ifndef NAVIGATIONTAB_H
#define NAVIGATIONTAB_H

#include <QWidget>

#include "helpers/context.hpp"

namespace Ui {
class NavigationTab;
}

class NavigationTab : public QWidget
{
    Q_OBJECT

public:
    explicit NavigationTab(Context & context, int id, QWidget *parent = 0);
    ~NavigationTab();

private:
    Ui::NavigationTab *ui;

    const int _id;

};

#endif // NAVIGATIONTAB_H
