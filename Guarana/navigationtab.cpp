#include "navigationtab.h"
#include "ui_navigationtab.h"

#include <QDesktopServices>
#include <QCompleter>
#include <QMimeData>
#include <QMenu>
#include <QMessageBox>
#include <QDirIterator>
#include <QInputDialog>
#include <QClipboard>
#include <QUrlQuery>

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

void NavigationTab::addFiles(QStringList & filepaths)
{
    for (auto & filepath : filepaths)
        _context.getWorkspace().importFromFS(filepath, _selectedTags.getModel());
}

void NavigationTab::updateFiles()
{
    _context.getWorkspace().filter(
                _selectedTags.getModel(),
                ui->textFilter->text(),
                _model.getModel(),
                true);
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
    const QMimeData *mimeData = event->mimeData();

    if (!mimeData->hasUrls())
    {
        qDebug("Mime doesnt have urls");
        return;
    }

    qDebug("Mime has urls");
    QStringList filesList;
    QList<QUrl> urlList = mimeData->urls();

    for (QUrl & url : urlList)
    {
        if (!url.isLocalFile())
            continue;

        QString filename = url.toLocalFile();
        QFileInfo info(filename);

        if (!info.isDir())
        {
            filesList.append(filename);
            continue;
        }

        QMessageBox box;
        box.setWindowTitle("Add folder");
        box.setText(filename + " is a local folder.\n\nWould you like to add the folder or its files?");
        box.addButton("&Cancel", QMessageBox::YesRole);
        box.addButton("F&iles", QMessageBox::YesRole);
        box.addButton("&Folder", QMessageBox::YesRole);

        box.exec();

        if (box.clickedButton() == box.buttons().at(1))
        {
            qDebug() << "Add files selected";
            QDirIterator dirIt(filename, QDirIterator::Subdirectories);
            while(dirIt.hasNext())
            {
                QString current = dirIt.next();
                QFileInfo currentInfo(current);

                if (currentInfo.isSymLink() || currentInfo.isDir())
                    continue;

                qDebug() << "Adding file: " << current;
                filesList.append(current);
            }
        }

        else if (box.clickedButton() == box.buttons().at(2))
        {
            qDebug() << "Add folder selected";
            filesList.append(filename);
        }

        else
        {
            qDebug() << "Cancel selected";
        }
    }

    addFiles(filesList);
    updateFiles();
}

void NavigationTab::createActions(QMenu & parentMenu,
                                  FileMap & parentFile,
                                  PtrList<QAction> & actionsList,
                                  PtrList<QMenu> & menusList,
                                  PtrList<Receiver> & receiversList)
{
    for (FileMap * file : parentFile)
    {
        if (file->isDir())
        {
            QMenu * menu = new QMenu(file->getName(), this);
            parentMenu.addMenu(menu);
            menusList.append(menu);

            createActions(*menu, *file, actionsList, menusList, receiversList);
        }
        else
        {
            QAction * action = new QAction(file->getName(), this);
            parentMenu.addAction(action);
            actionsList.append(action);

            Receiver * receiver = new Receiver(this, file->getPath());
            receiversList.append(receiver);

            connect(action, &QAction::triggered, receiver, &Receiver::triggered );
        }
    }
}

