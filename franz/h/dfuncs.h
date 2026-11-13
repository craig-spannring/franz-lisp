/*					-[Sat Jan 29 13:54:30 1983 by jkf]-
 * 	dfuncs.h			$Locker:  $
 * external function declaration
 *
 * $Header: dfuncs.h,v 1.2 84/02/29 17:09:10 sklower Exp $
 *
 * (c) copyright 1982, Regents of the University of California
 */
#ifndef DFUNCS_68f33c80330fca7e62f06a943413f710_h
#define DFUNCS_68f33c80330fca7e62f06a943413f710_h


#include "prototypes/alloc.h"

#include <stdio.h>


extern char        *getsp();
// char        *pinewstr();
// char        *inewstr();
extern char        *mkmsg();
// char        *newstr();
extern char        *rstore();
// char        *xsbrk();
// char        *ysbrk();
// extern int          csizeof();
extern int          finterp();
extern lispval      Iget(lispval atm, lispval ind);
// extern lispval      Imkrtab();
// extern lispval      Iputprop();
// extern lispval      Lfuncal();
// extern lispval      Lnegp();
// extern lispval      Lsub();
// // extern lispval      alloc();
// extern lispval      copval(lispval val, lispval value);
extern lispval      csegment(int typecode, int nitems, int useholeflag);
// lispval      error();
// extern lispval      errorh();
// extern lispval      errorh1();
// extern lispval      errorh2();
// extern lispval      eval();
// extern lispval      gc(struct types *ts);
// extern lispval      getatom();
// extern lispval      inewval();
extern lispval      linterp();
// extern lispval      matom(char *string);
// extern lispval      mfun();
// extern lispval      mstr();
extern lispval      newarray();
extern lispval      newdot();
extern lispval      newdoub();
extern lispval      newfunct();
extern lispval      newint();
extern lispval      newsdot();
extern lispval      newval();
extern lispval      newhunk(int hunknum);
extern lispval      pnewdot();
extern lispval      pnewdb();
extern lispval      pnewhunk(int hunknum);
extern lispval      pnewint();
extern lispval      pnewsdot();
extern lispval      pnewval();
// extern lispval      popnames();
// extern lispval      r();
// extern lispval ratomr(FILE *useport);

// extern lispval      readr();
// extern lispval      readrx();
extern lispval      readry();
// extern lispval      typred();
extern lispval      unprot();
// extern lispval      verify();
// struct atom *newatom();

#endif
