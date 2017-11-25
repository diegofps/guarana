#ifndef PTRLIST_HPP
#define PTRLIST_HPP

#include <QList>

template <typename T>
class PtrList : public QList<T*>
{
private:

    bool _ownsData;

public:

    PtrList(bool ownsData = true) :
        _ownsData(ownsData)
    {

    }

    ~PtrList()
    {
        deleteElements();
    }

    void clear()
    {
        deleteElements();
        QList<T*>::clear();
    }

private:

    void deleteElements()
    {
        if (_ownsData)
            for (auto ptr : *this)
                delete ptr;
    }

};

#endif // PTRLIST_HPP