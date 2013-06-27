#-------------------------------------------------
#
# Project created by QtCreator 2010-10-30T14:42:05
#
#-------------------------------------------------

QT       += core gui network

TARGET = Chess
TEMPLATE = app


SOURCES += main.cpp\
        mainboard.cpp \
    board.cpp \
    piece.cpp \
    comunication.cpp \
    online.cpp \
    computer.cpp \
    move.cpp \
    enums.cpp \
    ia.cpp \
    boardevaluator.cpp \
    main.cpp

HEADERS  += mainboard.h \
    board.h \
    enums.h \
    piece.h \
    comunication.h \
    online.h \
    computer.h \
    move.h \
    ia.h \
    boardevaluator.h \
    board.h \
    online.cpp \
    online.h \
    piece.cpp \
    piece.h \
    computer.h \
    enums.h \
    ia.cpp \
    ia.h \
    board.cpp

FORMS    += mainboard.ui \
    connect.ui \
    dialog.ui \
    online.ui
