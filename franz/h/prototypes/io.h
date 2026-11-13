/* ./io.c */
#ifndef IO_644fbff78c6d90ab6e738ceac4793ff6_h
#define IO_644fbff78c6d90ab6e738ceac4793ff6_h

#include "global.h"

#include "prototypes/error.h"

#include <stdio.h>


extern struct readtable initread;
extern int              keywait;
extern int              plevel;
extern int              plength;
extern void             macrox(void);
extern void             imacrox(lispval current, int inlist);

extern int              Iratom(void);
extern char            *strbuf;
extern char            *atomtoolong(char *copyto);
extern void             lfltpr(char *buf, double val);
                       
extern void             printr(lispval a, FILE *useport);
extern void             dmpport(FILE *useport);
extern lispval          readrx(int code);
extern lispval          readr(FILE *useport);
extern lispval          ratomr(FILE *useport);
extern lispval          getnum(char *name);
extern lispval          dopow(char *part2, int base);
extern lispval          calcnum(char *strbuf, char *name, int base);
extern lispval          finatom(char *name);
extern int              vectorpr(lispval vec, FILE *port);

    
#endif
