gcc -E -P -DGEN_MASM dyncall_call_x86.S >dyncall_call_x86_generic_masm.asm
gcc -E -P -DGEN_MASM dyncall_call_x64.S >dyncall_call_x64_generic_masm.asm

