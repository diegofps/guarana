#ifndef LOCALBROADCAST_HPP
#define LOCALBROADCAST_HPP

#include <QList>

#include <exceptions/guaranaexception.hpp>

class PagesEndedListener
{
public:
    virtual void onPageEnded() = 0;
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

class Bag
{
private:

    QMap<QString, QVariant> _content;

public:

    template <typename T>
    void put(QString & key, T & value)
    {
        _content[key] = value;
    }

    QVariant & get(QString & key)
    {
        if (!_content.contains(key))
            throw GuaranaException("Missing parameter: " + key);
        return _content[key];
    }

};

class BroadcastListener
{
public:
    virtual void onReceive(Bag & bag) = 0;
};

class LocalBroadcast
{
private:

    QList<PagesEndedListener*> _pagesEndedListeners;

    QList<NavTabChangedListener*> _navTabChangedListeners;

    QMap<QString, QList<BroadcastListener*>*> _listeners;

public:

    void registerListener(QString & eventName, BroadcastListener * listener)
    {
        if (!_listeners.contains(eventName))
            _listeners[eventName] = new QList<BroadcastListener*>();
        _listeners[eventName]->append(listener);
    }

    void unregisterListener(QString & eventName, BroadcastListener * listener)
    {
        if (_listeners.contains(eventName))
            _listeners[eventName]->removeAll(listener);
    }

    void sendEvent(QString & eventName, Bag & bag)
    {
        if (_listeners.contains(eventName))
            for (BroadcastListener * listener : *_listeners[eventName])
                listener->onReceive(bag);
    }

    void registerPageEndedListener(PagesEndedListener * listener)
    {
        _pagesEndedListeners.append(listener);
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

    void sendNavTabChanged(const NavTabChangedListener::NavTabChangedEvent & event)
    {
        for (auto listener : _navTabChangedListeners)
            listener->onTabChanged(event);
    }

};

#endif
