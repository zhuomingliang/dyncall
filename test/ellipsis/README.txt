dyncall stress test suite: testing ellipsis C calls
===================================================
(C) 2007 Daniel Adler

requirements:
  python (for preprocessing)

configuration:
  edit "nargs" in mkcase.py and run
  
    make distclean 
    make 
    
  on shell.
  

usage:

  ellipsis         	        - run full range
  ellipsis <id> 		- run test id <id>
  ellipsis <from> <to>		- run test id <from> to id <to> (inclusive).

  see test details in case.h


description:

  the test invokes 'void'-ellipsis functions that effectively overwrite global 
  variables in a structured way.
  
  functions are identified by an id (a number starting at 0).
  
  the implementation of each function does
  
    sets the gID to its id (which is compiled in) 
  
    sets all arguments into type-specific value vectors at the given position
  

