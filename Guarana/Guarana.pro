#-------------------------------------------------
#
# Project created by QtCreator 2017-11-11T19:12:26
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Guarana
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    main.cpp \
    mainwindow.cpp \
    workspacedialog.cpp \
    navigationform.cpp \
    favoritesform.cpp \
    historyform.cpp \
    tagsform.cpp \
    thrashform.cpp \
    settingsform.cpp \
    navigationtab.cpp \
    navigationform2.cpp

HEADERS += \
    mainwindow.h \
    helpers/jsonhelper.hpp \
    exceptions/guaranaexception.hpp \
    dal/configmanager.hpp \
    helpers/envhelper.hpp \
    workspacedialog.h \
    navigationform.h \
    favoritesform.h \
    historyform.h \
    tagsform.h \
    thrashform.h \
    settingsform.h \
    navigationtab.h \
    navigationform2.h \
    helpers/context.hpp \
    comm/local/localbroadcast.hpp \
    dal/managers/tag_manager.hpp \
    dal/managers/guaranafile_manager.hpp \
    dal/models/guaranafile.hpp \
    dal/models/tag.hpp \
    dal/managers/_guaranafile_tag_manager.hpp \
    dal/models/_guaranafile_tag.hpp \
    dal/workspace.hpp \
    dal/basemanager.hpp \
    dal/dbmanager.hpp \
    viewmodels/fileviewmodel.hpp \
    helpers/merlin.hpp \
    helpers/datehelper.hpp \
    helpers/ioutils.hpp \
    helpers/ptrlist.hpp \
    widgetmodels/filetablemodel.hpp \
    helpers/randomhelper.hpp

FORMS += \
    mainwindow.ui \
    workspacedialog.ui \
    navigationform.ui \
    favoritesform.ui \
    historyform.ui \
    tagsform.ui \
    thrashform.ui \
    settingsform.ui \
    navigationtab.ui \
    navigationform2.ui

RESOURCES += \
    resources.qrc
