#ifndef DBMANAGER_HPP
#define DBMANAGER_HPP

#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlDatabase>

#include "dal/basemanager.hpp"
#include "exceptions/guaranaexception.hpp"

#include "dal/models/guaranafile.hpp"
#include "dal/models/tag.hpp"
#include "dal/models/_guaranafile_tag.hpp"

#include "dal/managers/guaranafile_manager.hpp"
#include "dal/managers/tag_manager.hpp"
#include "dal/managers/_guaranafile_tag_manager.hpp"

class DBManager : public BaseManager
{
private:

    QSqlDatabase _db;

    GuaranaFileManager _GuaranaFileManager;

    TagManager _TagManager;

    _GuaranaFile_Tag_Manager __GuaranaFile_Tag_Manager;

public:

    DBManager(const QString & path)
    {
        _db = QSqlDatabase::addDatabase("QSQLITE");
        _db.setDatabaseName(path);

        if (!_db.open())
            throw GuaranaException();
        else
            qDebug("Database opened");

        createTables();
        applyPendingMigrations();
        seed();
    }

    ~DBManager()
    {
        _db.close();
    }

    void createTables()
    {
        //exec("CREATE TABLE IF NOT EXISTS People(id INTEGER PRIMARY KEY, name TEXT)");

        exec("CREATE TABLE IF NOT EXISTS Tags(id INTEGER PRIMARY KEY, name TEXT)");
        exec("CREATE TABLE IF NOT EXISTS GuaranaFiles(id INTEGER PRIMARY KEY, filename TEXT, uuid TEXT, isAlive INTEGER, removedDate INTEGER)");
        exec("CREATE TABLE IF NOT EXISTS _GuaranaFile_Tag(id INTEGER PRIMARY KEY, guaranaFileId INTEGER, tagId INTEGER)");

        exec("CREATE TABLE IF NOT EXISTS __Migrations__(id INTEGER PRIMARY KEY, timestamp INTEGER)");
    }

    void applyPendingMigrations()
    {

    }

    void seed()
    {

    }

    GuaranaFileManager & getGuaranaFileManager()
    {
        return _GuaranaFileManager;
    }

    TagManager & getTagManager()
    {
        return _TagManager;
    }

    _GuaranaFile_Tag_Manager & get_GuaranaFile_Tag_Manager()
    {
        return __GuaranaFile_Tag_Manager;
    }

//    bool addName(QString name)
//    {
//        QSqlQuery query;
//        query.prepare("INSERT INTO People(name) values(:name)");
//        query.bindValue(":name", name);
//        return exec(query);
//    }

//    void getNames(QStringList & names)
//    {
//        names.clear();
//        QSqlQuery query("SELECT * FROM People");
//        const int id = query.record().indexOf("name");

//        while(query.next())
//        {
//            QString name = query.value(id).toString();
//            names.append(name);
//        }
//    }

};

#endif // DBMANAGER_HPP
