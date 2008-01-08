#///////////////////////////////////////////////////
#
#	Rakefile.rb
#	Copyright 2007 Tassilo Philipp
#	Rakefile
#
#///////////////////////////////////////////////////


$TOP = '../'
require $TOP + 'build/rake/prolog.rake'


$LIB  = 'dyncall_s'
$PCH  = 'Headers'
$OBJS = ['dyncall', 'dyncall_callf', 'dyncall_callvm_x86', 'dyncall_vector', 'dyncall_x86_win32']


require $TOP + 'build/rake/epilog.rake'

