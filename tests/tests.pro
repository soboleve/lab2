include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += thread
CONFIG -= qt

QMAKE_CXXFLAGS += -fprofile-arcs -ftest-coverage
QMAKE_CFLAGS += -fprofile-arcs -ftest-coverage

DEFINES += INPUTDIR=\\\"$$PWD/input/\\\"

SOURCES += main.cpp \
           ../editor/save.c \
           ../editor/load.c \
           ../editor/show.c \
           ../editor/mwcursor.c \
           ../editor/showlineswithdigits.c \
           ../editor/ch.c \
           ../editor/c1n.c \
           $$files("../editor/text/*.c", true)

HEADERS += tests.h

LIBS += -lgcov

DISTFILES += input.txt
