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

    void removeAt(int i)
    {
        if (_ownsData)
            delete this->at(i);
        QList<T*>::removeAt(i);
    }

    void sort()
    {
        std::sort(this->begin(), this->end(), [](T * p1, T * p2) {
            return *p1 < *p2;
        });
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
