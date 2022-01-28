
AC_PREREQ([2.69])
AC_INIT([moritz],[2.0.0],[Eckard Klotz 2008-2020])

AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_AUX_DIR([build-aux])

AC_PREFIX_DEFAULT([/usr/local/packages/${PACKAGE_NAME}-${PACKAGE_VERSION}])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])

dnl Checks for programs.
AC_PROG_CPP
AC_PROG_CXX
AM_PROG_AR
AC_PROG_RANLIB
AC_PROG_INSTALL

dnl Checks for libraries.
dnl Checks for header files.
dnl Checks for typedefs, structures, and compiler characteristics.
dnl Checks for library functions.

AC_CONFIG_FILES([
    Makefile
    lib/Makefile
    src/Makefile
])
AC_OUTPUT
