noinst_LIBRARIES = libpwantools.a
libpwantools_a_SOURCES = \
	pwanutils.h \
	pwanutils.cpp \
	pwandebug.cpp \
	pwandebug.h \
	pwanstrings.cpp \
	pwanstrings.h \
	pwancmdlineparser.cpp \
	pwancmdlineparser.h

CLEANFILES = *moc *~

AM_CXXFLAGS = $(BOOST_CPPFLAGS)
AM_LDFLAGS = $(BOOST_THREAD_LIB) $(BOOST_LDFLAGS) $(BOOST_FILESYSTEM_LIB)
