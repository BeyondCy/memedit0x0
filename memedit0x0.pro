#-------------------------------------------------
#
# Project created by QtCreator 2012-04-21T10:16:40
#
#-------------------------------------------------

QT       += core gui

TARGET = memedit0x0
TEMPLATE = app

LIBS += "C:\Program Files\Microsoft SDKs\Windows\v6.0A\Lib\shell32.Lib" \
        "C:\Program Files\Microsoft SDKs\Windows\v6.0A\Lib\User32.Lib"
INCLUDEPATH += "C:\Program Files\Microsoft SDKs\Windows\v6.0A\Lib\Include"

SOURCES += main.cpp\
        mainwindow.cpp \
    scantabwidget.cpp \
    processlistwidget.cpp \
    ProcessList.cpp \
    MemoryScanner.cpp \
    MemoryCell.cpp \
    mainwindow.cpp \
    main.cpp

HEADERS  += mainwindow.h \
    scantabwidget.h \
    processlistwidget.h \
    ProcessList.h \
    MemoryScanner.h \
    MemoryCell.h \
    mainwindow.h

FORMS    += mainwindow.ui \
    mainwindow.ui

OTHER_FILES += \
    memedit0x0.pro.user \
    memedit0x0.pro

RESOURCES += \
    icons.qrc \
    icons.qrc
