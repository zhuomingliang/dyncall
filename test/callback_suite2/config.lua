-- calculate maxargs when mode = "ordered" ( hint: use log )
nsigs     = 4        -- number of functions to generate (used by make-signature)
offset    = math.pow(6,50)   -- when 'ordered': add offset to base number
step      = 7
mode      = "random"  -- generatore mode: 'random' or 'ordered' type sequences
maxargs   = 16        -- maximum function arity 
minargs   = 10         -- minimum function arity 
argtypes  = "Bilpfd"   -- supported argument types
rettypes  = argtypes   -- supported return types (currently no void support)

