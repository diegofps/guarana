#ifndef TAG_HPP
#define TAG_HPP

#include "QString"

class Tag
{
private:

    int _id;

    QString _name;

public:

    Tag() : _id(0)
    {

    }

    Tag(QString name) :
        _id(0),
        _name(name)
    {

    }

    int getId() const
    {
        return _id;
    }

    QString getName() const
    {
        return _name;
    }

    void setId(const int id)
    {
        _id = id;
    }

    void setName(const QString name)
    {
        _name = name;
    }

};

#endif // TAG_HPP
