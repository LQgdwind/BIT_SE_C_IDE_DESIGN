#-------------------------------------------------
#
# Project created by QtCreator 2022-08-16T16:03:23
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QEditor
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
    emenu.cpp \
    esidebar.cpp \
    editor.cpp \
    explorer.cpp \
    efilebar.cpp \
    efileinfo.cpp \
    efilelabel.cpp \
    eoutput.cpp \
    build.cpp \
    ecodeedit.cpp \
    completelistwidget.cpp \
    highlighter.cpp \
    finddialog.cpp \
    replacedialog.cpp \
    etheme.cpp \
    debugger.cpp \
    debuggerpage.cpp \
    gdbresultparser.cpp

HEADERS += \
        mainwindow.h \
    emenu.h \
    esidebar.h \
    editor.h \
    explorer.h \
    efilebar.h \
    efileinfo.h \
    helper.h \
    efilelabel.h \
    eoutput.h \
    build.h \
    ecodeedit.h \
    completelistwidget.h \
    highlighter.h \
    finddialog.h \
    replacedialog.h \
    etheme.h \
    debugger.h \
    debuggerpage.h \
    gdbresultparser.h

FORMS += \
        mainwindow.ui \
    debuggerpage.ui

RESOURCES += \
    res.qrc \
    res.qrc
RC_ICONS = logo.ico
