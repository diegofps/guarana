#ifndef RANDOMHELPER_HPP
#define RANDOMHELPER_HPP

#include <QUuid>

class RandomHelper
{
public:

    static QString createGuid()
    {
        return QUuid::createUuid().toString().mid(1, 36).toUpper();
    }

};

#endif // RANDOMHELPER_HPP
