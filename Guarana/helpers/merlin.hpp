#ifndef MERLIN_HPP
#define MERLIN_HPP

#include <QList>
#include <dal/workspace.hpp>
#include <viewmodels/fileviewmodel.hpp>
#include "dal/models/guaranafile.hpp"
#include "datehelper.hpp"
#include "ioutils.hpp"

class Merlin
{
public:

    static FileViewModel & cast(GuaranaFile & data, FileViewModel & model, QString workspace)
    {
        QString filepath = workspace + "/files/" + data.getUuid() + "/" + data.getFilename();

        QFileInfo fi(filepath);
        QString dateCreated = DateHelper::formatDateTime(fi.created());
        QString lastRead = DateHelper::formatDateTime(fi.lastRead());
        QString lastModification = DateHelper::formatDateTime(fi.lastModified());
        QString size = IOUtils::getReadableSize(fi.size());

        model.setFilename(data.getFilename());
        model.setGuaranaFileid(data.getId());
        model.setSize(size);
        model.setCreationDate(dateCreated);
        model.setModificationDate(lastModification);
        model.setReadingDate(lastRead);

        return model;
    }

    template <typename T1, typename T2, typename ... ARGS>
    static PtrList<T2> & castList(PtrList<T1> & src, PtrList<T2> & dst, ARGS & ... args)
    {
        dst.clear();

        for (T1 * t1 : src)
        {
            T2 * t2 = new T2();
            Merlin::cast(*t1, *t2, args...);
            dst.append(t2);
        }

        return dst;
    }

};

#endif // MERLIN_HPP
