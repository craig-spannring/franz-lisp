#ifndef INC_foo_20bd61a2160911ee943f7df99cde5d1f_h
#define INC_foo_20bd61a2160911ee943f7df99cde5d1f_h

/* foo.c */
extern lispval eval(lispval actarg);
extern lispval popnames(register struct nament *llimit);
extern int dumpnamestack(void);
extern lispval Lapply(void);
extern void rebind(lispval argptr, struct argent *workp);
extern lispval Ifuncal(lispval fcn);
extern lispval Lfuncal(void);
extern int fchack(void);
extern lispval Llexfun(void);
extern lispval unprot(void);
extern lispval linterp(void);
extern lispval Undeff(lispval atmn);
extern int bindfix(lispval firstarg);


#endif