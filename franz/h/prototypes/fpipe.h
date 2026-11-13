/* ./fpipe.c */
#ifndef FPIPE_c11c6d8cb2f6a942658a0d14734b1ce8_h
#define FPIPE_c11c6d8cb2f6a942658a0d14734b1ce8_h

#include "global.h"

#include <stdio.h>


extern char    *flag;
extern char    *alloconstack(int howmuch);

extern lispval  P(FILE *p);
extern FILE    *fstopen(char *base, int count, char *flag);
extern FILE    *fpipe(FILE *info[2]);

#endif
