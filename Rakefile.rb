#///////////////////////////////////////////////////
#
#	Rakefile.rb
#	Copyright 2007 Tassilo Philipp
#	Rakefile
#
#///////////////////////////////////////////////////


$TOP = './' 
require $TOP + 'build/rake/prolog.rake'


$SUBS = [:dyncall, :dynload]

task :test do |t|
	p t.methods
	p t.name
	chdir t.to_s do
		exit unless system('rake --nosearch') == true
	end
end


require $TOP + 'build/rake/epilog.rake'

