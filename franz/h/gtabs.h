/*					-[Sat Jan 29 13:57:36 1983 by jkf]-
 * 	gtabs.h				$Locker:  $
 * global lispval table
 *
 * $Header: /na/franz/franz/h/gtabs.h,v 1.1 83/01/29 14:06:37 jkf Exp $
 *
 * (c) copyright 1982, Regents of the University of California
 */
#ifndef GTABS_6c339ced3758f12a1507f26afbab1061_h
#define GTABS_6c339ced3758f12a1507f26afbab1061_h



/*  these are the tables of global lispvals known to the interpreter	*/
/*  and compiler.  They are not used by the garbage collector.		*/
#define GFTABLEN 200
#define GCTABLEN 8
extern lispval gftab[GFTABLEN];
extern lispval gctab[GCTABLEN];

#endif
