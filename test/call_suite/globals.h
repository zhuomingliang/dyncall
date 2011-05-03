#include "config.h"

extern const char      *K_c;
extern const short     *K_s;
extern const int       *K_i;
extern const long      *K_j;
extern const long long *K_l;
extern void* const     *K_p;
extern const float     *K_f;
extern const double    *K_d;

extern char      *V_c;
extern short     *V_s;
extern int       *V_i;
extern long      *V_j;
extern long long *V_l;
extern void*     *V_p;
extern float     *V_f;
extern double    *V_d;

extern void      *G_callvm;
typedef void (*funptr)();
/*
extern funptr    *T;
*/

void init_K();
void init_T();
void clear_V();
int  invoke(char const* signature, void* target);
