cl /nologo /DMAKE_CMD_%2 /EP Makefile.M 1> Makefile.dynmake
%2 /NOLOGO /f Makefile.dynmake %1
