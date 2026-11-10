/* ./stubs.c */
#ifndef STUBS_1448669f13c97bec18c1b2081484e1ea_h
#define STUBS_1448669f13c97bec18c1b2081484e1ea_h

extern char holbeg[];
extern char holend[];
extern char _sobuf[];
extern char etext[];
extern char _erthrow[];
extern int  Imuldiv(long p1, long p2, long add, long dv, long *quo, long *rem);
extern int  blzero(void *where, int howmuch);
extern int  calqhat(long *uj, long *v1);
extern long dodiv(long *top, long *bottom);
extern int  dsadd1(long *top, long *bot);
extern long dsdiv(long *top, long *bot, long div);
extern int  dsmult(long *top, long *bot, long mul);
extern long dsneg(long *top, long *bottom);
extern long dsrsh(long *top, long *bot, long ncnt, long mask1);
extern long exarith(int mul1, int mul2, long add, long *hi, long *lo);
extern int  gstart(void);
extern int  mcount(void);
extern long mlsb(long *utop, long *ubot, long *vtop, int nqhat);
extern int  mmuladd(long a, long b, long c, long m);
extern int  nargs(void);
extern int  qnewdoub(void);
extern int  qoneplus(void);
extern int  qnewint(void);
extern int  qoneminus(void);
extern int  qpushframe(void);
extern void qretfromfr(void);
extern long adback(long *utop, long *ubot, long *vtop);

#endif
