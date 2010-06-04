typedef int i;
typedef float f;
typedef double d;
void _();
void _iiiiii(i,i,i,i,i,i);
void _ffffff(f,f,f,f,f,f);
void _dddddd(d,d,d,d,d,d);
void _ifffff(i,f,f,f,f,f);
void _iddddd(i,d,d,d,d,d);
void _fdidfd(f,d,i,d,f,d);
void _ddidfd(d,d,i,d,f,d);
void _ididfd(i,d,i,d,f,d);
int    ai[] = { 0   , 1   , 2   , 3   , 4   , 5    };
float  af[] = { 0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f }; 
double ad[] = { 0.0 , 1.0 , 2.0 , 3.0 , 4.0 , 5.0  };

void call_()       { _(); }
void call_iiiiii() { _iiiiii(ai[0],ai[1],ai[2],ai[3],ai[4],ai[5]); }
void call_ffffff() { _ffffff(af[0],af[1],af[2],af[3],af[4],af[5]); }
void call_dddddd() { _dddddd(ad[0],ad[1],ad[2],ad[3],ad[4],ad[5]); }
void call_ifffff() { _ifffff(ai[0],af[1],af[2],af[3],af[4],af[5]); } 
void call_iddddd() { _iddddd(ai[0],ad[1],ad[2],ad[3],ad[4],ad[5]); }
void call_fdidfd() { _fdidfd(1.0f,2.0, 3   ,4.0, 5.0f,6.0 ); }
void call_ddidfd() { _ddidfd(1.0, 2.0, 3   ,4.0, 5.0f,6.0 ); }
void call_ididfd() { _ididfd(1  , 2.0, 3   ,4.0, 5.0f,6.0 ); }

