#ifndef FILEMANAGER_HPP
#define FILEMANAGER_HPP

#include <QVariant>
#include <dal/models/tag.hpp>
#include <helpers/ptrlist.hpp>
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

    void getFiles(PtrList<Tag> & tagsFilter, QString textFilter, PtrList<GuaranaFile> & gfiles)
    {
        gfiles.clear();

        QString whereTags;
        if (!tagsFilter.isEmpty())
        {
            whereTags += "tagId IN (";
            whereTags += tagsFilter.at(0)->getId();

            for (auto tag : tagsFilter)
            {
                whereTags += ", ";
                whereTags += tag->getId();
            }

            whereTags += ")";
        }

        QString whereText;
        if (!whereText.isEmpty())
        {
            whereText += "name LIKE '%";
            whereText += textFilter;
            whereText += "%'";
        }

        QSqlQuery query("SELECT id, filename, uuid FROM GuaranaFiles");
        queryMany(query);

        while(query.next()) {
            gfiles.append(decodeModel(query));
        }

//        QSqlQuery query;
//        query.prepare("SELECT ");

    }

    QSqlQuery & encodeModel(QSqlQuery & query, GuaranaFile & gfile)
    {
        if (gfile.getId() != 0)
            query.bindValue(":id", gfile.getId());

        query.bindValue(":filename", gfile.getFilename());
        query.bindValue(":uuid", gfile.getUuid());
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
