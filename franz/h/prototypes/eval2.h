/* ./eval2.c */
#ifndef EVAL2_8ced8cce9db368047b8efb8f9cbabe01_h
#define EVAL2_8ced8cce9db368047b8efb8f9cbabe01_h


#include "global.h"
extern int    *foundc;
extern long   *arglist;


extern int             dumpmydata(int thing);
extern int             xbcopy(void *to, void *from, int size);
extern int             xpopnames(struct nament *llimit);
extern struct  nament *locatevar(lispval clos, int *foundc, struct nament *rnp);
extern lispval         Ifcall(lispval a);
extern lispval         Iarray(lispval fun, lispval args, int evalp);
extern lispval         Ifclosure(lispval clos, int funcallp);


#endif
