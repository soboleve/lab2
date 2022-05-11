TEMPLATE = app

CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES = $$files("*.c", true)

HEADERS = $$files("*.h", true)

QMAKE_CFLAGS += -fprofile-arcs -ftest-coverage


INCLUDEPATH += ../text
