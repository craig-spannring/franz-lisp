/* ./eval.c */
#ifndef EVAL_aff06426b6b9c3f51b1e8c55c28eaa71_h
#define EVAL_aff06426b6b9c3f51b1e8c55c28eaa71_h

#include "global.h"

extern int            dumpnamestack(void);
extern struct argent *workp;

extern int            fchack(void);
extern lispval        Lapply(void);
extern lispval        eval(lispval actarg);
extern lispval        popnames(struct nament *llimit);
extern void           bindfix(lispval firstarg, ...); ///< @todo does this really need to be variadic?
extern lispval        Ifuncal(lispval fcn);
extern void           rebind(lispval argptr, struct argent *workp);



#endif