void NavigationTab::showContextMenu(const QPoint & pos)
{
    QMenu contextMenu(tr("Context menu"), this);

    QAction rename("Rename", this);
    QAction cut("Cut", this);
    QAction copy("Copy", this);
    QAction paste("Paste", this);
    QAction remove("Remove", this);
    QAction editTags("Tags", this);
    QAction refresh("Refresh", this);

    PtrList<QMenu> menuList;
    PtrList<QAction> actionsList;
    PtrList<Receiver> receiverList;

    FileMap & newFiles = _context.getTemplates();
    QMenu menuNewFile(newFiles.getName(), this);
    createActions(menuNewFile, newFiles, actionsList, menuList, receiverList);

    FileMap & execActions = _context.getActions();
    QMenu menuExecActions(execActions.getName(), this);
    createActions(menuExecActions, execActions, actionsList, menuList, receiverList);

    //connect(&templates, &QAction::triggered, [&]() { this->createFromTemplate(filepath); } );

    connect(&rename, SIGNAL( triggered() ), this, SLOT( renameElements() ));
    connect(&cut, SIGNAL( triggered() ), this, SLOT( cutElements() ));
    connect(&copy, SIGNAL( triggered() ), this, SLOT( copyElements() ));
    connect(&paste, SIGNAL( triggered() ), this, SLOT( pasteElements() ));
    connect(&remove, SIGNAL( triggered() ), this, SLOT( removeElements() ));
    connect(&editTags, SIGNAL( triggered() ), this, SLOT( editTags() ));
    connect(&refresh, SIGNAL( triggered() ), this, SLOT( refresh() ));

    contextMenu.addMenu(&menuNewFile);
    contextMenu.addMenu(&menuExecActions);
    contextMenu.addSeparator();
    contextMenu.addAction(&cut);
    contextMenu.addAction(&copy);
    contextMenu.addAction(&paste);
    contextMenu.addAction(&rename);
    contextMenu.addSeparator();
    contextMenu.addAction(&refresh);
    contextMenu.addAction(&editTags);
    contextMenu.addSeparator();
    contextMenu.addAction(&remove);

    // Cria um novo ponto fazendo a translação para o QTableView

//    Abordagem antiga
//    QPoint p2(pos.x() + ui->resultTable->x() + ui->splitter->x(),
//              pos.y() + ui->resultTable->y() + ui->splitter->y());

//    Nova abordagem
    QPoint p2(pos.x(), pos.y());
    QWidget *current = ui->resultTable;
    while(current != nullptr && current != this)
    {
        p2.setX(p2.x() + current->x());
        p2.setY(p2.y() + current->y());
        current = current->parentWidget();
    }

    qDebug() << "Context started";
    contextMenu.exec(mapToGlobal(p2));
    qDebug() << "Context ended";

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

void NavigationTab::refresh()
{
    qDebug() << "Refresh";
    updateFiles();
    QClipboard *cboard = QApplication::clipboard();
    qDebug() << "Current clipboard content:" << cboard->text();
}

void NavigationTab::renameElements()
{
    qDebug() << "Rename";
    QModelIndexList indexes = ui->resultTable->selectionModel()->selectedRows();

    if (indexes.isEmpty())
    {
        qDebug() << "No file selected";
        return;
    }

    FileViewModel * view = _model.getModel().at(indexes.at(0).row());

    bool ok;
    QString text = QInputDialog::getText(this, tr("Rename"),
                                         tr("New name:"), QLineEdit::Normal,
                                         view->getFilename(), &ok);
    if (ok && !text.isEmpty())
    {
        QList<int> ids;
        for (auto index : indexes)
            ids.append(_model.getModel().at(index.row())->getGuaranaFileId());
        _context.getWorkspace().rename(ids, text);
    }

    updateFiles();
}

void NavigationTab::cutElements()
{
    qDebug() << "Cut";
    updateClipboardWithSelectedFiles(true);
}

void NavigationTab::copyElements()
{
    qDebug() << "Copy";
    updateClipboardWithSelectedFiles(false);
}

void NavigationTab::updateClipboardWithSelectedFiles(bool cut)
{
    QList<QUrl> urls;
    GuaranaFile file;
    Workspace & workspace = _context.getWorkspace();

    QModelIndexList indexes = ui->resultTable->selectionModel()->selectedRows();
    for (auto & index : indexes)
    {
        FileViewModel * view = _model.getModel().at(index.row());

        workspace.getFileById(view->getGuaranaFileId(), file);
        if (file.getId() == 0)
            continue;

//        QString filepath = workspace.getFilePath(file);
//        QUrl url = QUrl::fromLocalFile(filepath);

        QUrlQuery query;
        query.addQueryItem("id", QString::number(file.getId()));
        query.addQueryItem("uuid", file.getUuid());

        QUrl t;
        t.setPath(workspace.getLocation());
        t.setScheme("guarana");
        t.setQuery(query);

        urls.append(t);
    }

    QClipboard *cboard = QApplication::clipboard();
    QMimeData * mime = new QMimeData();

    mime->setUrls(urls);
    mime->setText(cut ? "guarana-cut" : "guarana-copy");
    cboard->setMimeData(mime, QClipboard::Clipboard);

    qDebug() << "Updated clipboard content:" << cboard->text();
}

void NavigationTab::pasteElements()
{
    qDebug() << "Paste";
    QClipboard *clipboard = QApplication::clipboard();
    const QMimeData *mime = clipboard->mimeData();

    if (!mime->hasUrls())
    {
        qDebug() << "Mime has no urls";
        return;
    }

    QList<QUrl> urls = mime->urls();
    QMap<QString, QList<int>*> workspaces;
    cast(urls, workspaces);

    QMapIterator<QString, QList<int>*> it(workspaces);
    if (mime->text() == "guarana-cut")
    {
        while(it.hasNext())
        {
            it.next();
            _context.getWorkspace().importFromWS(it.key(), *it.value(), _selectedTags.getModel(), true);
            delete it.value();
        }
    }
    else
    {
        while(it.hasNext())
        {
            it.next();
            _context.getWorkspace().importFromWS(it.key(), *it.value(), _selectedTags.getModel(), false);
            delete it.value();
        }
    }

    updateFiles();
}

void NavigationTab::cast(QList<QUrl> & urls, QMap<QString, QList<int>*> & workspaces)
{
    for (QUrl url : urls)
    {
        if (url.scheme() != "guarana")
            continue;

        // We get the info we need to execute the cut (workspace location and id)
        QUrlQuery query(url);
        int fileId = query.queryItemValue("id").toInt();
        QString fileWorkspace = url.path();

        if (!workspaces.contains(fileWorkspace))
            workspaces[fileWorkspace] = new QList<int>();

        workspaces[fileWorkspace]->append(fileId);
    }
}

void NavigationTab::editTags()
{
    QModelIndexList rows = ui->resultTable->selectionModel()->selectedRows();
    qDebug() << "Tags";
}

void NavigationTab::newFromTemplate(QString & filepath)
{
    QStringList filesList;
    filesList.append(filepath);
    addFiles(filesList);
    updateFiles();
}

void NavigationTab::removeElements()
{
    QModelIndexList indexes = ui->resultTable->selectionModel()->selectedRows();

    qDebug() << "Remove";
    for (auto index : indexes)
    {
        FileViewModel * ptr = _model.getModel().at(index.row());
        _context.getWorkspace().remove(ptr->getGuaranaFileId());
        qDebug() << index.row() << ", " << index.column() << ": " << ptr->getFilename();
    }

    updateFiles();
}

void NavigationTab::on_resultTable_doubleClicked(const QModelIndex &index)
{
    GuaranaFile gfile;
    FileViewModel * view = _model.getModel().at(index.row());

    _context.getWorkspace().getFileById(view->getGuaranaFileId(), gfile);
    if (gfile.getId() == 0)
    {
        qDebug() << "File not found";
        return;
    }

    QString filepath = _context.getWorkspace().getFilePath(gfile);
    QUrl url = QUrl::fromLocalFile(filepath);
    QDesktopServices::openUrl(url);
}
