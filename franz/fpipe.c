#ifndef lint
static char *rcsid = "$Header: fpipe.c,v 1.3 85/05/22 07:53:41 sklower Exp $";
#endif

/*                                      -[Sat Jan 29 12:44:16 1983 by jkf]-
 *      fpipe.c                         $Locker:  $
 * pipe creation
 *
 * (c) copyright 1982, Regents of the University of California
 */

#include "prototypes/fpipe.h"
#include "prototypes/alloc.h"
#include "prototypes/error.h"

#include "global.h"
#include <signal.h>
#include <stdlib.h>

FILE *fpipe(info)
FILE *info[2];
{
  register FILE *p;
  int            fd[2];

  if (0 > pipe(fd)) return ((FILE *)-1);

  if (NULL == (p = fdopen(fd[0], "r")))
  {
    close(fd[0]);
    close(fd[1]);
    return ((FILE *)-1);
  }
  info[0] = p;
  if (NULL == (p = fdopen(fd[1], "w")))
  {
    close(fd[0]);
    close(fd[1]);
    return ((FILE *)-1);
  }
  info[1] = p;

  return ((FILE *)2); /*indicate sucess*/
}
/* Nioreset *************************************************************/

lispval Nioreset(void)
{
#if !IGNORE_STATIC_ASSERT
  _Static_assert(0, "need a portable way of doing this")
#if !RTPORTS
      register FILE *p;

  for (p = &_iob[3]; p < _iob + _NFILE; p++)
  {
    if (p->_flag & (_IOWRT | _IOREAD)) fclose(p);
  }
#else
      lispval NiorUtil();

  _fwalk(NiorUtil);
#endif RTPORTS
#endif
  return (nil);
}

#if RTPORTS
FILE FILEdummy;

static lispval NiorUtil(p)
FILE          *p;
{
  lispval handy;
  if (p == stdin || p == stdout || p == stderr) return (0);
  fclose(p);
  handy = P(p);
  if (TYPE(handy) == PORT)
  {
    handy->p = &FILEdummy;
  }
  return (nil);
}
FILE **xports;

#define LOTS (LBPG / (sizeof(FILE *)))
lispval P(p)
FILE   *p;
{
  register FILE **q;
  extern int      fakettsize;

  if (xports == ((FILE **)0))
  {
    /* this is gross.  I don't want to change csegment -- kls */
    xports = (FILE **)csegment(OTHER, LOTS, 0);
    SETTYPE(xports, PORT, 31);
    for (q = xports; q < xports + LOTS; q++)
    {
      *q = &FILEdummy;
    }
  }
  for (q = xports; q < xports + LOTS; q++)
  {
    if (*q == p) return ((lispval)q);
    if (*q == &FILEdummy)
    {
      *q = p;
      return ((lispval)q);
    }
  }
  /* Heavens above knows this could be disasterous in makevals() */
  error("Ran out of Ports", FALSE);
}

#endif RTPORTS

FILE *fstopen(char *base, int count, char *flag)
// char *base;
// char *flag;
{
  FILE *p = fdopen(0, flag);
#if !IGNORE_STATIC_ASSERT
  _Static_assert(0, "need to write this in a portable manner");

  p->_flag |= _IOSTRG;
  p->_cnt = count;
  p->_ptr = p->_base = base;
  p->_file           = -1;
#endif
  return (p);
}

#if !IGNORE_STATIC_ASSERT
_Static_assert(0, "think through the memory layouts and allocations");

#ifdef SPISFP
char *alloca(register int howmuch)
{
#if !IGNORE_STATIC_ASSERT
  _Static_assert(0, "We should be able to use the standard library here.");
#endif
  howmuch += 3;
  howmuch >>= 2;
  xsp -= howmuch;
  if (xsp < xstack)
  {
    xsp += howmuch;
    xserr();
  }
  return ((char *)xsp);
}
#endif
#endif
