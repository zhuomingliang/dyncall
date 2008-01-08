#///////////////////////////////////////////////////
#
#	Rakefile.rb
#	Copyright 2007 Tassilo Philipp
#	Rakefile
#
#///////////////////////////////////////////////////


$TOP = '../../'
require $TOP + 'build/rake/prolog.rake'


$APP       = 'callf'
$PCH       = 'Headers'
$OBJS      = ['main', '../main_Windows']
$LIBS      = ['dyncall_s']
$LIBPATHS  = ['../../dyncall']


require $TOP + 'build/rake/epilog.rake'

