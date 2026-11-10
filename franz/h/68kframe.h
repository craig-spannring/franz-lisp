/*
 * $Header: 68kframe.h,v 1.3 84/02/29 12:43:22 sklower Exp $
 * $Locker:  $
 * machine stack frame
 */
#ifndef 68KFRAME_974af9d063f312af0d36702c579a69f8_h
#define 68KFRAME_974af9d063f312af0d36702c579a69f8_h


struct machframe
{
  struct machframe *fp;
  lispval (*pc)();
  lispval ap[1];
};

#endif
