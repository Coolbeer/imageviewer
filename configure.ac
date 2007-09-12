#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.50)
AC_INIT([ImageViewer], 0.1.4_pre2)
AC_CONFIG_SRCDIR([src/main.h])
AC_CONFIG_HEADER([config.h])
AM_INIT_AUTOMAKE([-Wall -Werror])


AC_ARG_ENABLE(debug,[  --enable-debug	Turn on debugging], [case "${enableval}" in yes) debug=true ;; no)  debug=false ;;
    *) AC_MSG_ERROR(bad value ${enableval} for --enable-debug) ;; esac],[debug=false])
AM_CONDITIONAL(PWANDEBUG, test x$debug = xtrue)

if test x$debug = xtrue; then
AC_DEFINE(PWANDEBUG, 1, [Turn on debugging])
fi

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

CFLAGS="$CFLAGS -Wall -Werror"
CXXFLAGS="$CXXFLAGS -Wall -Werror"

# Checks for libraries.

PKG_CHECK_MODULES([QtCore], [QtCore >= 4.2.0])
AC_SUBST(QtCore_CFLAGS)
AC_SUBST(QtCore_LIBS)

PKG_CHECK_MODULES(QtGui, QtGui >= 4.2.0)
AC_SUBST(QtGui_CFLAGS)
AC_SUBST(QtGui_LIBS)

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile
                 src/Makefile])
AC_OUTPUT
