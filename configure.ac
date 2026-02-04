m4_define([__PACKAGE], [DMitry])
m4_define([__VERSION], [1.3a])
m4_define([__ADDRESS], [james@mor-pah.net])
m4_define([__URL],     [http://mor-pah.net/software/dmitry-deepmagic-information-gathering-tool/])

AC_PREREQ([2.72])

AC_INIT(m4_defn([__PACKAGE]),m4_defn([__VERSION]),m4_defn([__ADDRESS]),[],m4_defn([__URL]))
AM_INIT_AUTOMAKE([subdir-objects])

AM_SANITY_CHECK
AC_CONFIG_SRCDIR([src/includes/tcp_sock.h])
AC_CONFIG_HEADERS([src/includes/config.h])
AC_PROG_CC

AC_CHECK_HEADERS([arpa/inet.h netdb.h netinet/in.h stdlib.h string.h sys/socket.h sys/time.h unistd.h])
AC_CHECK_HEADERS_ONCE([sys/time.h])

AC_STRUCT_TM
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_FUNC_SELECT_ARGTYPES
AC_DEFINE_UNQUOTED([RETSIGTYPE],[void],[Define as the return type of signal handlers
		    ('int' or 'void').])

AC_FUNC_STRFTIME
AC_CHECK_FUNCS([alarm gethostbyaddr gethostbyname memset socket strstr])
AC_CHECK_HEADER([getopt.h], [AC_DEFINE([HAVE_GETOPT_H], 1, [Description])])
AC_CHECK_FUNC([sigsetjmp], [AC_DEFINE([HAVE_SIGSETJMP_F], 1, [Description])])
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
