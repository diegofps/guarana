#ifndef GUARANA_EXCEPTION_HPP
#define GUARANA_EXCEPTION_HPP

#include <QString>

class GuaranaException : public std::exception
{
private:

    QString _msg;

public:

    GuaranaException() : _msg("Unspecified")
    {

    }

    GuaranaException(const QString & str) : _msg(str.toLatin1())
    {

    }

    ~GuaranaException() throw()
    {

    }

    const char * what() const throw()
    {
        return _msg.toLatin1();
    }

};

#endif
