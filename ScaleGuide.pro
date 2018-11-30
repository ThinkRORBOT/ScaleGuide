#-------------------------------------------------
#
# Project created by QtCreator 2017-10-08T17:56:24
#
#-------------------------------------------------

QT       += core gui
QT       += widgets
QT       += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ScaleGuide
TEMPLATE = app

CONFIG+= static

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    dbmanager.cpp \
    showfretboard.cpp \
    ShowFretBoardChords/chordwindow.cpp \
    ShowFretBoardNotes/notewindow.cpp \
    ShowFretBoardScales/showscale.cpp \
    ShowFretBoardScales/scalewindow.cpp

HEADERS  += mainwindow.h \
    dbmanager.h \
    showfretboard.h \
    ShowFretBoardNotes/notewindow.h \
    ShowFretBoardChords/chordwindow.h \
    ShowFretBoardScales/scalewindow.h \
    ShowFretBoardScales/showscale.h

FORMS    += mainwindow.ui \
    scalewindow.ui \
    showscale.ui \
    showfretboard.ui \
    ShowFretBoardChords/chordwindow.ui \
    ShowFretBoardNotes/notewindow.ui

RESOURCES += \
    resources.qrc

DISTFILES += \
    guitarboard.txt \
    note_to_scale.db
