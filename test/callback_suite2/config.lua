                        -- global section
                  
nsigs     = 1000        -- number of functions to generate (used by make-signature)
mode      = "random"    -- generatore mode: 'random' or 'ordered' type sequences
minargs   = 1           -- minimum number of arguments
maxargs   = 100         -- maximum number of arguments

                        -- type system section

argtypes  = "Bilpfd"    -- supported argument types
rettypes  = argtypes    -- supported return types (currently no void support)

                        -- following options are related to 'ordered' mode
offset    = 0           -- math.pow(6,50)   -- when 'ordered': add offset to base number
step      = 0           -- combinartory

                        -- random section
seed      = 1           -- the seed

--[[ 
TODO:
- calculate maxargs when mode = "ordered" ( hint: use log )
]]

