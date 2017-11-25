#ifndef DATEHELPER_HPP
#define DATEHELPER_HPP

#include <QDateTime>
#include <QString>


class DateHelper
{
public:

    static QString formatDateTime(QDateTime date)
    {
        return date.toString("yy/MM/dd HH:mm");
    }

};

#endif // DATEHELPER_HPP
