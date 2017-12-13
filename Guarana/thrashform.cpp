#include "thrashform.h"
#include "ui_thrashform.h"

#include <QMenu>
#include <helpers/displayhelper.hpp>

ThrashForm::ThrashForm(Context & context, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ThrashForm),
    _context(context)
{
    ui->setupUi(this);

    configureGarbageList();
    updateList();
}

ThrashForm::~ThrashForm()
{
    delete ui;
}

void ThrashForm::updateList()
{
    _context.getWorkspace().getRemovedItems(_modelHolder.getModel());
    _modelHolder.notifyContentChanged();
}

void ThrashForm::configureGarbageList()
{
    // Conectar o modelo
    ui->garbageList->setModel(&_modelHolder);

    // Ocultar os headers verticais
    ui->garbageList->verticalHeader()->setVisible(false);

    // Ocultar as grades
    ui->garbageList->setShowGrid(false);

    // Modo de seleção por linhas
    ui->garbageList->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->garbageList->horizontalHeader()->setHighlightSections(false);

    // Expandir a primeira coluna
    ui->garbageList->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);

    // Construir o menu ao clicar com o botão direito
    ui->garbageList->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->garbageList, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(showContextMenu(const QPoint &)));
}

void ThrashForm::eraseAll()
{
    qDebug() << "Clear Thrash";
    _context.getWorkspace().emptyThrash();
    updateList();
}

void ThrashForm::recoverAll()
{
    qDebug() << "Recover all";
    _context.getWorkspace().recoverThrash();
    updateList();
}

void ThrashForm::recoverSelected()
{
    qDebug() << "Recover selected";
    QList<int> ids;

    for (auto & index : ui->garbageList->selectionModel()->selectedRows())
        ids.append(_modelHolder.getModel().at(index.row())->getGuaranaFileId());

    _context.getWorkspace().recoverFilesFromThrash(ids);

    updateList();
}

void ThrashForm::eraseSelected()
{
    qDebug() << "Erase selected";
    QList<int> ids;

    for (auto & index : ui->garbageList->selectionModel()->selectedRows())
        ids.append(_modelHolder.getModel().at(index.row())->getGuaranaFileId());
    _context.getWorkspace().destroyFiles(ids);

    updateList();
}

void ThrashForm::showContextMenu(const QPoint & pos)
{
    QMenu contextMenu(tr("Context menu"), this);

    QAction recover("Recover", this);
    QAction erase("Remove forever", this);
    QAction refresh("Refresh list", this);

    connect(&recover, SIGNAL( triggered() ), this, SLOT( recoverSelected() ));
    connect(&erase, SIGNAL( triggered() ), this, SLOT( eraseSelected() ));
    connect(&refresh, SIGNAL( triggered() ), this, SLOT( updateList() ));

    contextMenu.addAction(&recover);
    contextMenu.addSeparator();
    contextMenu.addAction(&refresh);
    contextMenu.addAction(&erase);

    contextMenu.exec(ui->garbageList->mapToGlobal(pos));
}
