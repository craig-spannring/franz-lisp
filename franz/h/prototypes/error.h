/* ./error.c */
#ifndef ERROR_65bd11e26e9cb1a40692379f80eee61c_h
#define ERROR_65bd11e26e9cb1a40692379f80eee61c_h


/* static int IElimit; */
extern int   contvl;
extern int   uniqid;
extern int   contuab;
extern char *message;
extern int   limit;
extern int   lispend(char mesg[]);
extern int   namerr(void);
extern int   binderr(void);
extern int   rtaberr(void);
extern int   xserr(void);
extern int   badmem(int n);
extern int   argerr(char *msg);

#endif
