#ifndef IOUTILS_HPP
#define IOUTILS_HPP

#include <QDirIterator>
#include <QFileInfo>
#include <QString>

class IOUtils
{
public:

    static void copyFile(QString src, QString dst)
    {
        qDebug() << "Copying file from '" << src << "' to '" << dst << "'";
        QFile::copy(src, dst);
    }

    static void copyDir(QString src, QString dst)
    {
        QDir tmp;
        tmp.mkpath(dst);

        QDirIterator it(src);
        while(it.hasNext())
        {
            QString current = it.next();
            QFileInfo info(current);

            if (current.endsWith("/..") || current.endsWith("/."))
                continue;

            if (info.isSymLink())
                continue;

            if (info.isDir())
                copyDir(current, dst + "/" + info.fileName());

            else
                copyFile(current, dst + "/" + info.fileName());
        }
    }

    static QString getReadableSize(long bytes)
    {
        long threshold = 1024;
        if (bytes < threshold)
            return QString("%1B").arg(bytes);

        threshold *= 1024;
        if (bytes < threshold)
            return QString("%1KB").arg(bytes * 1024 / threshold);

        threshold *= 1024;
        if (bytes < threshold)
            return QString("%1MB").arg(bytes * 1024 / threshold);

        threshold *= 1024;
        if (bytes < threshold)
            return QString("%1GB").arg(bytes * 1024 / threshold);

        return QString("%1TB").arg(bytes * 1024 / threshold);
    }

};

#endif // IOUTILS_HPP
