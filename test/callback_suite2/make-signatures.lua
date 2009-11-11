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
    print(signature)
  end
end

randomSignatures(nsigs)

