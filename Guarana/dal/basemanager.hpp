#ifndef BASEMANAGER_HPP
#define BASEMANAGER_HPP

#include <QDebug>
#include "QSqlQuery"
#include "exceptions/guaranaexception.hpp"

class BaseManager
{
public:

    void exec(QSqlQuery & query)
    {
        if (!query.exec())
            throw GuaranaException("SQL Error: " + query.lastError().text());
    }

    void exec(QString strQuery)
    {
        QSqlQuery query;
        query.prepare(strQuery);
        exec(query);
    }

    QVariant queryOne(QSqlQuery & query)
    {
        exec(query);

        if (!query.next())
            throw GuaranaException("Query returned nothing");

        return query.value(0);
    }

    void queryMany(QSqlQuery & query)
    {
        exec(query);

        if (!query.next())
            throw GuaranaException("Query returned nothing");
    }

};

#endif // BASEMANAGER_HPP
