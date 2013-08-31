for I in `find . -name "GNUmakefile"`; do
  D=`dirname $I`
  svn mv $D/GNUmakefile $D/Makefile.gmake
done
for I in `find . -name "BSDmakefile"`; do
  D=`dirname $I`
  svn mv $D/BSDmakefile $D/Makefile.bsdmake
done
