#ifndef GUARANAFILE_TAG_MANAGER_HPP
#define GUARANAFILE_TAG_MANAGER_HPP

#include "dal/basemanager.hpp"
#include "dal/models/_guaranafile_tag.hpp"

class _GuaranaFile_Tag_Manager : public BaseManager
{
public:

    void save(_GuaranaFile_Tag & model)
    {
        QSqlQuery query;
        query.prepare("INSERT INTO _GuaranaFile_Tag(tagId, guaranaFileId) values(:tagId, :guaranaFileId)");
        exec(encodeModel(query, model));
        model.setId(getLastId());
    }

    QSqlQuery & encodeModel(QSqlQuery & query, _GuaranaFile_Tag & model)
    {
        if (model.getId() != 0)
            query.bindValue(":id", model.getId());

        query.bindValue(":tagId", model.getTagId());
        query.bindValue(":guaranaFileId", model.getGuaranaFileId());
        return query;
    }

    _GuaranaFile_Tag * decodeModel(QSqlQuery & query)
    {
        _GuaranaFile_Tag * model = new _GuaranaFile_Tag();
        model->setId(query.value(0).toInt());
        model->setTagId(query.value(1).toInt());
        model->setGuaranaFileId(query.value(2).toInt());
        return model;
    }

};

#endif // GUARANAFILE_TAG_MANAGER_HPP
