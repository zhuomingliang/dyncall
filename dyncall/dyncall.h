#ifndef DYNCALL_H
#define DYNCALL_H

/*/////////////////////////////////////////////////////////////////////////////
                              
                 dyncall library - ANSI C API - Version 0.2 

//////////////////////////////////////////////////////////////////////////// */

#include "dyncall_types.h"

#ifdef __cplusplus
extern "C" {
#endif 

/** library API, specifies static linkage (left empty) */
#define DC_API

/** opaque CallVM structure */
typedef struct DCCallVM_    DCCallVM;

#define DOXY_GROUP 1

#if DOXY_GROUP
/** \defgroup Modes Supported Calling Convention Modes */
/*@{*/
#endif

/** Default C calling convention mode. Also applicable for ellipsis calls. */
#define DC_CALL_C_DEFAULT               0 
/** Win32/X86 platform: cdecl calling convention mode */
#define DC_CALL_C_X86_CDECL             1 
/** Win32/X86 platform: stdcall calling convention mode */
#define DC_CALL_C_X86_WIN32_STD         2
/** Win32/X86 platform: (microsoft-) fastcall calling convention mode */
#define DC_CALL_C_X86_WIN32_FAST_MS     3
/** Win32/X86 platform: (microsoft-) thiscall calling convention mode */
#define DC_CALL_C_X86_WIN32_THIS_MS     4
/** Win32/X86 platform: (gnu-) thiscall calling convention mode */
#define DC_CALL_C_X86_WIN32_THIS_GNU    5
/** Win32/X86 platform: (gnu-) fastcall calling convention mode */
#define DC_CALL_C_X86_WIN32_FAST_GNU    6
/** X64 Win64 platform: default c calling convention mode */
#define DC_CALL_C_X64_WIN64             7
/** PPC32/Darwin platform: default c calling convention mode */
#define DC_CALL_C_PPC32_DARWIN          8
/** ARM platform: default C calling convention mode */
#define DC_CALL_C_ARM                   9
/** MIPS32 platform: C EABI calling convention mode */
#define DC_CALL_C_MIPS32_EABI		10
/** MIPS32 Playstation Portable Homebrew platform: default C calling convention mode */
#define DC_CALL_C_MIPS32_PSPSDK		DC_CALL_C_MIPS32_EABI

#if DOXY_GROUP
/*@}*/
/** \defgroup ManageFuncs Init/Reset/Release functions */
/*@{*/
#endif

/** CallVM Allocation function
 *  @param size specifies the number of bytes (maximum) to be allocate memory for the internal argument 
 *   vector used for one call. 
 *  @note a size of 256 is usually enough (e.g. would allow for calls up to 64 integer arguments).
 *  @returns pointer on opaque CallVM structure.
 */
DC_API DCCallVM* dcNewCallVM     (DCsize size);

/** CallVM Release function
 *  Frees the CallVM structure. After this call, the memory is freed.
 *  @param vm Pointer on opaque CallVM structure.
 */
DC_API void      dcFree           (DCCallVM* vm);

/** Reset the argument stack.
 *  All bound values are cleared on the internal argument vector.
 *  @param vm Pointer on opaque CallVM structure.
 */
DC_API void      dcReset          (DCCallVM* vm);

#if DOXY_GROUP
/*@}*/
/** \defgroup ModeFunc Calling Convention Mode selection */
/*@{*/
#endif

/** Switch calling convention mode.
 *  @param vm Pointer on opaque CallVM structure.
 *  @param mode Integer calling convention id.
 *  @see Modes
 */
DC_API void      dcMode           (DCCallVM* vm, DCint          mode);

#if DOXY_GROUP
/*@}*/
/** \defgroup ArgFuncs Argument binding functions */
/*@{*/
#endif

/** Bind bool argument 
 *  @param vm Pointer on opaque CallVM structure.
 *  @param value bool value.
 */
DC_API void       dcArgBool       (DCCallVM* vm, DCbool        value);

/** Bind char argument 
 *  @param vm Pointer on opaque CallVM structure.
 *  @param value char value.
 */
DC_API void       dcArgChar       (DCCallVM* vm, DCchar        value);

/** Bind short integer argument 
 *  @param vm Pointer on opaque CallVM structure.
 *  @param value short integer value.
 */
DC_API void       dcArgShort      (DCCallVM* vm, DCshort       value);

/** Bind integer argument 
 *  @param vm Pointer on opaque CallVM structure.
 *  @param value integer value.
 */
DC_API void       dcArgInt        (DCCallVM* vm, DCint         value);

/** Bind long argument 
 *  @param vm Pointer on opaque CallVM structure.
 *  @param value long value.
 */
DC_API void       dcArgLong       (DCCallVM* vm, DClong        value);

/** Bind long long argument 
 *  @param vm Pointer on opaque CallVM structure.
 *  @param value long long value.
 */
DC_API void       dcArgLongLong   (DCCallVM* vm, DClonglong    value);

/** Bind float argument 
 *  @param vm Pointer on opaque CallVM structure.
 *  @param value float value.
 */
DC_API void       dcArgFloat      (DCCallVM* vm, DCfloat       value);

/** Bind double argument 
 *  @param vm Pointer on opaque CallVM structure.
 *  @param value double value.
 */
DC_API void       dcArgDouble     (DCCallVM* vm, DCdouble      value);

/** Bind pointer argument 
 *  @param vm Pointer on opaque CallVM structure.
 *  @param value pointer value.
 */
DC_API void       dcArgPointer    (DCCallVM* vm, DCpointer     value);

#if DOXY_GROUP
/*@}*/
/** \defgroup CallFuncs Call invocation functions */
/*@{*/
#endif

/** Invoke void function call
 *  @param vm Pointer on opaque CallVM structure.
 *  @param funcptr pointer on target void function.
 */
DC_API void       dcCallVoid      (DCCallVM* vm, DCpointer   funcptr);

/** Invoke bool function call
 *  @param vm Pointer on opaque CallVM structure.
 *  @param funcptr pointer on target bool function.
 *  @return bool function call result value.
 */
DC_API DCbool     dcCallBool      (DCCallVM* vm, DCpointer   funcptr);

/** Invoke char function call
 *  @param vm Pointer on opaque CallVM structure.
 *  @param funcptr pointer on target char function.
 *  @return char function call result value.
 */
DC_API DCchar     dcCallChar      (DCCallVM* vm, DCpointer   funcptr);

/** Invoke short function call
 *  @param vm Pointer on opaque CallVM structure.
 *  @param funcptr pointer on target short function.
 *  @return short function call result value.
 */
DC_API DCshort    dcCallShort     (DCCallVM* vm, DCpointer   funcptr);

/** Invoke integer function call
 *  @param vm Pointer on opaque CallVM structure.
 *  @param funcptr pointer on target integer function.
 *  @return integer function call result value.
 */
DC_API DCint      dcCallInt       (DCCallVM* vm, DCpointer   funcptr);

/** Invoke long function call
 *  @param vm Pointer on opaque CallVM structure.
 *  @param funcptr pointer on target long function.
 *  @return long function call result value.
 */
DC_API DClong     dcCallLong      (DCCallVM* vm, DCpointer   funcptr);

/** Invoke long long function call
 *  @param vm Pointer on opaque CallVM structure.
 *  @param funcptr pointer on target long long function.
 *  @return long long function call result value.
 */
DC_API DClonglong dcCallLongLong  (DCCallVM* vm, DCpointer   funcptr);


/** Invoke float function call
 *  @param vm Pointer on opaque CallVM structure.
 *  @param funcptr pointer on target float function.
 *  @return float function call result value.
 */
DC_API DCfloat    dcCallFloat     (DCCallVM* vm, DCpointer   funcptr);

/** Invoke double function call
 *  @param vm Pointer on opaque CallVM structure.
 *  @param funcptr pointer on target double function.
 *  @return double function call result value.
 */
DC_API DCdouble   dcCallDouble    (DCCallVM* vm, DCpointer   funcptr);

/** Invoke pointer function call
 *  @param vm Pointer on opaque CallVM structure.
 *  @param funcptr pointer on target pointer function.
 *  @return pointer function call result value.
 */
DC_API DCpointer  dcCallPointer   (DCCallVM* vm, DCpointer   funcptr);

#if DOXY_GROUP
/*@}*/
#endif

#ifdef __cplusplus
}
#endif

#endif /* DYNCALL_H */

