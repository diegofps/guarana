#include "navigationtab.h"
#include "ui_navigationtab.h"

NavigationTab::NavigationTab(Context & context, int id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NavigationTab),
    _id(id)
{
    ui->setupUi(this);
    ui->tagFilter->setText(QString::number(_id));
}

NavigationTab::~NavigationTab()
{
    delete ui;
}
