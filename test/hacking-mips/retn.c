#define DEF_RETN(N) int ret##N(int a0, int a1, int a2, int a3, int a4, int a5) { return a##N; }

DEF_RETN(0)
DEF_RETN(1)
DEF_RETN(2)
DEF_RETN(3)
DEF_RETN(4)
DEF_RETN(5)

