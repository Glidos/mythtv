
h264test: h264test.cc H264Parser.cpp
	g++ -D__STDC_CONSTANT_MACROS \
	    -I. -I../../libmythdb -I../.. \
	    -I../../.. -I../../../external/FFmpeg \
	    -o h264test h264test.cc H264Parser.cpp \
	    -L../../../external/FFmpeg/libavcodec -lmythavcodec
