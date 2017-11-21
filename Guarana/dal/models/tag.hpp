#ifndef TAG_HPP
#define TAG_HPP

#include "QString"

class Tag
{
private:

    long _id;

    QString _name;

public:

    Tag()
    {

    }

    Tag(QString name) :
        _name(name)
    {

    }

    long getId() const
    {
        return _id;
    }

    QString getName() const
    {
        return _name;
    }

    void setId(const long id)
    {
        _id = id;
    }

    void setName(const QString name)
    {
        _name = name;
    }

};

#endif // TAG_HPP
