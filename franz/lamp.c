/*                                      -[Tue Mar 22 15:17:09 1983 by jkf]-
 *      lamp.c                          $Locker:  $
 * interface with unix profiling
 *
 * (c) copyright 1982, Regents of the University of California
 */

#include "prototypes/lamp.h"
#include "prototypes/error.h"
#include "prototypes/io.h"

#include "global.h"

#ifdef PROF

#define PBUFSZ 500000
short pbuf[PBUFSZ];

/* data space for fasl to put counters */
int mcnts[NMCOUNT];
int mcntp  = (int)mcnts;
int doprof = TRUE;

lispval Lmonitor(void)
{
  extern etext, countbase;

  if (np == lbot)
  {
    monitor((int (*)())0);
    countbase = 0;
  }
  else if (TYPE(lbot->val) == INT)
  {
    monitor((int (*)())2, (int (*)())lbot->val->i, pbuf, PBUFSZ * (sizeof(short)), 7000);
    countbase = ((int)pbuf) + 12;
  }
  else
  {
    monitor((int (*)())2, (int (*)())sbrk(0), pbuf, PBUFSZ * (sizeof(short)), 7000);
    countbase = ((int)pbuf) + 12;
  }
  return (tatom);
}

#else

/* if prof is not defined, create a dummy Lmonitor */

short pbuf[8];

/* data space for fasl to put counters */
int  mcnts[1] = {0};
int *mcntp    = mcnts;
int  doprof   = FALSE;

lispval Lmonitor(void)
{
  error("Profiling not enabled", FALSE);
}

#endif
