#ifndef LOCALBROADCAST_HPP
#define LOCALBROADCAST_HPP

#include <QList>

class PagesEndedListener
{
public:
    virtual void onPageEnded() = 0;
};

class LocalBroadcast
{
private:

    QList<PagesEndedListener*> _pagesEndedListeners;

public:

    void registerPageEndedListener(PagesEndedListener * listener)
    {
        _pagesEndedListeners.append(listener);
    }

    void sendPagesEnded()
    {
        for (auto listener : _pagesEndedListeners)
            listener->onPageEnded();
    }

};

#endif
