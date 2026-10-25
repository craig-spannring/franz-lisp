/*                                      -[Sat Jan 29 13:54:30 1983 by jkf]-
 *      dfuncs.h                        $Locker:  $
 * external function declaration
 *
 * $Header: dfuncs.h,v 1.2 84/02/29 17:09:10 sklower Exp $
 *
 * (c) copyright 1982, Regents of the University of California
 */

#include <unistd.h>

extern void qretfromfr(void);

extern long dodiv(long *top, long *bottom);
extern long dsneg(long *top, long *bottom);

extern int mmuladd(long a, long b, long c, long m);
extern int gstart();
typedef lispval (*callg_fx)(int, ...);
extern int callg_(lispval (*funct)(int, ...), int *arglist);

/* mlsb.c */
extern long mlsb(long *utop, long *ubot, long *vtop, int nqhat);
extern long adback(long *utop, long *ubot, long *vtop);
extern long dsdiv(long *top, long *bot, long div);
extern int  dsadd1(long *top, long *bot);
extern long dsrsh(long *top, long *bot, long ncnt, long mask1);

/* dsmult.c */
extern int dsmult(long *top, long *bot, long mul);

/* calqhat.c */
extern int calqhat(register long *uj, register long *v1);

// char *getsp();
// char *pinewstr();
// char *inewstr();
// char *mkmsg();
// char *newstr();
// char *rstore();
// char *xsbrk();
// char *ysbrk();
// int csizeof();
// int finterp();
// lispval Iget();
// lispval Imkrtab();
// lispval Iputprop();
// lispval Lfuncal();
// lispval Lnegp();
// lispval Lsub();
// lispval alloc();
extern lispval copval(lispval option, lispval value);
// lispval csegment();
// lispval error();
// lispval errorh();
// lispval errorh1();
// lispval errorh2();
// lispval eval();
// lispval gc();
// lispval getatom(int);
// lispval inewval();
// lispval linterp();
// lispval matom();
// lispval mfun();
// lispval mstr();
// lispval newarray();
// lispval newdot();
// lispval newdoub();
// lispval newfunct();
// lispval newint();
// lispval newsdot();
// lispval newval();
// lispval newhunk();
// lispval pnewdot();
// lispval pnewdb();
// lispval pnewhunk();
// lispval pnewint();
// lispval pnewsdot();
// lispval pnewval();
// lispval popnames();
// lispval r();
// lispval ratomr();
// lispval readr();
// lispval readry();
// lispval typred();
// lispval unprot();
// lispval verify();
// struct atom * newatom();
