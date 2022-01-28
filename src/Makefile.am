
bin_PROGRAMS = abc2xml xml2abc

abc2xml_SOURCES = abc2xml.cpp
xml2abc_SOURCES = xml2abc.cpp

AM_CPPFLAGS = -I. -I@top_builddir@/lib
AM_CFLAGS =
AM_CXXFLAGS = -std=c++11
AM_LDFLAGS = -L. -L../lib @top_builddir@/lib/libhelper.a

LIBADD =
LDADD = -lhelper
