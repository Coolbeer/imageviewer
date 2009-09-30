#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.63)
AC_INIT([ImageViewer],[0.1.5])
AC_CONFIG_SRCDIR([src/main.h])
AC_CONFIG_HEADER([config.h])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([-Wall -Werror])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CXXCPP
AX_BOOST_BASE([1.37.0])
AX_BOOST_THREAD
AX_BOOST_FILESYSTEM
AX_BOOST_ASIO
AX_BOOST_DATE_TIME
AC_PROG_INSTALL
AC_PROG_LIBTOOL

CFLAGS="$CFLAGS -Wall -Werror -Wextra -pedantic -Wno-long-long"
CXXFLAGS="$CXXFLAGS -Wall -Werror -Wextra -pedantic -Wno-long-long"

# Checks for libraries.

PKG_CHECK_MODULES([QtCore], [QtCore >= 4.5.1])
AC_SUBST(QtCore_CFLAGS)
AC_SUBST(QtCore_LIBS)

PKG_CHECK_MODULES(QtGui, QtGui >= 4.5.1)
AC_SUBST(QtGui_CFLAGS)
AC_SUBST(QtGui_LIBS)


# Checks for header files.

AC_LANG_PUSH([C++])

AC_CHECK_HEADER([stdexcept],,   [stdexcept not found.])
AC_CHECK_HEADER([vector],,      [vector not found.])
AC_CHECK_HEADER([string],,      [string not found.])
AC_CHECK_HEADER([iostream],,    [iostream not found.])
AC_CHECK_HEADER([map],,         [map not found.])
AC_CHECK_HEADER([fstream],,     [fstream not found.])
AC_CHECK_HEADER([string.h],,    [string.h not found.])
AC_CHECK_HEADER([cctype],,      [cctype not found.])
AC_CHECK_HEADER([sys/stat.h],,  [sys/stat.h not found.])
AC_CHECK_HEADER([stdlib.h],,    [stdlib.h not found.])

AC_LANG_POP([C++])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile src/Makefile src/pwantools/Makefile])

AC_OUTPUT
