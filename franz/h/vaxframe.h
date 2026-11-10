/*					-[Sat Jan 29 14:02:34 1983 by jkf]-
 * 	vaxframe.h			$Locker:  $
 * vax calling frame definition
 *
 * $Header: vaxframe.h,v 1.3 84/02/29 15:06:57 sklower Exp $
 *
 * (c) copyright 1982, Regents of the University of California
 */
#ifndef VAXFRAME_dab91188139bc49e58177d3830cd920f_h
#define VAXFRAME_dab91188139bc49e58177d3830cd920f_h



struct machframe
{
  lispval (*handler)();
  long              mask;
  lispval          *ap;
  struct machframe *fp;
  lispval (*pc)();
  lispval *r6;
  lispval *r7;
};

#endif
