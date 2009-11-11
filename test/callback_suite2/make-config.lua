require "config"

local defs = {
  MAXARGS = maxargs,
  NSIGS   = nsigs
}

for k,v in pairs(defs) do
  io.write("#define CONFIG_" .. k .. " " .. v .. "\n" )
end
io.flush()

