#ifndef ENVIRONMENTHELPER_HPP
#define ENVIRONMENTHELPER_HPP

#include <QString>
#include <QStandardPaths>
#include <QCoreApplication>
#include <QFileInfo>
#include <QDir>

#include "exceptions/guaranaexception.hpp"

namespace EnvHelper
{
    inline QString getAppName()
    {
         return QFileInfo(QCoreApplication::applicationFilePath()).baseName();
    }

    inline QString getLocalAppFolder()
    {
        QStringList filenames1 = QStandardPaths::standardLocations(QStandardPaths::AppLocalDataLocation);
        if (!filenames1.isEmpty())
        {
            QDir().mkpath(filenames1[0]);
            return filenames1[0];
        }

        QStringList homes = QStandardPaths::standardLocations(QStandardPaths::HomeLocation);
        if (!homes.isEmpty())
        {
            QDir().mkpath(homes[0]);
            return homes[0];
        }

        throw GuaranaException("Could not find a good local app folder");
    }

    inline QString getHomeFolder()
    {
        QStringList homes = QStandardPaths::standardLocations(QStandardPaths::HomeLocation);
        if (!homes.isEmpty())
        {
            QDir().mkpath(homes[0]);
            return homes[0];
        }

        throw GuaranaException("Could not find home folder");
    }

}

#endif // ENVIRONMENTHELPER_HPP
