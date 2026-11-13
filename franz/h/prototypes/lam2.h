/* ./lam2.c */
#ifndef LAM2_b874887c6d951cc3e9e72a03cab042aa_h
#define LAM2_b874887c6d951cc3e9e72a03cab042aa_h

#include "global.h"

extern int join;

extern lispval r(int op);
extern void    Iflatsi(lispval current);
extern lispval Igetplist(lispval pptr, lispval ind);
extern lispval Iputprop(lispval atm, lispval prop, lispval ind);
extern lispval Lputprop(void);

#endif
