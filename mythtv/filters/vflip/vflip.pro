include ( ../filter-common.pro )
include ( ../filter-avcodec.pro )
INCLUDEPATH += ../../libs/libmythtv \
    ../../libs/libavcodec \
    ../..

# Input
SOURCES += filter_vflip.c
QMAKE_CFLAGS_ISYSTEM =
