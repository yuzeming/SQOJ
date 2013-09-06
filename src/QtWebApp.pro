QT = core network
TARGET = QtWebApp
TEMPLATE = app
CONFIG += CONSOLE

QMAKE_CXXFLAGS += -std=gnu++0x

CONFIG(debug, debug|release) {
  DEFINES += SUPERVERBOSE
}

HEADERS = \
    static.h \
    startup.h \
    requestmapper.h \
    controller/dumpcontroller.h \
    controller/formcontroller.h \
    controller/fileuploadcontroller.h \
    controller/sessioncontroller.h \
    controller/usercontroller.h

SOURCES = main.cpp \
    static.cpp \
    startup.cpp \
    requestmapper.cpp \
    controller/dumpcontroller.cpp \
    controller/formcontroller.cpp \
    controller/fileuploadcontroller.cpp \
    controller/sessioncontroller.cpp \
    controller/usercontroller.cpp

OTHER_FILES += \
    ../Doxyfile \
    ../etc/QtWebApp.ini \
    ../etc/docroot/* \
    ../etc/templates/* \
    ../doc/releasenotes.txt \
    ../doc/license.txt \
    ../doc/readme.txt

include(../lib/qtservice/src/qtservice.pri)
include(../lib/bfLogging/src/bfLogging.pri)
include(../lib/bfHttpServer/src/bfHttpServer.pri)
include(../lib/bfTemplateEngine/src/bfTemplateEngine.pri)
