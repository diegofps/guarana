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

    configureShortcuts();
    newTab();
}

NavigationForm2::~NavigationForm2()
{
    delete _shortcutNewTab;
    delete _shortcutCloseTab;
    delete _shortcutNextTab;
    delete _shortcutPreviousTab;
    delete ui;
}

void NavigationForm2::configureShortcuts()
{
    _shortcutNewTab = new QShortcut(QKeySequence("Ctrl+T"), this);
    _shortcutCloseTab = new QShortcut(QKeySequence("Ctrl+W"), this);
    _shortcutNextTab = new QShortcut(QKeySequence("Ctrl+Tab"), this);
    _shortcutPreviousTab = new QShortcut(QKeySequence("Ctrl+Shift+Tab"), this);

    connect(_shortcutNewTab, SIGNAL(activated()), this, SLOT(newTab()));
    connect(_shortcutCloseTab, SIGNAL(activated()), this, SLOT(closeTab()));
    connect(_shortcutNextTab, SIGNAL(activated()), this, SLOT(nextTab()));
    connect(_shortcutPreviousTab, SIGNAL(activated()), this, SLOT(previousTab()));
}

void NavigationForm2::onTitleChanged(NavigationTab * /*tab*/, QString & /*newTitle*/)
{
    _tabs.refresh();
}

void NavigationForm2::newTab()
{
    qDebug() << "New tab";

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

void NavigationForm2::closeTab()
{
    qDebug() << "Close tab";

    int index = ui->cbPages->currentIndex();
    NavigationTab *page = _tabs[index];
    ui->stackedPages->removeWidget(page);
    _tabs.removeAt(index);

    if (_tabs.size() == 0)
        _context.getLocalBroadcast().sendPagesEnded();

    else if (index >= _tabs.size())
        ui->cbPages->setCurrentIndex(index-1);

    else
        ui->cbPages->setCurrentIndex(index);
}

void NavigationForm2::on_cbPages_activated(int index)
{
    qDebug() << "Tab changed";
    ui->stackedPages->setCurrentIndex(index);
}

void NavigationForm2::nextTab()
{
    qDebug() << "Next tab";
    navigateTab(+1);
}

void NavigationForm2::previousTab()
{
    qDebug() << "Previous tab";
    navigateTab(-1);
}

void NavigationForm2::navigateTab(const int relativeIndex)
{
    int current = ui->cbPages->currentIndex();
    int size = ui->cbPages->count();
    int newIndex = (current + relativeIndex ) % size;

    if (newIndex < 0)
        newIndex += size;

    if (newIndex < 0)
        newIndex = 0;

    qDebug() << "Relative index: " << relativeIndex;
    qDebug() << "Previous index: " << current;
    qDebug() << "New index: " << newIndex;
    qDebug() << "Size: " << size;

    ui->cbPages->setCurrentIndex(newIndex);
    on_cbPages_activated(newIndex);
}
