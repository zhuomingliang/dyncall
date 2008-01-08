#///////////////////////////////////////////////////
#
#	Rakefile.rb
#	Copyright 2007 Tassilo Philipp
#	Rakefile
#
#///////////////////////////////////////////////////


$TOP = '../../'
require $TOP + 'build/rake/prolog.rake'


$APP       = 'ellipse'
$PCH       = 'Headers'
$OBJS      = ['main', 'ellipse', '../main_Windows']
$TEMPFILES = ['case.h', 'config.h']
$LIBS      = ['dyncall_s']
$LIBPATHS  = ['../../dyncall']

task :autogen      => $TEMPFILES
file $TEMPFILES[0] => ['mkcase.py']
file $TEMPFILES[1] => ['mkcase.py'] do
	puts "Generating #{$TEMPFILES.join(', ')} ..."
	system "mkcase.py >#{$TEMPFILES[0]} 2>#{$TEMPFILES[1]}"
end


require $TOP + 'build/rake/epilog.rake'

