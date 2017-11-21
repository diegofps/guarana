#ifndef GUARANAFILE_HPP
#define GUARANAFILE_HPP

#include "QString"
#include "QUuid"

class GuaranaFile
{
private:

    int _id;

    QString _filename;

    QString _uuid;

public:

    GuaranaFile()
    {

    }

    GuaranaFile(const QString filename, const QString uuid) :
        _id(0),
        _filename(filename),
        _uuid(uuid)
    {

    }

    int getId() const
    {
        return _id;
    }

    QString getFilename() const
    {
        return _filename;
    }

    QString getUuid() const
    {
        return _uuid;
    }

    void setId(const int id)
    {
        _id = id;
    }

    void setFilename(const QString filename)
    {
        _filename = filename;
    }

    void setUuid(const QString uuid)
    {
        _uuid = uuid;
    }

};

#endif /* GUARANAFILE_HPP */
