Notes on building with CMake
----------------------------

Build in-source
---------------
cd <dyncall-source-dir>
cmake .
make -f Makefile

NOTE: The "-f Makefile" flag !
If you build in-source make sure to specify the makefile with "-f Makefile".
Otherwise GNU make will use GNUmakefile.


Install in a specific location
------------------------------
cmake -DCMAKE_INSTALL_PREFIX=<absolute-path>


Tested settings
---------------
- CMake Unix Makefile generators on Mac OS X and Linux.


