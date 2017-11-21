#ifndef IOUTILS_HPP
#define IOUTILS_HPP

#include <QString>

class IOUtils
{
public:

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
