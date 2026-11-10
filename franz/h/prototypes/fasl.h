/* ./fasl.c */
#ifndef FASL_2c3273d3d3842057c95ac399bf1cbbce_h
#define FASL_2c3273d3d3842057c95ac399bf1cbbce_h


extern struct ssym   Symbtb[];
extern struct nlist  syml;
extern int           compar(int *arg1, int *arg2);
extern struct trent *gettran(int size);
extern int           clrtt(int flag);
extern int           add_offset(int *addr, int relocoffset);
extern int           add_offset(int *addr, int relocoffset);

#endif
