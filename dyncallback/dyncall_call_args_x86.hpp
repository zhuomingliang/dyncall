/*
 * dyncall_call_args_x86.hpp
 *
 *  Created on: Feb 9, 2009
 *      Author: dadler
 */

#ifndef DYNCALL_CALL_ARGS_X86_HPP_
#define DYNCALL_CALL_ARGS_X86_HPP_

namespace dyncall
{
	struct callmode_x86_cdecl
	{
		typedef struct { int* ptr; } args;
		typedef struct {  } info;
	};

	struct callmode_x86_stdcall
	{
		typedef struct { int* ptr; } args;
		typedef struct { size_t cleanup; } info;
	};

	struct callmode_x86_fastcall_ms
	{
		typedef struct { int* ptr; int reg_data[2]; int reg_count; } args;
		typedef struct { size_t cleanup; } info;
	};

	struct callmode_x86_fastcall_gnu
	{
		typedef struct { int* ptr; int reg_data[2]; int reg_count; } args;
		typedef struct { size_t cleanup; } info;
	};

	struct callback
	{
		virtual char invokeCall(callback*, args*, value*);
	};

	struct callback_entry;

	callback_entry* newCallback();
	void            freeCallback(callback_entry*);

}

#endif /* DYNCALL_CALL_ARGS_X86_HPP_ */
