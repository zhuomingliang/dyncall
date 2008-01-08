#///////////////////////////////////////////////////
#
#	globalConf.rake.rb
#	Copyright 2007 Tassilo Philipp
#	Rakefile
#
#///////////////////////////////////////////////////


# @@@ ADD CONFIG TO SCRATCHPATH
$OUT_DIRS = {
	:scratch => $TOP + '../n-saneBuild/' + File.basename(Dir.pwd) + '/',
	:out     => $TOP + '../n-saneBin/system/'
}

