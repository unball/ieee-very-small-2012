#-------------------------------------------------
#
# Project created by QtCreator 2012-07-31T07:38:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Visualization_last
TEMPLATE = app


SOURCES += main.cpp\
	gameboard.cpp \
    soccerfield.cpp

HEADERS  += gameboard.h \
    soccerfield.h \
    soccerfield.h

FORMS    += gameboard.ui

RESOURCES += \
    VisualizationAppends.qrc

INCLUDEPATH += ../shared

LIBS += ../shared/*.o \
	-lm -lpthread -lrt \
	-lboost_thread -lboost_system -lboost_filesystem -lboost_regex
