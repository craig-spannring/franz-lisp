/*                                      -[Sat Jan 29 13:24:33 1983 by jkf]-
 *      lisp.c                          $Locker:  $
 * main program
 *
 * (c) copyright 1982, Regents of the University of California
 */

#include "prototypes/inits.h"
#include "prototypes/io.h"
#include "prototypes/eval.h"
#include "prototypes/sysat.h"
#include "prototypes/frame.h"
#include "prototypes/fex4.h"
#include "lfuncs.h"


#include "global.h"
#include "frame.h"

#include <unistd.h>
#include <stdlib.h>

#include "stubs.h"



/* main *****************************************************************/
/* Execution of the lisp system begins here.  This is the top level     */
/* executor which is an infinite loop.  The structure is similar to     */
/* error.                                                               */

extern lispval reborn;
extern int     rlevel;
static int     virgin = 0;
int            Xargc;
char         **Xargv;
extern char  **environ;

int main(int argc, char **argv, char **arge)
{
  lispval              Lapply();
  extern struct frame *errp;
  pbuf                 pb;

  environ = arge;
#if sun_4_2 || sun_4_2beta
  setlinebuf(stdout);
#else
  {
    extern char _sobuf[];
    setbuf(stdout, _sobuf);
  }
#endif
  Xargc  = argc;
  Xargv  = argv;
  virgin = 0;
  errp   = (struct frame *)0;
  initial();

  errp = Pushframe(F_RESET, nil, nil);
  switch (retval)
  {
    case C_RESET:   break; /* what to do? */
    case C_INITIAL: break; /* first time  */
  }

  for (EVER)
  {
    lbot = np = orgnp;
    rlevel    = 0;
    depth     = 0;
    clearerr(piport = stdin);
    clearerr(poport = stdout);
    np++->val = matom("top-level");
    np++->val = nil;
    Lapply();
  }
}

lispval Ntpl(void)
{
  lispval Lread();

  if (virgin == 0)
  {
    fputs((char *)Istsrch(matom("version"))->d.cdr->d.cdr->d.cdr, poport);
    virgin = 1;
  }
  lbot      = np;
  np++->val = P(stdin);
  np++->val = eofa;
  while (TRUE)
  {
    fputs("\n-> ", stdout);
    dmpport(stdout);
    vtemp = Lread();
    if (vtemp == eofa) exit(0);
    printr(eval(vtemp), stdout);
  }
}

/* franzexit :: give up the ghost
 * this function is called whenever one decides to kill this process.
 * We clean up a bit then call then standard exit routine.  C code
 * in franz should never call exit() directly.
 */
int franzexit(int code)
{
  extern int   fvirgin;
  extern char *stabf;
  if (!fvirgin) unlink(stabf); /* give up any /tmp symbol tables */
  exit(code);
  /* is this something special??  _cleanup();
   *                              proflush();
   *                              _exit(code);
   */
}
