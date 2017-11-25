#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include "comm/local/localbroadcast.hpp"
#include "dal/configmanager.hpp"
#include "dal/workspace.hpp"

class Context
{
private:

    LocalBroadcast _localBroadcast;

    ConfigManager _configManager;

    Workspace _workspace;

public:

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

};

#endif // CONTEXT_HPP
