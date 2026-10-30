#include "global.h"
#include "structs.h"

int prunei(lispval what)
{
  extern struct types int_str;

  if (((long)what) > ((long)gstart))
  {
    --(int_items->i);
    what->i           = (long)int_str.next_free;
    int_str.next_free = (char *)what;
  }
}
