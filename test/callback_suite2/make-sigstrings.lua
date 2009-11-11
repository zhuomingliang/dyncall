local id = 1
for signature in io.lines() do
  io.write( '"' .. signature .. '",\n' )
end

