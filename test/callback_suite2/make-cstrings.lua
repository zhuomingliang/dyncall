for line in io.lines() do
  io.write( '"' .. line .. '",\n' )
end
io.flush()

