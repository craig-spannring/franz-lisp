/* ./ffasl.c */
#ifndef FFASL_aeb7442694422b9710c186c92fc71e4c_h
#define FFASL_aeb7442694422b9710c186c92fc71e4c_h


#include "global.h"

extern char *stabf;
extern char *messg;
// extern char *error;
extern long size;

extern char      *gstab(void);
extern char      *mytemp(void);
extern int        ungstab(void);
extern char      *Ilibdir(void);
extern lispval    verify(lispval in, char *error);
extern lispval    dispget(lispval given, char *messg, lispval defult);


#endif
