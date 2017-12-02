#ifndef FILEBUCKET_HPP
#define FILEBUCKET_HPP

#include "ptrlist.hpp"

#include <QString>
#include <QDirIterator>

class FileMap
{
private:

    QString _name;

    QString _path;

    bool _isDir;

    PtrList<FileMap> * _files;

public:

    FileMap(QString name, QString path, bool isDir) :
        _name(name),
        _path(path),
        _isDir(isDir),
        _files(isDir ? new PtrList<FileMap>() : nullptr)
    {

    }

    inline PtrList<FileMap>::const_iterator begin() const
    {
        return _files->begin();
    }

    inline PtrList<FileMap>::const_iterator end() const
    {
        return _files->end();
    }

    ~FileMap()
    {
        if (_files != nullptr)
            delete _files;
    }

    QString & getName()
    {
        return _name;
    }

    QString & getPath()
    {
        return _path;
    }

    bool isDir()
    {
        return _isDir;
    }

    void clear()
    {
        _files->clear();
    }

    void addFolder(QString path)
    {
        QDirIterator it(path);
        while(it.hasNext())
        {
            QString current = it.next();
            QFileInfo info(current);

            if (info.isSymLink() || current.endsWith("/.") || current.endsWith("/.."))
            {
                qDebug() << "Ignoring " << current;
                continue;
            }

            FileMap * child;
            if (info.isDir())
            {
                qDebug() << "Parsing folder " << current;
                child = new FileMap(info.baseName(), current, true);
                child->addFolder(current);
            }
            else
            {
                qDebug() << "Parsing file " << current;
                child = new FileMap(info.baseName(), current, false);
            }

            _files->append(child);
        }

        qSort(_files->begin(), _files->end(), cmpFilesLessThan);
    }

    static bool cmpFilesLessThan(FileMap *& f1, FileMap *& f2)
    {
        if ( (f1->isDir() && f2->isDir()) || (!f1->isDir() && !f2->isDir()))
            return f1->getName() < f2->getName();

        else if (f1->isDir())
            return true;

        else
            return false;

    }

};

#endif // FILEBUCKET_HPP
