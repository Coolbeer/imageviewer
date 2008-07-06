#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.61)
AC_INIT([ImageViewer], 0.1.5)
AC_CONFIG_SRCDIR([src/main.h])
AC_CONFIG_HEADER([config.h])
AM_INIT_AUTOMAKE([-Wall -Werror])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_CXXCPP
AC_PROG_INSTALL

CFLAGS="$CFLAGS -Wall -Werror -Wextra -pedantic -Wno-long-long"
CXXFLAGS="$CXXFLAGS -Wall -Werror -Wextra -pedantic -Wno-long-long"

# Checks for libraries.

PKG_CHECK_MODULES([QtCore], [QtCore >= 4.2.0])
AC_SUBST(QtCore_CFLAGS)
AC_SUBST(QtCore_LIBS)

PKG_CHECK_MODULES(QtGui, QtGui >= 4.2.0)
AC_SUBST(QtGui_CFLAGS)
AC_SUBST(QtGui_LIBS)

# Checks for header files.

AC_HEADER_STDC
AC_CHECK_HEADERS(netdb.h sys/socket.h arpa/inet.h errno.h sys/time.h dirent.h,,
    AC_MSG_ERROR(You need the glibc header files installed))

AC_LANG_SAVE
AC_LANG_CPLUSPLUS
AC_CHECK_HEADERS(stdexcept,,
    AC_MSG_ERROR(You need the standard <stdexcept> header file))

AC_CHECK_HEADERS(vector string iostream list map fstream sstream,,
    AC_MSG_ERROR(You need to have the libstdc++ headers installed))

AC_LANG_RESTORE


# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile
                 src/Makefile])
AC_OUTPUT
