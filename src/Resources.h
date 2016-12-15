#ifndef RESOURCES_H
#define RESOURCES_H

//PKGDATADIR is defined in the "Makefile.am" file, used by GNU Autotools
//If it doesn't exist, just set it to the local project data directory
#ifndef PKGDATADIR
    #define PKGDATADIR "../data"
#endif

#endif // RESOURCES_H
