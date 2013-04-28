#-------------------------------------------------
#
# Project created by QtCreator 2013-04-05T22:14:31
#
#-------------------------------------------------

QT       += core gui

QMAKE_CXXFLAGS += -std=c++0x

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = atomic-weights
TEMPLATE = app


SOURCES += main.cpp\
        Windows\mainwindow.cpp \
        Windows\aboutwindow.cpp \
        Widgets\calculationwizard.cpp \
        Widgets\wizardsettingspage.cpp \
        Widgets\wizardipsearchpage.cpp \
        Widgets\calculationresults.cpp \
        Widgets\calculationinfo.cpp \
        Widgets\welcomeinfo.cpp \
        IO\writeresults.cpp \
        Core\calculationscore.cpp \
        Core\mtrandom.cpp \
        Core\math.cpp \


HEADERS  += Windows\mainwindow.h \
         Windows\aboutwindow.h \
         Widgets\calculationwizard.h \
         Widgets\wizardsettingspage.h \
         Widgets\wizardipsearchpage.h \
         Widgets\calculationresults.h \
         Widgets\calculationinfo.h \
         Widgets\welcomeinfo.h \
         IO\writeresults.h \
         Core\calculationscore.h \
         Core\mtrandom.h \
         Core\math.h \
         application.h \
         data.h \


FORMS    += Windows\mainwindow.ui \
         Windows\aboutwindow.ui \
         Widgets\calculationwizard.ui \
         Widgets\wizardsettingspage.ui \
         Widgets\wizardipsearchpage.ui \
         Widgets\calculationresults.ui \
         Widgets\calculationinfo.ui \
         Widgets\welcomeinfo.ui


RESOURCES += \
    graphics.qrc


win32:RC_FILE = resources.rc


# ------ d:/l is a path to folder with software-update library

LIBS += -Ld:/l -lsoftware-update

# ------ d:/l/includes/ is a path to folder with software-update library header files

INCLUDEPATH += d:/l/includes/

