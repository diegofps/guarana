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

    void addFolder(QString path, bool allowFolders)
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
                if (info.baseName().startsWith("_"))
                {
                    qDebug() << "Parsing folder as single entity " << current;
                    QString basename = info.baseName();
                    child = new FileMap(basename.mid(1, basename.length()), current, false);
                }
                else
                {
                    qDebug() << "Parsing folder " << current;
                    child = new FileMap(info.fileName(), current, true);
                    child->addFolder(current, allowFolders);
                }
            }
            else
            {
                qDebug() << "Parsing file " << current;
                child = new FileMap(info.fileName(), current, false);
            }

            _files->append(child);
        }

        std::sort(_files->begin(), _files->end(), cmpFilesLessThan);
    }

    static bool cmpFilesLessThan(FileMap *& f1, FileMap *& f2)
    {
        if ( f1->isDir() == f2->isDir())
            return f1->getName() < f2->getName();
        else
            return f1->isDir();

    }

};

#endif // FILEBUCKET_HPP
