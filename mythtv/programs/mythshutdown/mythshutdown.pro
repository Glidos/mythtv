include (../../settings.pro)
include (../../version.pro)
include (../programs-libs.pro)

QT += sql network

TEMPLATE = app
CONFIG += thread
target.path = $${PREFIX}/bin

INSTALLS = target

QMAKE_CLEAN += $(TARGET)

# Input
HEADERS += commandlineparser.h
SOURCES += main.cpp commandlineparser.cpp
QMAKE_CFLAGS_ISYSTEM =
