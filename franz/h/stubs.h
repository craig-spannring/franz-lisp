#ifndef STUBS_a5cc0adf90fa1d41bd52eaf166bc83d4_h
#define STUBS_a5cc0adf90fa1d41bd52eaf166bc83d4_h

#include "frame.h"
#include "global.h"

#if STILL_PORTING
#include <assert.h>
#else
static_assert(0, "this file should go away.");
#endif

#if USES_MACHO_OBJ_FMT
  #include <mach-o/nlist.h>
#elif USES_ELF64_OBJ_FMT
  #warning "need to handle ELF64"
#elif USES_ELF32_OBJ_FMT
  #warning "need to handle ELF32"
#elif USES_COFF_OBJ_FMT
  #warning "need to handle COFF"
#endif 


extern void _fwalk(int (*function)(FILE*)); 

extern char     holbeg[];
extern char     holend[];
extern char     _sobuf[];
extern char     etext[];
extern lispval *tynames[];
extern char     _erthrow[];


/**
        myfrexp returns three values, exp, hi, lo,
        Such that value = 2**exp*tmp, where tmp = (hi*2**-23+lo*2**-53)
        is uniquely determined subect to .5< abs(tmp) <= 1.0
 */
extern double myfrexp (double value, double *exp, double *hi, double *lo);

extern int           Imuldiv(long p1, long p2, long add, long dv, long *quo, long *rem);
// extern lispval       LIshowstack(void);
extern lispval       Lbaktrace(void);
// extern lispval       Lmkcth(void);
extern lispval       Lpolyev(void);
// extern lispval       Lrot(void);
// extern lispval       Lshostk(void);
extern lispval       adbig(lispval, lispval);
extern lispval       subbig(lispval, lispval);
extern lispval       mulbig(lispval, lispval);
extern int           blzero(void *where, int howmuch);
extern int           calqhat(long *uj, long *v1);
extern void          dmlad(lispval sdot, long, long add);
extern long          dodiv(long *top, long *bottom);
extern int           dsadd1(long *top, long *bot);
extern long          dsdiv(long *top, long *bot, long div);
extern int           dsmult(long *top, long *bot, long mul);
extern long          dsneg(long *top, long *bottom);
extern long          dsrsh(long *top, long *bot, long ncnt, long mask1);
extern long          exarith(int mul1, int mul2, long add, long *hi, long *lo);
extern int           gstart(void);
extern lispval       inewint(void *n);
extern int           mcount(void);
extern long          mlsb(long *utop, long *ubot, long *vtop, int nqhat);
extern int           mmuladd(long a, long b, long c, long m);
extern int           nargs(void);
extern int           prunei(lispval what);
extern lispval       qcons(void);
extern lispval       qget(void);
extern lispval       qlinker(lispval, int *);
extern int           qnewdoub(void);
extern int           qoneplus(void);
extern int           qnewint(void);
extern int           qoneminus(void);
extern int           qpushframe(void);
extern void          qretfromfr(void);
extern int           callg_(lispval (*funct)(void), int *arglist);
extern long          adback(long *utop, long *ubot, long *vtop);

extern void*         lToVP(long l); // convert long to a void*  
extern void*         iToVP(int i);  // convert int to a void*   

#if STILL_PORTING
#define TODO_FIX(s)  do { int todoFix; assert(0); } while(0)
#else
#define TODO_FIX(s)  static_assert(0, s)
#endif

#endif
