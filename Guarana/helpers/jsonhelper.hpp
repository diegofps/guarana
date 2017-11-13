#ifndef JSONHELPER_HPP
#define JSONHELPER_HPP

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>
#include <QFile>

#include "exceptions/guaranaexception.hpp"

namespace JsonHelper
{
    inline void save(QJsonObject & obj, QString filepath)
    {
        QFile loadFile(filepath);

        if (!loadFile.open(QIODevice::WriteOnly))
            throw GuaranaException("Could not write to the json file: " + filepath);

        QJsonDocument saveDoc(obj);
        loadFile.write(saveDoc.toJson());
    }

    inline QJsonObject load(QString filepath)
    {
        QFile loadFile(filepath);

        if (!loadFile.open(QIODevice::ReadOnly))
            throw GuaranaException("Could not read json file: " + filepath);

        return QJsonDocument::fromJson(loadFile.readAll()).object();
    }

    inline void cast(QJsonArray & jsonArray, QStringList & stringList)
    {
        for (QJsonValueRef jDataFolderRef : jsonArray)
            if (jDataFolderRef.isString())
                stringList.append(jDataFolderRef.toString());
    }

    inline void cast(QStringList & stringList, QJsonArray & jsonArray)
    {
        for (auto & dataPath : stringList)
            jsonArray.append(dataPath);
    }

}

#endif // JSONHELPER_HPP
