typedef int (*fp)(int,int,int,int,int,int);

extern int f(int,int,int,int,int,int);
extern int dispatch(fp,int,int,int,int,int,int);
extern void ext();
extern void n0();
extern void n1(int a);
extern void n2(int a, int b);
extern void n4(int a, int b, int c, int d);
extern void n8(int a, int b, int c, int d, int e, int f, int g, int h);
extern void call_f0();
extern void call_f4();
extern void call_f8();

