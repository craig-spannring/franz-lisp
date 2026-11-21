/* ./low.c */
#ifndef LOW_c32a5a84c3d9dae85de0a58b2f3301a3_h
#define LOW_c32a5a84c3d9dae85de0a58b2f3301a3_h

#include "global.h"

extern struct atom nilatom;
extern struct atom eofatom;

/**
 * @defgroup smallfixnums Small Integers
 * @brief Table of small integers.
 *
 * These can be thought of as bookmarks into a table of integers
 * ranging from -1024 to 1023.  Negs points to the first item in the
 * array which contains a value -1024.  Fixzero is the index of the
 * element with the value 0.  Lastfix is the index of the last element
 * into the array.  This last element contains the number 1023.
 * 
 * @{
 */ 
extern const long *const Negs;
extern const long *const Fixzero;
extern const long *const Lastfix;

/** @} */ 
#endif
