require "config"
require "math"
require "string"

local nargtypes = string.len(argtypes)
local nrettypes = string.len(rettypes)

function randomSignatures(nsigs)
  local i 
  for i = 1, nsigs do
    local nargs = math.random(maxargs+1) - 1
    local signature = ""
    for j = 1, nargs do
      local typeindex = math.random(nargtypes)
      signature = signature .. string.sub(argtypes, typeindex, typeindex)
    end
    local rtypeindex = math.random(nrettypes)
    signature = signature .. ")" .. string.sub(rettypes, rtypeindex, rtypeindex)
    io.write(signature .. "\n")
  end
end

function orderedSignature(x)
  local signature = ""
  local typeindex
  while true do
    if x < nargtypes then break end
    typeindex = 1 + math.mod(x, nargtypes)
    signature = signature .. string.sub(argtypes, typeindex, typeindex)
    x = math.floor( x / nargtypes )
  end
  typeindex = 1 + x
  signature = signature .. ")" .. string.sub(argtypes, typeindex, typeindex)
  return signature
end

function orderedSignatures(nsigs)
  local i 
  for i = 1, nsigs do
    io.write( orderedSignature(offset+i) .. "\n" )
  end
end

if mode == "random" then
  randomSignatures(nsigs)
elseif mode == "ordered" then
  orderedSignatures(nsigs)
end

io.flush()

