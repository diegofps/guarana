#include "navigationtab.h"
#include "ui_navigationtab.h"

#include <QCompleter>
#include <QMimeData>
#include <QMenu>

NavigationTab::NavigationTab(Context & context, int id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NavigationTab),
    _context(context),
    _id(id),
    _tagCompleter(&_tagOptions)
{
    ui->setupUi(this);

    setAcceptDrops(true);

    configureTagFilter();
    configureTagList();
    configureResultTable();

    _context.getLocalBroadcast().registerWorkspaceReadyListener(this);
    _context.getWorkspace().getDB().getTagManager().getAll(_tagOptions.getModel());
    _tagOptions.refresh();
}

NavigationTab::~NavigationTab()
{
    delete ui;
}

void NavigationTab::onWorkspaceReady()
{
    updateFiles();
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
//    QStringList wordList;
//    wordList << "alpha" << "omega" << "omicron" << "zeta";

//    QCompleter *completer = new QCompleter(wordList, this);
//    completer->setCaseSensitivity(Qt::CaseInsensitive);

//    ui->tagFilter->setCompleter(completer);
    ui->tagFilter->setCompleter(&_tagCompleter);
}

void NavigationTab::configureTagList()
{
    ui->tagsList->setModel(&_selectedTags);
}

void NavigationTab::addFiles(QStringList filepaths)
{
    for (auto & filepath : filepaths)
        _context.getWorkspace().copyFileFromFS(filepath, _selectedTags.getModel());

    updateFiles();
}

void NavigationTab::updateFiles()
{
    _context.getWorkspace().filter(
                _selectedTags.getModel(),
                ui->textFilter->text(),
                _model.getModel());
    _model.refresh();
}

//void NavigationTab::updateTagOptions()
//{
//    _tagOptions.getModel().clear();
//    _context.getWorkspace().getDB().getTagManager().getNested(
//                _selectedTags.getModel(),
//                _tagOptions.getModel());
//}

void NavigationTab::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("text/plain"))
        event->acceptProposedAction();
}

void NavigationTab::dropEvent(QDropEvent *event)
{
    qDebug() << "Here" ;
//    const QMimeData * mimeData = event->mimeData();
//    if (mimeData->hasUrls())
//    {
//        QString txt = mimeData->text();
//        qDebug() << txt;
//    }
    const QMimeData *mimeData = event->mimeData();

    if (mimeData->hasUrls())
    {
        qDebug("It has");
        QStringList pathList;
        QList<QUrl> urlList = mimeData->urls();

        for (int i = 0; i < urlList.size(); ++i)
            if (urlList.at(i).isLocalFile())
                pathList.append(urlList.at(i).toLocalFile());

        addFiles(pathList);
    }
    else
    {
        qDebug("It doesnt");
    }
}

void NavigationTab::showContextMenu(const QPoint & pos)
{
    QMenu contextMenu(tr("Context menu"), this);

    QAction action1("Remove Data Point", this);
    //connect(&action1, SIGNAL(triggered()), this, SLOT(removeDataPoint()));
    contextMenu.addAction(&action1);

    // Cria um novo ponto fazendo a translação para o QTableView
    QPoint p2(pos.x() + ui->resultTable->x() + ui->splitter->x(),
              pos.y() + ui->resultTable->y() + ui->splitter->y());

    contextMenu.exec(mapToGlobal(p2));
}

void NavigationTab::on_tagFilter_returnPressed()
{
    QString tagName = ui->tagFilter->text();
    Tag * tag = _tagOptions.getOrDefault(tagName);

    if (tag == nullptr)
        tag = new Tag(tagName);

    if (!_selectedTags.contains(tagName))
    {
        _selectedTags.getModel().append(tag);
        _selectedTags.refresh();
        updateFiles();
    }

    ui->tagFilter->clear();
}

void NavigationTab::on_btClearTagFilter_clicked()
{
    ui->tagFilter->clear();
    updateFiles();
}

void NavigationTab::on_btClearTextFilter_clicked()
{
    ui->textFilter->clear();
    updateFiles();
}

void NavigationTab::on_textFilter_returnPressed()
{
    updateFiles();
}

void NavigationTab::on_tagsList_doubleClicked(const QModelIndex &index)
{
    _selectedTags.getModel().removeAt(index.row());
    _selectedTags.refresh();
    updateFiles();
}
