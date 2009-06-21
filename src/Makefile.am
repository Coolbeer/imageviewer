bin_PROGRAMS = ImageViewer
ImageViewer_SOURCES = \
	main.h \
	main.cpp \
	pwanutils.h \
	pwanutils.cpp \
	pwandebug.cpp \
	pwandebug.h \
	t_loadimage.cpp \
	t_loadimage.moc \
	t_loadimage.h \
	pwanstrings.cpp \
	pwanstrings.h \
	t_imageviewer.cpp \
	t_imageviewer.moc \
	t_imageviewer.h \
	pwancmdlineparser.cpp \
	pwancmdlineparser.h \
	imageviewer_frontend_qt.cpp \
	imageviewer_frontend_qt.h \
	imageviewer_frontend_base.cpp \
	imageviewer_frontend_base.h

t_loadimage.cpp:t_loadimage.moc
t_imageviewer.cpp:t_imageviewer.moc

t_imageviewer.moc: 
	moc t_imageviewer.h -o t_imageviewer.moc

t_loadimage.moc:
	moc t_loadimage.h -o t_loadimage.moc

CLEANFILES = *moc *~

AM_CXXFLAGS = $(QtCore_CFLAGS) $(QtGui_CFLAGS) $(BOOST_CPPFLAGS)
AM_LDFLAGS = $(QtCore_LIBS) $(QtGui_LIBS) $(BOOST_THREAD_LIB) $(BOOST_LDFLAGS) $(BOOST_FILESYSTEM_LIB)
