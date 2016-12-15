AC_INIT([messyfoods], [0.1], [myrunescapeemail609@gmail.com])
AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects])
AC_PROG_CXX
AC_LANG([C++])

AC_CHECK_HEADER([SFML/Audio.hpp], [], [AC_MSG_ERROR([header not found.])])
AC_CHECK_HEADER([SFML/Graphics.hpp], [], [AC_MSG_ERROR([header not found.])])

AC_CHECK_LIB([sfml-audio], [main], [], [AC_MSG_ERROR([library not found.])])
AC_CHECK_LIB([sfml-graphics], [main], [], [AC_MSG_ERROR([library not found.])])
AC_CHECK_LIB([sfml-system], [main], [], [AC_MSG_ERROR([library not found.])])
AC_CHECK_LIB([sfml-window], [main], [], [AC_MSG_ERROR([library not found.])])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
