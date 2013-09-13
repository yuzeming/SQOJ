QT = core network sql
TARGET = SQOJ
TEMPLATE = app
CONFIG += CONSOLE

#QMAKE_CXXFLAGS += -std=gnu++0x

CONFIG(debug, debug|release) {
  DEFINES += SUPERVERBOSE
}

HEADERS = \
    static.h \
    startup.h \
    requestmapper.h \
    controller/usercontroller.h \
    model/usermodel.h \
    model/probmodel.h \
    model/db.h \
    controller/probcontroller.h \
    model/submitmodel.h \
    controller/submitcontroller.h \
    controller/judgecontroller.h \
    controller/indexpage.h

SOURCES = main.cpp \
    static.cpp \
    startup.cpp \
    requestmapper.cpp \
    controller/usercontroller.cpp \
    model/usermodel.cpp \
    model/probmodel.cpp \
    model/db.cpp \
    controller/probcontroller.cpp \
    model/submitmodel.cpp \
    controller/submitcontroller.cpp \
    controller/judgecontroller.cpp \
    controller/indexpage.cpp

OTHER_FILES += \
    ../etc/SQOJ.ini \
    ../etc/docroot/* \
    ../etc/templates/* \
    ../readme.md

include(../lib/qtservice/src/qtservice.pri)
include(../lib/bfLogging/src/bfLogging.pri)
include(../lib/bfHttpServer/src/bfHttpServer.pri)
include(../lib/bfTemplateEngine/src/bfTemplateEngine.pri)
