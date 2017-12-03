#ifndef FILEVIEWMODEL_HPP
#define FILEVIEWMODEL_HPP

#include <QString>

class FileViewModel
{
private:

    int _guaranaFileId;

    QString _filename;

    QString _size;

    QString _modifDate;

    QString _creatDate;

    QString _readDate;

    bool _isDir;

public:

    int getGuaranaFileId() const
    {
        return _guaranaFileId;
    }

    QString getFilename() const
    {
        return _filename;
    }

    QString getSize() const
    {
        return _size;
    }

    QString getModificationDate() const
    {
        return _modifDate;
    }

    QString getReadingDate() const
    {
        return _readDate;
    }

    QString getCreationDate() const
    {
        return _creatDate;
    }

    bool isDir()
    {
        return _isDir;
    }

    void setGuaranaFileid(const int guaranaFileId)
    {
        _guaranaFileId = guaranaFileId;
    }

    void setFilename(const QString & filename)
    {
        _filename = filename;
    }

    void setSize(const QString & size)
    {
        _size = size;
    }

    void setModificationDate(const QString & modifDate)
    {
        _modifDate = modifDate;
    }

    void setReadingDate(const QString & readDate)
    {
        _readDate = readDate;
    }

    void setCreationDate(const QString & creatDate)
    {
        _creatDate = creatDate;
    }

    void setIsDir(const bool isDir)
    {
        _isDir = isDir;
    }

};

#endif // FILEVIEWMODEL_HPP
