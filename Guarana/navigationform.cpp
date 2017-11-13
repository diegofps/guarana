#include "navigationform.h"
#include "ui_navigationform.h"

#include <QToolButton>
#include <QLabel>

NavigationForm::NavigationForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NavigationForm)
{
    ui->setupUi(this);
    createAddTabButton();
}

NavigationForm::~NavigationForm()
{
    delete ui;
}

void NavigationForm::createAddTabButton()
{
    QToolButton *tb = new QToolButton();
    tb->setText("+");
    tb->setStyleSheet("background-color: #0000");

    ui->tabWidget->addTab(new QLabel("Add tabs by pressing \"+\""), QString());

    int lastIndex = ui->tabWidget->tabBar()->count()-1;
    ui->tabWidget->setTabEnabled(lastIndex, false);
    ui->tabWidget->tabBar()->setTabButton(lastIndex, QTabBar::RightSide, tb);
}
