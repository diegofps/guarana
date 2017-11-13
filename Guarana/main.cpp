#include "mainwindow.h"
#include "workspacedialog.h"

#include <QApplication>
#include <QStandardPaths>
#include <QJsonDocument>

#include "helpers/jsonhelper.hpp"
#include "exceptions/guaranaexception.hpp"
#include "dal/configmanager.hpp"

void checkLocation(QStandardPaths::StandardLocation type)
{
    qDebug("Checking location");
    QStringList paths = QStandardPaths::standardLocations(type);
    for (auto s : paths)
        qDebug(s.toLatin1());
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Context context;
    WorkspaceDialog d(context);

    return a.exec();
}
