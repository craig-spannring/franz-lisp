/* not used - just to look at I guess */
#ifndef TAHOEFRAME_e6bc4f589a72a457b7554d8d8c14a658_h
#define TAHOEFRAME_e6bc4f589a72a457b7554d8d8c14a658_h



#define FRAMOFFSET (-8) /* FP points to frame + 8 */

struct machframe
{
  lispval (*pc)();
  short             mask;
  short             removed;
  struct machframe *fp;
  lispval          *arg[2];
};

#endif
