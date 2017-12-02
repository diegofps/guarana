#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include "comm/local/localbroadcast.hpp"
#include "dal/configmanager.hpp"
#include "dal/workspace.hpp"
#include "filemap.hpp"

class Context
{
private:

    LocalBroadcast _localBroadcast;

    ConfigManager _configManager;

    Workspace _workspace;

    FileMap _actions;

    FileMap _templates;

public:

    Context() :
        _actions("Transform", "", true),
        _templates("New", "", true)
    {
        QDir tmp;
        tmp.mkpath(_configManager.getGlobalActionsDir());
        tmp.mkpath(_configManager.getGlobalTemplatesDir());
    }

    LocalBroadcast & getLocalBroadcast()
    {
        return _localBroadcast;
    }

    ConfigManager & getConfigManager()
    {
        return _configManager;
    }

    Workspace & getWorkspace()
    {
        return _workspace;
    }

    FileMap & getActions()
    {
        return _actions;
    }

    FileMap & getTemplates()
    {
        return _templates;
    }

    void openWorkspace(QString path)
    {
        _configManager.setLastWorkspaceLocation(path);
        _workspace.setWorkspaceLocation(path);
        _templates.clear();
        _actions.clear();

        _actions.addFolder(_configManager.getGlobalActionsDir());
        _actions.addFolder(_workspace.getWorkspaceActionsDir());

        _templates.addFolder(_configManager.getGlobalTemplatesDir());
        _templates.addFolder(_workspace.getWorkspaceTemplatesDir());
    }

};

#endif // CONTEXT_HPP
