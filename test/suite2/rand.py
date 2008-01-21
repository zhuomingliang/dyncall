#!/usr/bin/python

import random
import sys

N = 100
MINARG = 0
MAXARG = 19

argtypes = [ 'B','c','s','i','l','L','f','d','p' ]
apitypes = [ '_' ]

def sig(n):
  s = ""
  x = random.randint( 0, len(apitypes)-1 )
  # s += apitypes[x]
  for i in xrange(0,n):
    x = random.randint( 0, len(argtypes)-1 )
    s += argtypes[x]
  return s

for i in xrange(0,N):
  n = random.randint(MINARG,MAXARG)
  sys.stdout.write( sig(n) )
  sys.stdout.write( "\n" )

