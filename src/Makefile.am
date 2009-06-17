bin_PROGRAMS = ImageViewer
ImageViewer_SOURCES = \
	t_imageviewer.moc \
	t_loadimage.moc \
	main.cpp \
	t_imageviewer.cpp \
	t_loadimage.cpp \
	pwanutils.cpp \
	pwanstrings.cpp \
	pwanoptions.cpp \
	pwandebug.cpp \
	pwancmdlineparser.cpp \
	imageviewer_frontend_qt.cpp \
	imageviewer_frontend_base.cpp


t_loadimage.cpp:t_loadimage.moc
t_imageviewer.cpp:t_imageviewer.moc

t_imageviewer.moc: 
	moc t_imageviewer.h -o t_imageviewer.moc

t_loadimage.moc:
	moc t_loadimage.h -o t_loadimage.moc

#t_imageviewer.cpp: moc_timageviewer
#moc_timageviewer:
#	moc t_imageviewer.h -o t_imageviewer.moc

#t_loadimage.cpp: moc_tloadimage
#moc_tloadimage:
#	moc t_loadimage.h -o t_loadimage.moc

CLEANFILES = *moc *~

AM_CPPFLAGS = $(QtCore_CFLAGS) $(QtGui_CFLAGS) $(BOOST_CPPFLAGS)
LIBS = $(QtCore_LIBS) $(QtGui_LIBS) $(BOOST_THREAD_LIB) $(BOOST_LDFLAGS) 
