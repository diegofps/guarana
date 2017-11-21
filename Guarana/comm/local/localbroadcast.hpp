#ifndef LOCALBROADCAST_HPP
#define LOCALBROADCAST_HPP

#include <QList>

class PagesEndedListener
{
public:
    virtual void onPageEnded() = 0;
};

class WorkspaceReadyListener
{
public:
    virtual void onWorkspaceReady() = 0;
};

class LocalBroadcast
{
private:

    QList<PagesEndedListener*> _pagesEndedListeners;

    QList<WorkspaceReadyListener*> _workspaceReadyListeners;

public:

    void registerPageEndedListener(PagesEndedListener * listener)
    {
        _pagesEndedListeners.append(listener);
    }

    void registerWorkspaceReadyListener(WorkspaceReadyListener * listener)
    {
        _workspaceReadyListeners.append(listener);
    }

    void sendPagesEnded()
    {
        for (auto listener : _pagesEndedListeners)
            listener->onPageEnded();
    }

    void sendWorkspaceReady()
    {
        for (auto listener : _workspaceReadyListeners)
            listener->onWorkspaceReady();
    }

};

#endif
