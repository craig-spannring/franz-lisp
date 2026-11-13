
#include "stubs.h"

#include "global.h"
#include "frame.h"


#include <assert.h>

char     holbeg[1];
char     holend[1];
char     _sobuf[1];
char     etext[1];
lispval *tynames[1];
char     _erthrow[1];


int Imuldiv(long p1, long p2, long add, long dv, long *quo, long *rem)
{
  TODO_FIX("Not implemented yet");
  return 0;
}

lispval LIshowstack(void)
{
  TODO_FIX("Not implemented yet");
  return 0;
}

lispval Lbaktrace(void)
{
  TODO_FIX("Not implemented yet");
  return 0;
}

lispval Lmkcth(void)
{
  TODO_FIX("Not implemented yet");
  return 0;
}

lispval Lpolyev(void)
{
  TODO_FIX("Not implemented yet");
  return 0;
}

lispval Lrot(void)
{
  TODO_FIX("Not implemented yet");
  return 0;
}

lispval Lshostk(void)
{
  TODO_FIX("Not implemented yet");
  return 0;
}

lispval adbig(lispval a, lispval b)
{
  TODO_FIX("Not implemented yet");
  return 0;
}

int blzero(void *where, int howmuch)
{
  TODO_FIX("Not implemented yet");
  return 0;
}

int calqhat(long *uj, long *v1)
{
  TODO_FIX("Not implemented yet");
  return 0;
}

void dmlad(lispval sdot, long, long add)
{
  TODO_FIX("Not implemented yet");
}

long dodiv(long *top, long *bottom)
{
  TODO_FIX("Not implemented yet");
  return 0;
}

int dsadd1(long *top, long *bot)
{
  TODO_FIX("Not implemented yet");
  return 0;
}

long dsdiv(long *top, long *bot, long div)
{
  TODO_FIX("Not implemented yet");
  return 0;
}

int dsmult(long *top, long *bot, long mul)
{
  TODO_FIX("Not implemented yet");
  return 0;
}

long dsneg(long *top, long *bottom)
{
  TODO_FIX("Not implemented yet");
  return 0;
}

long dsrsh(long *top, long *bot, long ncnt, long mask1)
{
  TODO_FIX("Not implemented yet");
  return 0;
}

long exarith(int mul1, int mul2, long add, long *hi, long *lo)
{
  TODO_FIX("Not implemented yet");
  return 0;
}

int gstart(void)
{
  TODO_FIX("Not implemented yet");
  return 0;
}

lispval inewint(void *n)
{
  TODO_FIX("Not implemented yet");
  return 0;
}

int mcount(void)
{
  TODO_FIX("Not implemented yet");
  return 0;
}

long mlsb(long *utop, long *ubot, long *vtop, int nqhat)
{
  TODO_FIX("Not implemented yet");
  return 0;
}

int mmuladd(long a, long b, long c, long m)
{
  TODO_FIX("Not implemented yet");
  return 0;
}

lispval mulbig(lispval, lispval)
{
  TODO_FIX("Not implemented yet");
  return 0;
}

int nargs(void)
{
  TODO_FIX("Not implemented yet");
  return 0;
}

int prunei(lispval what)
{
  TODO_FIX("Not implemented yet");
  return 0;
}

lispval qcons(void)
{
  TODO_FIX("Not implemented yet");
  return 0;
}

lispval qget(void)
{
  TODO_FIX("Not implemented yet");
  return 0;
}

lispval qlinker(lispval, int *)
{
  TODO_FIX("Not implemented yet");
  return 0;
}

int qnewdoub(void)
{
  TODO_FIX("Not implemented yet");
  return 0;
}

int qoneplus(void)
{
  TODO_FIX("Not implemented yet");
  return 0;
}

int qnewint(void)
{
  TODO_FIX("Not implemented yet");
  return 0;
}

int qoneminus(void)
{
  TODO_FIX("Not implemented yet");
  return 0;
}

int qpushframe(void)
{
  TODO_FIX("Not implemented yet");
  return 0;
}

void qretfromfr(void)
{
  TODO_FIX("Not implemented yet");
}

int callg_(lispval (*funct)(/* TODO- figure out the parameters and types */), int *arglist)
{
  TODO_FIX("Not implemented yet");
  return 0;
}

long adback(long *utop, long *ubot, long *vtop)
{
  TODO_FIX("Not implemented yet");
  return 0;
}

struct frame *Ipushf(int a, lispval b, lispval c, struct pframe *d)
{
  TODO_FIX("Not implemented yet");
  return 0;
}


void *lToVP(long l)
{
  TODO_FIX("This function should be removed.");
  return NULL;
}

void *iToVP(int i)
{
  TODO_FIX("This function should be removed.");
  return NULL;
}


