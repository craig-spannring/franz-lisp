/* ./error.c */
#ifndef ERROR_65bd11e26e9cb1a40692379f80eee61c_h
#define ERROR_65bd11e26e9cb1a40692379f80eee61c_h

#include "global.h"

/* static int IElimit; */
extern int     contvl;
extern int     uniqid;
extern int     contuab;
extern char   *message;
extern int     limit;
extern lispval error(char *mesg, int contvl);
extern int     lispend(char mesg[]);
extern int     namerr(void);
extern int     binderr(void);
extern int     rtaberr(void);
extern int     xserr(void);
extern int     badmem(int n);
extern int     argerr(char *msg);
extern lispval errorh(lispval type, char *message, lispval valret, int contuab, int uniqid);
extern lispval errorh1(lispval type, char *message, lispval valret, int contuab, int uniqid, lispval arg1);
extern lispval errorh2(lispval type, char *message, lispval valret, int contuab, int uniqid, lispval arg1, lispval arg2);
extern lispval calhan(int limit, lispval *work, lispval type, int uniqid, lispval contuab, char *message, lispval handler);

extern void wnaerr(lispval fcn, int wantargs);


#endif

