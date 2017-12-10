#ifndef WORKSPACE_H
#define WORKSPACE_H

#include <QList>
#include <QString>
#include <QFileInfo>
#include <QClipboard>
#include <QApplication>
#include <QMimeData>
#include <QUrlQuery>

#include <helpers/ptrlist.hpp>

#include "dal/models/guaranafile.hpp"
#include "dal/models/tag.hpp"
#include "dal/dbmanager.hpp"
#include "dal/models/_guaranafile_tag.hpp"
#include "dal/managers/guaranafile_manager.hpp"
#include "dal/managers/_guaranafile_tag_manager.hpp"
#include "viewmodels/fileviewmodel.hpp"
#include "helpers/merlin.hpp"
#include "helpers/randomhelper.hpp"

class Workspace
{
private:

    DBManager * _db;

    QString _workspace;

public:

    Workspace() : _db(nullptr)
    {

    }

    void setWorkspaceLocation(QString path, bool skipExtraFolders=false)
    {
        if (path == _workspace)
            return;

        _workspace = path;

        if (_db != nullptr)
            delete _db;

        _db = new DBManager(_workspace + "/guarana.db");

        if (!skipExtraFolders)
        {
            QDir tmp;
            tmp.mkpath(getWorkspaceTemplatesDir());
            tmp.mkpath(getWorkspaceActionsDir());
        }
    }

    QString getWorkspaceActionsDir() const
    {
        return _workspace + "/actions";
    }

    QString getWorkspaceTemplatesDir() const
    {
        return _workspace + "/new";
    }

    void remove(int fileId)
    {
        auto & manager = _db->getGuaranaFileManager();

        GuaranaFile file;
        manager.getById(fileId, file);

        if (file.getId() == 0)
            return;

        //auto date = QDateTime::currentDateTime();
        file.setRemovedDate(QDateTime::currentDateTime());
        file.setIsAlive(false);

        manager.update(file);
    }

    void rename(QList<int> ids, QString & newName)
    {
        GuaranaFileManager & manager = _db->getGuaranaFileManager();
        GuaranaFile file;
        QDir dir;

        for (int id : ids)
        {
            manager.getById(id, file);

            if (file.getId() == 0 || newName == file.getFilename())
                continue;

            QString location = getFileLocation(file);
            QString oldFilepath = location + "/" + file.getFilename();
            QString newFilepath = location + "/" + newName;

            if (dir.rename(oldFilepath, newFilepath))
            {
                file.setFilename(newName);
                manager.update(file);
            }
            else
            {
                qDebug() << "Could not rename: " << getFilePath(file);
            }
        }
    }

    void getFileById(int id, GuaranaFile & gfile)
    {
        _db->getGuaranaFileManager().getById(id, gfile);
    }

    void importFromWS(const QString & oldWorkspace, const QList<int> & oldIds, const PtrList<Tag> & newTags, const bool moveFiles=false)
    {
        QString newWorkspace = _workspace;
        QStringList srcFilepaths;
        QStringList srcFolders;
        GuaranaFile oldFile;
        QList<int> validIds;

        // We access the original workspace to see if the files exist and get their paths
        setWorkspaceLocation(oldWorkspace, true);
        for (int oldId : oldIds)
        {
            _db->getGuaranaFileManager().getById(oldId, oldFile);
            // If it doesn't exists we ignore the file
            if (oldFile.getId() == 0)
            {
                qDebug() << "Could not locate src file with id: " << oldId;
                continue;
            }

            validIds.append(oldId);
            srcFilepaths.append(getFilePath(oldFile));
            srcFolders.append(getFileLocation(oldFile));
        }

        // We come back to the new workspace and perform the moves
        setWorkspaceLocation(newWorkspace, true);
        for (QString & oldFilepath : srcFilepaths)
            importFromFS(oldFilepath, newTags, moveFiles);

        // If this is a move then we go to the old workspace to permanently
        // delete the files and then return to our workspace.
        if (moveFiles)
        {
            setWorkspaceLocation(oldWorkspace, true);
            _db->getGuaranaFileManager().destroyAll(validIds);
            setWorkspaceLocation(newWorkspace, true);

            // Remove the uuid folders
            for (QString srcFolder : srcFolders)
                QDir(srcFolder).removeRecursively();
        }
    }

    void importFromFS(const QString & filepath,
                      const PtrList<Tag> & tags,
                      const QString & newName,
                      const bool moveFile=false)
    {
        QFileInfo fi(filepath);
        GuaranaFile gfile(newName, RandomHelper::createGuid());
        QString innerFileLocation = getFileLocation(gfile);
        QString innerFilePath = getFilePath(gfile);
        QDir dir;

        dir.mkpath(innerFileLocation);

        if (moveFile)
            dir.rename(filepath, innerFilePath);

        else if (fi.isDir())
            IOUtils::copyDir(filepath, innerFilePath);

        else
            QFile::copy(filepath, innerFilePath);

        TagManager & tm = _db->getTagManager();
        GuaranaFileManager & gfm = _db->getGuaranaFileManager();
        _GuaranaFile_Tag_Manager & guaranafile_tag_manager = _db->get_GuaranaFile_Tag_Manager();

        qDebug() << "Importing file: " << gfile.getFilename();

        gfm.save(gfile);
        for (Tag * tag : tags)
        {
            if (tag->getId() == 0)
            {
                tm.getByName(tag->getName(), *tag);
                if (tag->getId() == 0)
                    tm.save(*tag);
            }

            _GuaranaFile_Tag gt(gfile.getId(), tag->getId());
            qDebug() << "Including GuaranaFile-Tag association: " << gt.getGuaranaFileId() << ", " << gt.getTagId();
            guaranafile_tag_manager.save(gt);
        }
    }

    void importFromFS(const QString & filepath, const PtrList<Tag> & tags, const bool moveFile=false)
    {
        QFileInfo fi(filepath);
        QString filename = fi.fileName();

        if (filename.startsWith("_"))
            importFromFS(filepath, tags, filename.mid(1, filename.length()), moveFile);
        else
            importFromFS(filepath, tags, filename, moveFile);
    }

    void filter(PtrList<Tag> & tagsFilter, QString textFilter, PtrList<FileViewModel> & result, bool isAlive)
    {
        // Check the tags received
        for (Tag * tag : tagsFilter)
        {
            if (tag->getId() != 0)
                continue;

            _db->getTagManager().getByName(tag->getName(), *tag);

            if (tag->getId() != 0)
                continue;

            result.clear();
            return;
        }

        // Get the files for the given tags
        PtrList<GuaranaFile> gfiles;
        _db->getGuaranaFileManager().filter(tagsFilter, textFilter, gfiles, isAlive);

        // Cast the files to the corresponding viewmodel
        Merlin::castList(gfiles, result, _workspace);
        result.sort();
    }

    void getRemovedItems(PtrList<FileViewModel> & result)
    {
        PtrList<GuaranaFile> gfiles;
        _db->getGuaranaFileManager().getRemovedFiles(gfiles);
        Merlin::castList(gfiles, result, _workspace);
        result.sort();
    }

    QString getFileLocation(GuaranaFile & gfile) const
    {
        return _workspace + "/files/" + gfile.getUuid();
    }

    QString getFilePath(GuaranaFile & gfile) const
    {
        return getFileLocation(gfile) + "/" + gfile.getFilename();
    }

    DBManager & getDB()
    {
        return *_db;
    }

    QString getLocation()
    {
        return _workspace;
    }

};

#endif // WORKSPACE_H
