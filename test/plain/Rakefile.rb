#///////////////////////////////////////////////////
#
#	Rakefile.rb
#	Copyright 2007 Tassilo Philipp
#	Rakefile
#
#///////////////////////////////////////////////////


$TOP = '../../'
require $TOP + 'build/rake/prolog.rake'


$APP       = 'plain'
$PCH       = 'Headers'
$OBJS      = ['test_main', '../main_Windows']
$LIBS      = ['dyncall_s']
$LIBPATHS  = ['../../dyncall']


require $TOP + 'build/rake/epilog.rake'

