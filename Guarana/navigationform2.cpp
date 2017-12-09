#include "navigationform2.h"
#include "ui_navigationform2.h"

NavigationForm2::NavigationForm2(Context & context, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NavigationForm2),
    _tabs(true),
    _context(context),
    _id(0)
{
    ui->setupUi(this);
    ui->cbPages->setModel(&_tabs);

    createTab();
}

NavigationForm2::~NavigationForm2()
{
    delete ui;
}

void NavigationForm2::onTitleChanged(NavigationTab * tab, QString &newTitle)
{
    _tabs.refresh();
}

void NavigationForm2::on_btNewPage_clicked()
{
    createTab();
}

void NavigationForm2::on_btClosePage_clicked()
{
    int index = ui->cbPages->currentIndex();
    NavigationTab *page = _tabs[index];

    ui->stackedPages->removeWidget(page);
    _tabs.removeAt(index);

    delete page;

    if (_tabs.size() == 0)
        _context.getLocalBroadcast().sendPagesEnded();
}

void NavigationForm2::on_cbPages_activated(int index)
{
    ui->stackedPages->setCurrentIndex(index);
}

void NavigationForm2::createTab()
{
    ++_id;
    NavigationTab *tab = new NavigationTab(_context, this, _id);
    _tabs.append(tab);

    int index = _tabs.count() - 1;

    _tabs.refresh();
    ui->stackedPages->addWidget(tab);
    ui->stackedPages->setCurrentIndex(index);
    ui->cbPages->addItem("Unnamed tab " + QString::number(_id));
    ui->cbPages->setCurrentIndex(index);
}
