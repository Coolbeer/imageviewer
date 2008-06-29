bin_PROGRAMS = ImageViewer
ImageViewer_SOURCES = \
	t_imageviewer.moc \
	t_loadimage.moc \
	main.cpp \
	t_imageviewer.cpp \
	t_loadimage.cpp \
	pwandir.cpp \
	pwanutils.cpp \
	pwanfileinfo.cpp \
	main.h \
	t_imageviewer.h \
	t_loadimage.h \
	pwandir.h \
	pwanutils.h \
	pwanfileinfo.h \
	pwanstrings.cpp \
	pwanstrings.h \
	pwanoptions.cpp \
	pwanoptions.h \
	pwandebug.cpp \
	pwandebug.h

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

AM_CPPFLAGS = $(QtCore_CFLAGS) $(QtGui_CFLAGS)
LIBS = $(QtCore_LIBS) $(QtGui_LIBS)