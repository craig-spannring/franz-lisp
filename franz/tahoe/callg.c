/*
 * callg_ - call with 'general' argument list for CCI `tahoe'
 *
 * by P. S. Housel 04/30/86
 *
 */

int 
callg_ (
    register int (*funct)(void),                /* r12 */
    register int *arglist                  /* r11 */
)
{
 register int *argptr, n;               /* r10, r9 */

 n = (*arglist + 1) * 4;

 argptr = arglist + *arglist;

 while(argptr > arglist)
      {asm("pushl       (r10)");
       argptr--;
      }
 
 asm("  calls   r9,(r12)");
}
