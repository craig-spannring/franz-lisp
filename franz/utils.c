/**
 * @file
 */

#include "utils.h"
#include <string.h>

int blzero(void *where, size_t howmuch)
{
  memset(where, 0, howmuch);
  
  return 0;
}

