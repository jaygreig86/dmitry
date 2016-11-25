AC_PREREQ(2.59)
VERSION="1.2a"
PACKAGE=DMitry
ADDRESS=james@mor-pah.net
AC_INIT
AM_INIT_AUTOMAKE($PACKAGE, $VERSION)
AM_SANITY_CHECK
AC_CONFIG_SRCDIR([src/includes/tcp_sock.h])
AC_CONFIG_HEADER([src/includes/config.h])
AC_PROG_CC
AC_HEADER_STDC
AC_CHECK_HEADERS([arpa/inet.h netdb.h netinet/in.h stdlib.h string.h sys/socket.h sys/time.h unistd.h])
AC_HEADER_TIME
AC_STRUCT_TM
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_FUNC_SELECT_ARGTYPES
AC_TYPE_SIGNAL
AC_FUNC_STRFTIME
AC_CHECK_FUNCS([alarm gethostbyaddr gethostbyname memset socket strstr])
AC_CHECK_HEADER([getopt.h], [AC_DEFINE([HAVE_GETOPT_H], 1, [Description])])
AC_CHECK_FUNC([sigsetjmp], [AC_DEFINE([HAVE_SIGSETJMP_F], 1, [Description])])
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
