#include "../buildsys/dynmake/Makefile.base.M"

TARGET	= _L(dyncall_s)
OBJS	= _O(dyncall_vector) _O(dyncall_api) _O(dyncall_callvm) _O(dyncall_callvm_base) _O(dyncall_call) _O(dyncall_callf) _O(dyncall_struct)
all: _(TARGET)
_L(dyncall_s): _(OBJS)
	echo works!
