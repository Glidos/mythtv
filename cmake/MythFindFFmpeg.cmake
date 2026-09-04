#
# Copyright (C) 2022-2023 David Hampton
#
# See the file LICENSE_FSF for licensing information.
#

#
# This module needs pkg-config functionality
#
find_package(PkgConfig REQUIRED)

#
# FFmpeg is required. This can only find the MythTV version that was just
# installed, because its looking for libmythavcodec , not libavcodec.
#
# Empty MYTH_FFMPEG_BUILD_SUFFIX → libmythavcodec (unchanged for default builds).
# Set to e.g. "-37" when packaging against FFmpeg built with --build-suffix=-37.
#
set(_myth_ff_suf "${MYTH_FFMPEG_BUILD_SUFFIX}")
if(_myth_ff_suf STREQUAL "")
  message(STATUS "Looking for MythTV FFmpeg wrappers (unsuffixed pkg-config names)")
else()
  message(STATUS "Looking for MythTV FFmpeg wrappers with suffix '${_myth_ff_suf}'")
endif()

pkg_check_modules(LIBAVCODEC libmythavcodec${_myth_ff_suf} REQUIRED IMPORTED_TARGET)
pkg_check_modules(LIBAVDEVICE libmythavdevice${_myth_ff_suf} REQUIRED IMPORTED_TARGET)
pkg_check_modules(LIBAVFILTER libmythavfilter${_myth_ff_suf} REQUIRED IMPORTED_TARGET)
pkg_check_modules(LIBAVFORMAT libmythavformat${_myth_ff_suf} REQUIRED IMPORTED_TARGET)
pkg_check_modules(LIBAVUTIL libmythavutil${_myth_ff_suf} REQUIRED IMPORTED_TARGET)
pkg_check_modules(LIBSWRESAMPLE libmythswresample${_myth_ff_suf} REQUIRED IMPORTED_TARGET)
pkg_check_modules(LIBSWSCALE libmythswscale${_myth_ff_suf} REQUIRED IMPORTED_TARGET)
