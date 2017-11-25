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

class NavTabChangedListener
{
public:

    class NavTabChangedEvent
    {
    public:
        QString newName;
    };

    virtual void onTabChanged(const NavTabChangedEvent & event) = 0;
};

class LocalBroadcast
{
private:

    QList<PagesEndedListener*> _pagesEndedListeners;

    QList<WorkspaceReadyListener*> _workspaceReadyListeners;

    QList<NavTabChangedListener*> _navTabChangedListeners;

public:

    void registerPageEndedListener(PagesEndedListener * listener)
    {
        _pagesEndedListeners.append(listener);
    }

    void registerWorkspaceReadyListener(WorkspaceReadyListener * listener)
    {
        _workspaceReadyListeners.append(listener);
    }

    void registerNavTabChangedListener(NavTabChangedListener * listener)
    {
        _navTabChangedListeners.append(listener);
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

    void sendNavTabChanged(const NavTabChangedListener::NavTabChangedEvent & event)
    {
        for (auto listener : _navTabChangedListeners)
            listener->onTabChanged(event);
    }

};

#endif
