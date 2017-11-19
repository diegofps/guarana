#ifndef DBMANAGER_HPP
#define DBMANAGER_HPP

#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlDatabase>
#include "exceptions/guaranaexception.hpp"

class DBManager
{
private:

    QSqlDatabase _db;

private:

    bool exec(QSqlQuery & query)
    {
        if (query.exec())
            return true;

        qDebug(("SQL Error: " + query.lastError().text()).toLatin1());
        return false;
    }

    bool exec(QString strQuery)
    {
        QSqlQuery query;
        query.prepare(strQuery);
        return exec(query);
    }

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
    }

    void createTables()
    {
        exec("CREATE TABLE IF NOT EXISTS People(id INTEGER PRIMARY KEY, name TEXT)");
        exec("CREATE TABLE IF NOT EXISTS __Migrations__(id INTEGER PRIMARY KEY, timestamp INTEGER)");
    }

    void applyPendingMigrations()
    {

    }

    bool addName(QString name)
    {

        QSqlQuery query;
        query.prepare("INSERT INTO People(name) values(:name)");
        query.bindValue(":name", name);
        return exec(query);
    }

    void getNames(QStringList & names)
    {
        names.clear();
        QSqlQuery query("SELECT * FROM People");
        const int id = query.record().indexOf("name");

        while(query.next())
        {
            QString name = query.value(id).toString();
            names.append(name);
        }
    }

};

#endif // DBMANAGER_HPP
