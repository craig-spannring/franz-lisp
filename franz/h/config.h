/*					-[Thu Mar  3 15:57:51 1983 by jkf]-
 * 	config.h			$Locker:  $
 * configuration dependent info
 *
 * $Header: config.h,v 1.16 87/12/14 18:33:31 sklower Exp $
 *
 * (c) copyright 1982, Regents of the University of California
 */
 
/* 
 * this file contains parameters which each site is likely to modify
 * in order to personalize the configuration of Lisp at their site.
 * The typical things to modifiy are:
 *    [optionally] turn on GCSTRINGS
 *    [optionally] provide a value for SITE 
 */

/*
 * The type of machine and os this is to run on will come from
 * the file lconf.h.  The lconf.h file is created by the shell script
 * 'lispconf' in the directory ../..
 * lconf.h will define exactly one of these symbols:
 *  vax_4_2 vax_4_1c vax_4_1a vax_4_1 vax_unix_ts vax_eunice_vms
 *  sun_4_2 sun_4_1c sun_unisoft dual_unisoft pixel_unisoft lisa_unisys3
 *  mc500_2_0
 */
// #include "lconf.h"


/* GCSTRINGS - define this if you want the garbage collector to reclaim
 *  strings.  It is not normally set because in typical applications the
 *  expense of collecting strings is not worth the amount of space
 *  retrieved
 */
 
/* #define GCSTRINGS */

/*
 * set up the global defines based on the choice above
 * the global names are
 * operating system:
 *		  os_unix
 *		     os_4_1, os_4_1a, os_4_1c, os_4_2, os_unix_ts
 *		  os_vms
 */

/* OFFSET -  this is the offset to the users address space. */
/* NB: this is not necessarily tied to the hardware.  Pixel
   informs us that when they put up 4.1 the offsetis likely
   to change*/




