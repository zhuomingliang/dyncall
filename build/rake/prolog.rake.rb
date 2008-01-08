#///////////////////////////////////////////////////
#
#	prolog.rake.rb
#	Copyright 2007 Tassilo Philipp
#	Rakefile
#
#///////////////////////////////////////////////////


if File.exist? $TOP + 'config.rake.rb' then
	require $TOP + 'config.rake'
else
	puts 'Project not configured yet. Run configure.rb first.'
	exit
end


if File.exist? $TOP + 'globalConf.rake.rb' then
	require $TOP + 'globalConf.rake'
else
	$OUT_DIRS = {
		:scratch => './',
		:out     => './'
	}
end

