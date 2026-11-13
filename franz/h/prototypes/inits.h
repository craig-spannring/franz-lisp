/* ./inits.c */
#ifndef INITS_09b6ad6778d27d7d892a5c35e55edffb_h
#define INITS_09b6ad6778d27d7d892a5c35e55edffb_h

#include "global.h"

extern lispval reborn;

extern void initial(void);
extern void sginth(int signo);
extern int  sigcall(int which);
extern int  delayoff(void);
extern int  dosig(void);
extern void badmr(int number);

#endif

