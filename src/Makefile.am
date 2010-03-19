bin_PROGRAMS = ImageViewer
ImageViewer_SOURCES = \
	main.h \
	main.cpp \
	imageviewer_frontend_base.cpp \
	imageviewer_frontend_base.h \
	imageviewer_backend_base.cpp \
	imageviewer_backend_base.h \
	imageviewer_backend_qt.cpp \
	imageviewer_backend_qt.h \
	imageviewer_frontend_qt_new.cpp \
	imageviewer_frontend_qt_new.h \
	imageviewer_frontend_qt_widget.cpp \
	imageviewer_frontend_qt_widget.h


imageviewer_frontend_qt_new.cpp:imageviewer_frontend_qt_new.moc
imageviewer_frontend_qt_widget.cpp:imageviewer_frontend_qt_widget.moc

imageviewer_frontend_qt_new.moc:
	moc imageviewer_frontend_qt_new.h -o imageviewer_frontend_qt_new.moc

imageviewer_frontend_qt_widget.moc:
	moc imageviewer_frontend_qt_widget.h -o imageviewer_frontend_qt_widget.moc

CLEANFILES = *moc *~
SUBDIRS = pwantools
LDADD = pwantools/libpwantools.a

AM_CXXFLAGS = $(QtCore_CFLAGS) $(QtGui_CFLAGS) $(BOOST_CPPFLAGS)
AM_LDFLAGS = $(QtCore_LIBS) $(QtGui_LIBS) $(BOOST_THREAD_LIB) $(BOOST_LDFLAGS) $(BOOST_FILESYSTEM_LIB)
