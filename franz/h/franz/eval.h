#ifndef INC_eval_49f729ded1b87454ea2cc1e12b8f911d_h
#define INC_eval_49f729ded1b87454ea2cc1e12b8f911d_h

/* eval.c */
extern lispval eval(lispval actarg);
extern lispval popnames(register struct nament *llimit);
extern int dumpnamestack(void);
extern lispval Lapply(void);
extern int rebind(lispval argptr, struct argent *workp);
extern lispval Ifuncal(lispval fcn);
extern lispval Lfuncal(void);
extern int fchack(void);
extern lispval Llexfun(void);
extern lispval unprot(void);
extern lispval linterp(void);
extern lispval Undeff(lispval atmn);
extern int bindfix(lispval firstarg);


#endif