#ifndef WORKSPACE_H
#define WORKSPACE_H

#include <QList>
#include <QString>
#include <QFileInfo>

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

public:

    Workspace() : _db(nullptr)
    {

    }

    void setWorkspaceLocation(QString path)
    {
        _workspace = path;

        if (_db != nullptr)
            delete _db;

        _db = new DBManager(_workspace + "/guarana.db");
    }

    void copyFileFromFS(QString filepath, PtrList<Tag> & tags)
    {
        QFileInfo fi(filepath);
        GuaranaFile gfile(fi.fileName(), RandomHelper::createGuid());

        QString innerFileLocation = getFileLocation(gfile);
        QString innerFilePath = getFilePath(gfile);

        QDir().mkpath(innerFileLocation);
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

    void filter(PtrList<Tag> & tagsFilter, QString textFilter, PtrList<FileViewModel> & result)
    {
        // Check the tags received
        for (Tag * tag : tagsFilter)
        {
            if (tag->getId() == 0)
            {
                _db->getTagManager().getByName(tag->getName(), *tag);
                if (tag->getId() == 0)
                {
                    result.clear();
                    return;
                }
            }
        }

        // Get the files for the given tags
        PtrList<GuaranaFile> gfiles;
        _db->getGuaranaFileManager().filter(tagsFilter, textFilter, gfiles);

        // Cast the files to the corresponding viewmodel
        Merlin::castList(gfiles, result, _workspace);
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

    QString getRootLocation()
    {
        return _workspace;
    }

private:

    QString _workspace;

};

#endif // WORKSPACE_H
