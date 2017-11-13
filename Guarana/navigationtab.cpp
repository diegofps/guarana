#include "navigationtab.h"
#include "ui_navigationtab.h"

#include <QCompleter>
#include <QMenu>

NavigationTab::NavigationTab(Context & context, int id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NavigationTab),
    _id(id),
    _model(_id)
{
    ui->setupUi(this);

    ui->tagFilter->setText(QString::number(_id));

    configureTagFilter();
    configureResultTable();
}

NavigationTab::~NavigationTab()
{
    delete ui;
}

void NavigationTab::configureResultTable()
{
    // Conectar o modelo
    ui->resultTable->setModel(&_model);

    // Ocultar os headers verticais
    ui->resultTable->verticalHeader()->setVisible(false);

    // Ocultar as grades
    ui->resultTable->setShowGrid(false);

    // Modo de seleção por linhas
    ui->resultTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->resultTable->horizontalHeader()->setHighlightSections(false);

    // Expandir a primeira coluna
    ui->resultTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);

    // Construir o menu ao clicar com o botão direito
    ui->resultTable->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->resultTable, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(showContextMenu(const QPoint &)));
}

void NavigationTab::configureTagFilter()
{
    QStringList wordList;
    wordList << "alpha" << "omega" << "omicron" << "zeta";

    QCompleter *completer = new QCompleter(wordList, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);

    ui->tagFilter->setCompleter(completer);
}

void NavigationTab::showContextMenu(const QPoint & pos)
{
    QMenu contextMenu(tr("Context menu"), this);

    QAction action1("Remove Data Point", this);
    //connect(&action1, SIGNAL(triggered()), this, SLOT(removeDataPoint()));
    contextMenu.addAction(&action1);

    // Cria um novo ponto fazendo a translação para o QTableView
    QPoint p2(pos.x() + ui->resultTable->x(),
              pos.y() + ui->resultTable->y());

    contextMenu.exec(mapToGlobal(p2));
}
