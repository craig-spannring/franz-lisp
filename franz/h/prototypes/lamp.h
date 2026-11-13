/* ./lamp.c */
#ifndef LAMP_6a4fef007bf4062789f6fa8516d38336_h
#define LAMP_6a4fef007bf4062789f6fa8516d38336_h

#include "global.h"
#include <stdint.h>

#ifdef PROF
#define PBUFSZ 500000
#else
#define PBUFSZ 8
#endif

extern short pbuf[PBUFSZ];
#ifdef PROF
extern int mcnts[NMCOUNT];
#else
extern int mcnts[1];
#endif 
extern uintptr_t    mcntp;
extern int          doprof;
extern int          Lmonitor(void);

#endif
