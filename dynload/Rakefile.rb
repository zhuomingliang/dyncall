#///////////////////////////////////////////////////
#
#	Rakefile.rb
#	Copyright 2007 Tassilo Philipp
#	Rakefile
#
#///////////////////////////////////////////////////


$TOP = '../'
require $TOP + 'build/rake/prolog.rake'


$LIB  = 'dynload_s'
$PCH  = 'Headers'
$OBJS = ['dynload_win32']


require $TOP + 'build/rake/epilog.rake'

