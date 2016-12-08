# Run "autoreconf" to create the "configure" script.

# Initialize autoconf with the name of the program,
# the version number, and the contact information.
#
# https://www.gnu.org/software/autoconf/manual/autoconf.html#Initializing-configure
AC_INIT([messyfoods], [0.1], [myrunescapeemail609@gmail.com])

# Initialize automake with all warnings.
#
# https://www.gnu.org/software/automake/manual/html_node/Public-Macros.html
#
# "foreign" will ignore any missing files (README, AUTHORS...).
#
# https://www.gnu.org/software/automake/manual/html_node/Strictness.html
AM_INIT_AUTOMAKE([-Wall -Werror foreign])

# Check for a compiler.
#
# https://www.gnu.org/software/autoconf/manual/autoconf.html#C-Compiler
AC_PROG_CXX

# Check for libraries.
#
# https://www.gnu.org/software/autoconf/manual/autoconf.html#Libraries
AC_CHECK_LIB([sfml-audio], [main], [],
             [AC_MSG_ERROR([libsfml-audio not found.])])

AC_CHECK_LIB([sfml-graphics], [main], [],
             [AC_MSG_ERROR([libsfml-graphics not found.])])

AC_CHECK_LIB([sfml-system], [main], [],
             [AC_MSG_ERROR([libsfml-system not found.])])

AC_CHECK_LIB([sfml-window], [main], [],
             [AC_MSG_ERROR([libsfml-window not found.])])

# A list of the Makefiles that need to be created.
AC_CONFIG_FILES([Makefile
                 data/Makefile
                 data/fonts/Makefile
                 data/music/Makefile
                 data/sfx/Makefile
                 data/textures/Makefile
                 data/textures/ui/Makefile
                 src/Makefile])

# Rebuild these header files.
#
# This header file can be used in the project. It contains
# useful strings provided by Autotools.
#
# https://www.gnu.org/software/autoconf/manual/autoconf.html#Configuration-Headers
AC_CONFIG_HEADERS([config.h])

# Finish up by writing the new configuration files.
#
# https://www.gnu.org/software/autoconf/manual/autoconf.html#Output
AC_OUTPUT
