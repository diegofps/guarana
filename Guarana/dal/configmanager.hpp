#ifndef CONFIGMANAGER_HPP
#define CONFIGMANAGER_HPP

#include <QString>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValueRef>

#include "helpers/jsonhelper.hpp"
#include "helpers/envhelper.hpp"

class ConfigManager
{
private:

    const char * const DEFAULT_DATA_FOLDER = "defaultDataFolder";
    const char * const DATA_FOLDER_PATH = "dataFolderPath";
    const char * const DATA_FOLDERS = "dataFolders";

    QString _defaultDataFolder;
    QStringList _dataFolders;

    QString getConfigFilename() const
    {
        return EnvHelper::getLocalAppFolder() + "/guarana.settings";
    }

    QString getRecommendedDataFolder() const
    {
        return EnvHelper::getHomeFolder() + "/Dropbox/Guarana";
    }

public:

    ConfigManager()
    {
        qDebug("Settings file is at: %s", getConfigFilename().toLatin1().data());
        if (!load())
            loadDefault();
    }

    void loadDefault()
    {
        _defaultDataFolder = "";
        _dataFolders.append(getRecommendedDataFolder());
        qDebug("Loaded default settings");
    }

    bool load()
    {
        try
        {
            QJsonObject settings = JsonHelper::load(getConfigFilename());
            _defaultDataFolder = settings[DEFAULT_DATA_FOLDER].toString();

            QJsonArray jDataFolders = settings[DATA_FOLDERS].toArray();
            JsonHelper::cast(jDataFolders, _dataFolders);

            if (_dataFolders.isEmpty())
                _dataFolders.append(getRecommendedDataFolder());

            qDebug("Settings file loaded");
            return true;
        }
        catch(GuaranaException &e)
        {
            qDebug("Could not load settings from the settings file");
            return false;
        }
    }

    void save()
    {
        QJsonArray jDataFolders;
        JsonHelper::cast(_dataFolders, jDataFolders);

        QJsonObject jSettings;
        jSettings[DEFAULT_DATA_FOLDER] = _defaultDataFolder;
        jSettings[DATA_FOLDERS] = jDataFolders;

        JsonHelper::save(jSettings, getConfigFilename());
        qDebug("Settings saved");
    }

    bool hasDefaultDataFolder() const
    {
        bool hasPath = !_defaultDataFolder.isEmpty();
        bool exists = QDir().exists(_defaultDataFolder);
        return hasPath && exists;
    }

    QString & getDefaultDataFolder()
    {
        return _defaultDataFolder;
    }

    void setDefaultDataFolder(QString & dataFolder)
    {
        _defaultDataFolder = dataFolder;
        if (!_dataFolders.contains(dataFolder))
        {
            _dataFolders.append(dataFolder);
            _dataFolders.sort();
        }
    }

    const QStringList & getDataFolders() const
    {
        return _dataFolders;
    }

};

#endif // CONFIGMANAGER_HPP
