/*                                      -[Sat Jan 29 13:32:26 1983 by jkf]-
 *      rlc.c                           $Locker:  $
 * relocator for data space
 *
 * (c) copyright 1982, Regents of the University of California
 */

#include <assert.h>

#define TRUE 1
#include "h/global.h"
#if vax_4_2 | vax_4_3 | tahoe_4_3
#define brk(p) syscall(17, p)
#endif
extern char  holend[], end[];
extern int   usehole;
extern char *curhbeg;

void rlc(void)
{
#if STILL_PORTING  
  VERIFY_STILL_PORTING("need to implement this in modern C");
#else
  VERIFY_NOT_PORTING("need to implement this in modern C");
  _Static_assert(0, "need to implement this in modern C");
  char *cp, *dp;

  brk(end);
  dp = holend;
  cp = dp - HOLE;
  while (dp < end)
    *dp++ = *cp++;
  curhbeg = holend - HOLE; /* set up the hole */
  usehole = TRUE;
#endif
}
