#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include "comm/local/localbroadcast.hpp"
#include "dal/configmanager.hpp"

class Context
{
private:

    LocalBroadcast _localBroadcast;

    ConfigManager _configManager;

public:

    LocalBroadcast & getLocalBroadcast()
    {
        return _localBroadcast;
    }

    ConfigManager & getConfigManager()
    {
        return _configManager;
    }

};

#endif // CONTEXT_HPP
