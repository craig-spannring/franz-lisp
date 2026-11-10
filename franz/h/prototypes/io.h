/* ./io.c */
#ifndef IO_644fbff78c6d90ab6e738ceac4793ff6_h
#define IO_644fbff78c6d90ab6e738ceac4793ff6_h


extern struct readtable initread;
extern int              keywait;
extern int              plevel;
extern int              plength;
/* static int dbqflag; */
/* static int mantisfl; */
/* static char baddot1[]; */
/* static char baddot2[]; */
extern int   macrox(void);
extern int   Iratom(void);
extern char *strbuf;
extern char *atomtoolong(char *copyto);
extern int   lfltpr(char *buf, double val);

#endif
