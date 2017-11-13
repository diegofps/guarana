#include "navigationform2.h"
#include "ui_navigationform2.h"

NavigationForm2::NavigationForm2(Context & context, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NavigationForm2),
    _context(context),
    _id(0)
{
    ui->setupUi(this);
    createTab();
}

NavigationForm2::~NavigationForm2()
{
    delete ui;
    for (NavigationTab *page : _navigationPages)
        delete page;
}

void NavigationForm2::on_btNewPage_clicked()
{
    createTab();
}

void NavigationForm2::on_btClosePage_clicked()
{
    int index = ui->cbPages->currentIndex();
    NavigationTab *page = _navigationPages[index];

    ui->cbPages->removeItem(index);
    ui->stackedPages->removeWidget(page);
    _navigationPages.removeAt(index);

    delete page;

    if (_navigationPages.size() == 0)
        _context.getLocalBroadcast().sendPagesEnded();
}

void NavigationForm2::on_cbPages_activated(int index)
{
    ui->stackedPages->setCurrentIndex(index);
}

void NavigationForm2::createTab()
{
    ++_id;
    NavigationTab *tab = new NavigationTab(_context, _id);
    _navigationPages.append(tab);

    int index = _navigationPages.count() - 1;

    ui->stackedPages->addWidget(tab);
    ui->stackedPages->setCurrentIndex(index);
    ui->cbPages->addItem("Unnamed tab " + QString::number(_id));
    ui->cbPages->setCurrentIndex(index);
}
