#///////////////////////////////////////////////////
#
#	Rakefile.rb
#	Copyright 2007 Tassilo Philipp
#	Rakefile
#
#///////////////////////////////////////////////////


$TOP = '../../'
require $TOP + 'build/rake/prolog.rake'


$APP       = 'nm'
$PCH       = 'Headers'
$OBJS      = ['nm', '../main_Windows']
$LIBS      = ['dyncall_s', 'dynload_s']
$LIBPATHS  = ['../../dyncall', '../../dynload']


require $TOP + 'build/rake/epilog.rake'

