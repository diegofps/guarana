#ifndef PTRLIST_HPP
#define PTRLIST_HPP

#include <QList>

template <typename T>
class PtrList : public QList<T*>
{
public:

    ~PtrList()
    {
        for (auto ptr : *this)
            delete ptr;
    }

    void clear()
    {
        for (auto ptr : *this)
            delete ptr;

        QList<T*>::clear();
    }

};

#endif // PTRLIST_HPP
