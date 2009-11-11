nsigs     = 20        -- number of functions to generate (used by make-signature)
maxargs   = 3         -- maximum function arithy
argtypes  = "Bilpfd"  -- supported argument types
rettypes  = argtypes  -- supported return types (currently no void support)
typemap   =           -- type map from signature character to C type name
{ 
  v="DCvoid",
  B="DCbool",
  c="DCchar",
  s="DCshort",
  i="DCint",
  j="DClong",
  l="DClonglong",
  p="DCpointer",
  f="DCfloat",
  d="DCdouble"
}

