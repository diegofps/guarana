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

    void setWorkspace(QString path)
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

        GuaranaFileManager & gfm = _db->getGuaranaFileManager();
//        _GuaranaFile_Tag_Manager & guaranafile_tag_manager = _db->get_GuaranaFile_Tag_Manager();

        gfm.save(gfile);
//        for (auto & tag : tags)
//        {
//            _GuaranaFile_Tag gt(gfile.getId(), tag->getId());
//            guaranafile_tag_manager->save(gt);
//        }
    }

    QString getFileLocation(GuaranaFile & gfile) const
    {
        return _workspace + "/files/" + gfile.getUuid();
    }

    QString getFilePath(GuaranaFile & gfile) const
    {
        return getFileLocation(gfile) + "/" + gfile.getFilename();
    }

    void getFiles(PtrList<Tag> & tagsFilter, QString textFilter, PtrList<FileViewModel> & result)
    {
        PtrList<GuaranaFile> gfiles;
        _db->getGuaranaFileManager().getFiles(tagsFilter, textFilter, gfiles);
        Merlin::castList(gfiles, result, _workspace);
    }

private:

    QString _workspace;

};

#endif // WORKSPACE_H
