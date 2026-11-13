/* ./fex4.c */
#ifndef FEX4_13063e49c53c6ec91a4eb58f6f4cb4d4_h
#define FEX4_13063e49c53c6ec91a4eb58f6f4cb4d4_h

#include "global.h"


extern int readcode;
extern int setcode;

extern lispval   Istsrch(lispval nam);
extern lispval   Isstatus(lispval curnam, lispval curval);
extern lispval   Iaddstat(lispval name, int readcode, int setcode, lispval valu);

#endif
