/* ./sysat.c */
#ifndef SYSAT_cf308f3911cc8627acaba5e56af6b82a_h
#define SYSAT_cf308f3911cc8627acaba5e56af6b82a_h

#include "global.h"

struct ftab
{
  char     *string;
    lispval (*start)(); 
  lispval  *discip;
};


extern long int tint[2 * NUMSPACES];
extern int      makevals(void);
/* static struct ftab cfuns[]; */
/* static dofuns(void); */


extern lispval matom(char *string);
extern lispval mstr(char *string);
extern lispval mfun(char *string, lispval (*start)(), lispval discip);
extern lispval mftab(struct ftab *table);

#endif
