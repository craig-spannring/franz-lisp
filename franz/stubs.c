#include "structs.h"
#include "frame.h"

#include "stubs.h"

#include <assert.h>


char    holbeg[];
char    holend[];
char    _sobuf[];
char    etext[];
lispval *tynames[];
char    _erthrow[];


int Imuldiv(long p1, long p2, long add, long dv, long *quo, long *rem)
{
   assert(0);
   return 0;
}

lispval LIshowstack(void)
{
   assert(0);
   return 0;
}

lispval Lbaktrace(void)
{
   assert(0);
   return 0;
}

lispval Lmkcth(void)
{
   assert(0);
   return 0;
}

lispval Lpolyev(void)
{
   assert(0);
   return 0;
}

lispval Lrot(void)
{
   assert(0);
   return 0;
}

lispval Lshostk(void)
{
   assert(0);
   return 0;
}

lispval adbig(lispval, lispval)
{
   assert(0);
   return 0;
}

int blzero(void *where, int howmuch)
{
   assert(0);
   return 0;
}

int calqhat(register long *uj, register long *v1)
{
   assert(0);
   return 0;
}

void         dmlad(lispval sdot, long, long add)
{
   assert(0);
}

long dodiv(long *top, long *bottom)
{
   assert(0);
   return 0;
}

int dsadd1(long *top, long *bot)
{
   assert(0);
   return 0;
}

long dsdiv(long *top, long *bot, long div)
{
   assert(0);
   return 0;
}

int dsmult(long *top, long *bot, long mul)
{
   assert(0);
   return 0;
}

long dsneg(long *top, long *bottom)
{
   assert(0);
   return 0;
}

long dsrsh(long *top, long *bot, long ncnt, long mask1)
{
   assert(0);
   return 0;
}

long exarith(int mul1, int mul2, long add, long *hi, long *lo)
{
   assert(0);
   return 0;
}

int          gstart(void)
{
   assert(0);
   return 0;
}

lispval inewint (int n)
{
   assert(0);
   return 0;
}

int          mcount(void)
{
   assert(0);
   return 0;
}

long mlsb(long *utop, long *ubot, long *vtop, int nqhat)
{
   assert(0);
   return 0;
}

int          mmuladd(long a, long b, long c, long m)
{
   assert(0);
   return 0;
}

lispval mulbig(lispval, lispval)
{
   assert(0);
   return 0;
}

int          nargs(void)
{
   assert(0);
   return 0;
}

int          prunei(register lispval what)
{
   assert(0);
   return 0;
}

lispval qcons(void)
{
   assert(0);
   return 0;
}

lispval qget(void)
{
   assert(0);
   return 0;
}

lispval qlinker(lispval, int*)
{
   assert(0);
   return 0;
}

int          qnewdoub(void)
{
   assert(0);
   return 0;
}

int          qoneplus(void)
{
   assert(0);
   return 0;
}

int          qnewint(void)
{
   assert(0);
   return 0;
}

int          qoneminus(void)
{
   assert(0);
   return 0;
}

int          qpushframe(void)
{
   assert(0);
   return 0;
}

void qretfromfr(void)
{
   assert(0);
}

int callg_(lispval (*funct)(int, ...), int *arglist)
{
   assert(0);
   return 0;
}

long adback(long *utop, long *ubot, long *vtop)
{
   assert(0);
   return 0;
}

struct frame *Ipushf(int,lispval,lispval,struct pframe*)
{
   assert(0);
   return 0;
}

