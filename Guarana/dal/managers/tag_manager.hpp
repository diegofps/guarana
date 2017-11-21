#ifndef TAG_MANAGER_HPP
#define TAG_MANAGER_HPP

#include "dal/basemanager.hpp"
#include "dal/models/tag.hpp"

#include <helpers/ptrlist.hpp>

class TagManager : public BaseManager
{
public:

    void save(Tag & tag)
    {
        QSqlQuery query;
        query.prepare("INSERT INTO Tags(name) values(:name)");
        exec(encodeModel(query, tag));
        tag.setId(getLastId());
    }

    void getByName(QString name, Tag & tag)
    {
        QSqlQuery query;
        query.prepare("SELECT id, name FROM Tags WHERE name=:name LIMIT 1");
        query.bindValue(":name", tag.getName());
        exec(query);

        if (query.next())
            decodeModel(query, tag);
    }

    void getAll(PtrList<Tag> tags)
    {
        tags.clear();

        QSqlQuery query;
        query.prepare("SELECT id, name FROM Tags");
        queryMany(query);

        while(query.next())
            tags.append(decodeModel(query));
    }

//    void getNested(const PtrList<Tag> currentTags, PtrList<Tag> availableTags)
//    {
//        availableTags.clear();

//        QSqlQuery query;
//        query.prepare("SELECT id, name FROM Tags");
//        queryMany(query);

//        while(query.next())
//            availableTags.append(decodeModel(query));
//    }

    QSqlQuery & encodeModel(QSqlQuery & query, Tag & model)
    {
        if (model.getId() != 0)
            query.bindValue(":id", model.getId());

        query.bindValue(":name", model.getName());
        return query;
    }

    Tag * decodeModel(QSqlQuery & query)
    {
        Tag * model = new Tag();
        decodeModel(query, *model);
        return model;
    }

    void decodeModel(QSqlQuery & query, Tag & model)
    {
        model.setId(query.value(0).toInt());
        model.setName(query.value(1).toString());
    }
};

#endif // TAG_MANAGER_HPP
