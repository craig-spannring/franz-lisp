/* ./alloc.c */
#ifndef ALLOC_e03ca4903c3680ce69cd3d3422d2ddc8_h
#define ALLOC_e03ca4903c3680ce69cd3d3422d2ddc8_h

#include "config.h"
#include "global.h"

#define NUMWORDS TTSIZE * 128 /*  max number of words in P0 space  */
#define BITQUADS TTSIZE * 2   /*  length of bit map in quad words  */
#define BITLONGS TTSIZE * 4   /*  length of bit map in long words  */

extern int              debugin;
extern int              bitmapi[BITLONGS];
extern double           zeroq;
extern char            *bbitmap;
extern double          *qbitmap;
extern int              bitmsk[32];
extern struct types    *gcableptr[];
extern long             npages;
extern int              printall;

extern lispval          alloc(lispval tname, long npages);
extern int              get_more_space(struct types *type_struct, int purep);
extern int              space_warn(int g);
extern lispval          getatom(int purep);
extern struct atom     *newatom(int pure);
extern lispval          inewatom(char *name);
extern lispval          inewval(lispval arg);
extern char            *newstr(int purep);
extern char            *inewstr(char *s);
extern char            *pinewstr(char *s);
extern int              gc1(void);
extern char            *gethspace(int segsiz, int type);
extern int              gcrebear(void);
extern char            *xsbrk(int n);
extern char            *ysbrk(int pages, int type);
extern int              hashfcn(char *symb);
extern int              myhook(void);
extern void             pruneb(lispval bignum);
extern int              csizeof(lispval tname);
extern int              typenum(lispval tname);
extern lispval          getvec(int size, struct types *typestr, int purep);
extern void             markdp(lispval p);
extern lispval          newvec(int size);
extern lispval          nveci(int size);

extern lispval          Ipurep(lispval element);

#endif
