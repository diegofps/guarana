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

    QString _lasltWorkspaceLocation;
    QStringList _dataFolders;

public:

    ConfigManager()
    {
        qDebug("Settings file is at: %s", getConfigFilename().toLatin1().data());

        if (!loadSettings())
            loadDefaultSettings();
    }

    void loadDefaultSettings()
    {
        _lasltWorkspaceLocation = "";
        _dataFolders.append(getRecommendedDataFolder());
        qDebug("Loaded default settings");
    }

    bool loadSettings()
    {
        try
        {
            QJsonObject settings = JsonHelper::load(getConfigFilename());
            _lasltWorkspaceLocation = settings[DEFAULT_DATA_FOLDER].toString();

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

    void saveSettings()
    {
        QJsonArray jDataFolders;
        JsonHelper::cast(_dataFolders, jDataFolders);

        QJsonObject jSettings;
        jSettings[DEFAULT_DATA_FOLDER] = _lasltWorkspaceLocation;
        jSettings[DATA_FOLDERS] = jDataFolders;

        JsonHelper::save(jSettings, getConfigFilename());
        qDebug("Settings saved");
    }

    bool hasLastWorkspaceLocation() const
    {
        bool hasPath = !_lasltWorkspaceLocation.isEmpty();
        bool exists = QDir().exists(_lasltWorkspaceLocation);
        return hasPath && exists;
    }

    QString & getLastWorkspaceLocation()
    {
        return _lasltWorkspaceLocation;
    }

    void setLastWorkspaceLocation(QString & dataFolder)
    {
        _lasltWorkspaceLocation = dataFolder;
        if (!_dataFolders.contains(dataFolder))
        {
            _dataFolders.append(dataFolder);
            _dataFolders.sort();
        }
    }

    const QStringList & getWorkspaceLocations() const
    {
        return _dataFolders;
    }

    QString getConfigFilename() const
    {
        return EnvHelper::getLocalAppFolder() + "/guarana.settings";
    }

    QString getGlobalActionsDir() const
    {
        return EnvHelper::getLocalAppFolder() + "/actions";
    }

    QString getGlobalTemplatesDir() const
    {
        return EnvHelper::getLocalAppFolder() + "/new";
    }

    QString getRecommendedDataFolder() const
    {
        return EnvHelper::getHomeFolder() + "/Dropbox/Guarana";
    }

};

#endif // CONFIGMANAGER_HPP
