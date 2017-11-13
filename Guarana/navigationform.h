#ifndef NAVIGATIONFORM_H
#define NAVIGATIONFORM_H

#include <QWidget>

namespace Ui {
class NavigationForm;
}

class NavigationForm : public QWidget
{
    Q_OBJECT

    void createAddTabButton();

public:
    explicit NavigationForm(QWidget *parent = 0);
    ~NavigationForm();

private:
    Ui::NavigationForm *ui;
};

#endif // NAVIGATIONFORM_H
