/* ./fasl.c */
#ifndef FASL_2c3273d3d3842057c95ac399bf1cbbce_h
#define FASL_2c3273d3d3842057c95ac399bf1cbbce_h



#include <stdint.h>


struct ssym
{
  static_assert(STILL_PORTING, "flock should probably be a uintptr_t");

  char      *fnam; /* pointer to string containing name */
  uintptr_t  floc; /* address of symbol */
  int        ord;  /* ordinal number within cur sym tab */
  
};


extern struct ssym   Symbtb[];
extern struct nlist  syml;
extern int           compar(int *arg1, int *arg2);
extern struct trent *gettran(int size);
extern int           clrtt(int flag);
extern int           add_offset(int *addr, int relocoffset);
extern int           add_offset(int *addr, int relocoffset);

#endif
