#ifndef FILEMANAGER_HPP
#define FILEMANAGER_HPP

#include <QVariant>
#include <dal/models/tag.hpp>
#include <helpers/merlin.hpp>
#include <helpers/ptrlist.hpp>
#include <viewmodels/fileviewmodel.hpp>
#include "dal/basemanager.hpp"
#include "dal/models/guaranafile.hpp"

class GuaranaFileManager : public BaseManager
{
public:

    void save(GuaranaFile & gfile)
    {
        QSqlQuery query;
        query.prepare("INSERT INTO GuaranaFiles(filename, uuid) values(:filename, :uuid)");
        exec(encodeModel(query, gfile));

        QSqlQuery query2("select last_insert_rowid()");
        int id = queryOne(query2).toInt();

        qDebug("Inserted id: %d", id);
        gfile.setId(id);
    }

    void filter(PtrList<Tag> & tagsFilter, QString textFilter, PtrList<GuaranaFile> & gfiles)
    {
        gfiles.clear();

        QStringList wheres;

        for (Tag * tag : tagsFilter)
            wheres.append(QString("EXISTS (SELECT ft.id FROM _guaranafile_tag ft WHERE tagId=%1 AND guaranaFileId=f.id)").arg(tag->getId()));

        if (!textFilter.isEmpty())
            wheres.append(QString("filename LIKE '%%1%'").arg(textFilter));


        QSqlQuery query;
        if (wheres.isEmpty())
            query.prepare("SELECT f.id, f.filename, f.uuid FROM GuaranaFiles f");
        else
            query.prepare("SELECT f.id, f.filename, f.uuid FROM GuaranaFiles f WHERE " + wheres.join(" AND "));

        qDebug() << "Query:" << query.lastQuery();

        queryMany(query);
        while(query.next())
            gfiles.append(decodeModel(query));
    }

    QSqlQuery & encodeModel(QSqlQuery & query, GuaranaFile & model)
    {
        if (model.getId() != 0)
            query.bindValue(":id", model.getId());

        query.bindValue(":filename", model.getFilename());
        query.bindValue(":uuid", model.getUuid());
        return query;
    }

    GuaranaFile * decodeModel(QSqlQuery & query)
    {
        GuaranaFile * model = new GuaranaFile();
        model->setId(query.value(0).toInt());
        model->setFilename(query.value(1).toString());
        model->setUuid(query.value(2).toString());
        return model;
    }

};

#endif // FILEMANAGER_HPP
