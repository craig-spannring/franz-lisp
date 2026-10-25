#ifndef STUBS_a5cc0adf90fa1d41bd52eaf166bc83d4_h
#define STUBS_a5cc0adf90fa1d41bd52eaf166bc83d4_h

extern char    holbeg[];
extern char    holend[];
extern char    _sobuf[];
extern char    etext[];
extern lispval *tynames[];
extern char    _erthrow[];


extern int          Imuldiv(long p1, long p2, long add, long dv, long *quo, long *rem);
extern lispval      LIshowstack(void);
extern lispval      Lbaktrace(void);
extern lispval      Lmkcth(void);
extern lispval      Lpolyev(void);
extern lispval      Lrot(void);
extern lispval      Lshostk(void);
extern lispval      adbig(lispval, lispval);
extern lispval      subbig(lispval, lispval);
extern lispval      mulbig(lispval, lispval);
extern int          blzero(void *where, int howmuch);
extern int          calqhat(register long *uj, register long *v1);
extern void         dmlad(lispval sdot, long, long add);
extern long         dodiv(long *top, long *bottom);
extern int          dsadd1(long *top, long *bot);
extern long         dsdiv(long *top, long *bot, long div);
extern int          dsmult(long *top, long *bot, long mul);
extern long         dsneg(long *top, long *bottom);
extern long         dsrsh(long *top, long *bot, long ncnt, long mask1);
extern long         exarith(int mul1, int mul2, long add, long *hi, long *lo);
extern int          gstart(void);
extern lispval      inewint (int n);
extern int          mcount(void);
extern long         mlsb(long *utop, long *ubot, long *vtop, int nqhat);
extern int          mmuladd(long a, long b, long c, long m);
extern int          nargs(void);
extern int          prunei(register lispval what);
extern lispval      qcons(void);
extern lispval      qget(void);
extern lispval      qlinker(lispval, int*);
extern int          qnewdoub(void); 
extern int          qoneplus(void); 
extern int          qnewint(void);
extern int          qoneminus(void); 
extern int          qpushframe(void);
extern void         qretfromfr(void);                    
extern int          callg_(lispval (*funct)(int, ...), int *arglist);
extern long         adback(long *utop, long *ubot, long *vtop);
struct Foo{}; 
extern struct frame *Ipushf(int,lispval,lispval,struct pframe*);

#endif
