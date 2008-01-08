#///////////////////////////////////////////////////
#
#	tool_windows_msvc_rake.rb
#	Copyright 2007 Tassilo Philipp
#	Rakefile
#
#///////////////////////////////////////////////////


$CC         = 'cl'
$CXX        = 'cl'
$AS         = 'ml'#64 if x64 @@@
$AR         = 'lib'
$LD         = 'link'

$ASFLAGS    = ''
$CFLAGS     = '/EHsc /GR- /GS- /Ox'
$CXXFLAGS   = $CFLAGS
$LDFLAGS    = '/OPT:REF /OPT:ICF /NOLOGO'
$ARFLAGS    = '/NOLOGO'

$OBJ_PREFIX = ''
$OBJ_SUFFIX = '.obj'
$LIB_PREFIX = ''
$LIB_SUFFIX = '.lib'
$DLL_PREFIX = ''
$DLL_SUFFIX = '.dll'
$APP_PREFIX = ''
$APP_SUFFIX = '.exe'



# Pipe errors to output stream - otherwise we don't see no errors at all.
#$stderr = $stdout
$ERR_RDR = ' 2>&1'

# Concatenate libpaths (and remove empty strings, etc.).
#if $LIBPATHS.class == Array then
#	$LIBPATHS.delete_if { |s| /^[ \t]*$/ =~ s }
#	LPATHS = ($LIBPATHS and /[^ \t]$/ =~ $LIBPATHS) ? "/LIBPATH:#{$LIBPATHS.join(' /LIBPATH:'}"
#end
LPATHS = $LIBPATHS ? "/LIBPATH:#{$LIBPATHS.join(' /LIBPATH:')}" : ''
LIBS   = $LIBS ? $LIB_PREFIX + $LIBS.join($LIB_SUFFIX + ' ' + $LIB_PREFIX) + $LIB_SUFFIX : ''



rule '.obj' => ['.asm'] do |t| 
	exit unless system("#{$AS} #{$ASFLAGS} /c /nologo /Fo#{t.name} #{t.source}" + $ERR_RDR) == true
end



rule '.obj' => ['.c'] do |t|
	exit unless system("#{$CC} #{$CFLAGS} /c /nologo /Fo#{t.name} #{t.source}" + $ERR_RDR) == true
end


rule '.obj' => ['.cpp'] do |t| 
	exit unless system("#{$CXX} #{$CXXFLAGS} /c /nologo /Fo#{t.name} #{t.source}" + $ERR_RDR) == true
end


rule '.lib' do |t|
	puts 'Creating ' + t.name + ' ...'
	exit unless system("#{$AR} #{$ARFLAGS} /OUT:#{t.name} #{t.prerequisites}" + $ERR_RDR) == true
end


rule '.dll' do |t|
	puts 'Linking ' + t.name + ' ...' 
	exit unless system("#{$LD} /DLL #{$LDFLAGS} #{LPATHS} /OUT:#{t.name} #{t.prerequisites} #{LIBS}" + $ERR_RDR) == true
end


rule '.exe' do |t|
	puts 'Linking ' + t.name + ' ...'
	exit unless system("#{$LD} #{$LDFLAGS} #{LPATHS} /OUT:#{t.name} #{t.prerequisites} #{LIBS}" + $ERR_RDR) == true
end


rule '.pdf' => ['.tex'] do |t|
	exit unless system("pdflatex #{t.name}") == true
end

