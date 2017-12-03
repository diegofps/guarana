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

    const QString SELECT_FIELDS = "id, filename, uuid, isAlive, removedDate";
    const QString INSERT_FIELDS = "filename, uuid, isAlive, removedDate";
    const QString INSERT_VALUES = ":filename, :uuid, :isAlive, :removedDate";
    const QString UPDATE_FIELDS = "filename=:filename, uuid=:uuid, isAlive=:isAlive, removedDate=:removedDate";

public:

    void save(GuaranaFile & gfile)
    {
        QSqlQuery query;
        query.prepare("INSERT INTO GuaranaFiles(" + INSERT_FIELDS + ") values(" + INSERT_VALUES + ")");
        exec(encodeModel(query, gfile));

        QSqlQuery query2("select last_insert_rowid()");
        int id = queryOne(query2).toInt();

        qDebug("Inserted id: %d", id);
        gfile.setId(id);
    }

    void update(GuaranaFile & file)
    {
        QSqlQuery query;
        query.prepare("UPDATE GuaranaFiles SET " + UPDATE_FIELDS + " WHERE id=:id");
        exec(encodeModel(query, file));
    }

    void getById(int fileId, GuaranaFile & file)
    {
        QSqlQuery query;
        query.prepare("SELECT " + SELECT_FIELDS + " FROM GuaranaFiles WHERE id=:id");
        query.bindValue(":id", fileId);

        exec(query);
        if (query.next())
            decodeModel(query, file);
    }

    void filter(PtrList<Tag> & tagsFilter, QString textFilter, PtrList<GuaranaFile> & gfiles, bool isAlive)
    {
        gfiles.clear();

        QStringList wheres;

        wheres.append(QString("isAlive=%1").arg(isAlive?1:0));

        for (Tag * tag : tagsFilter)
            wheres.append(QString("EXISTS (SELECT ft.id FROM _guaranafile_tag ft WHERE tagId=%1 AND guaranaFileId=f.id)").arg(tag->getId()));

        if (!textFilter.isEmpty())
            wheres.append(QString("filename LIKE '%%1%'").arg(textFilter));


        QSqlQuery query;
        if (wheres.isEmpty())
            query.prepare("SELECT " + SELECT_FIELDS + " FROM GuaranaFiles f");
        else
            query.prepare("SELECT " + SELECT_FIELDS + " FROM GuaranaFiles f WHERE " + wheres.join(" AND "));

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
        query.bindValue(":isAlive", model.isAlive());
        query.bindValue(":removedDate", model.getRemovedDate());
        return query;
    }

    GuaranaFile * decodeModel(QSqlQuery & query)
    {
        GuaranaFile * model = new GuaranaFile();
        decodeModel(query, *model);
        return model;
    }

    void decodeModel(QSqlQuery & query, GuaranaFile & model)
    {
        auto timestamp = query.value(4).toUInt();
        QDateTime removedDate = QDateTime::fromTime_t(timestamp);

        model.setId(query.value(0).toInt());
        model.setFilename(query.value(1).toString());
        model.setUuid(query.value(2).toString());
        model.setIsAlive(query.value(3).toBool());
        model.setRemovedDate(removedDate);
    }

};

#endif // FILEMANAGER_HPP
