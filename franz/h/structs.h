/*                                      -[Sat Jan 29 14:00:31 1983 by jkf]-
 *      structs.h                       $Locker:  $
 * random structure definitions 
 *
 * $Header: /na/franz/franz/h/structs.h,v 1.1 83/01/29 14:07:48 jkf Exp $
 *
 * (c) copyright 1982, Regents of the University of California
 */

/* 
 * this file contains auxiliary structure definitions which are used by
 * just a few files.
 */

/* transfer table structures. */

#ifndef INC_structs189ce59e8bb2819a5f119e303707393f_h
#define INC_structs189ce59e8bb2819a5f119e303707393f_h

#include <stdio.h>

// #include "global.h"

#define TRENTS 510


#define lispint long                    /* TODO probably wrong, maybe use uintptr_t? */
#define MAX10LNG 200000000              /* max long divided by 10       */


typedef union lispobj *lispval ;

struct dtpr {
        lispval cdr, car;
};

struct sdot {
        int     I;
        lispval CDR;
};


struct  atom    {
        lispval         clb;            /* current level binding*/
        lispval         plist;          /* pointer to prop list */
#ifndef WILD
        lispval         fnbnd;          /* function binding     */
#endif
        struct  atom    *hshlnk;        /* hash link to next    */
        char            *pname;         /* print name   */
        };
#ifdef WILD
#define fnbnd clb
#endif

struct array {
        lispval accfun,         /*  access function--may be anything  */
                aux;            /*  slot for dimensions or auxilliary data  */
        char *data;             /*  pointer to first byte of array    */
        lispval length, delta;  /* length in items and length of one item */
};

struct bfun {
        lispval (*start)();     /*  entry point to routine  */
        lispval discipline,     /*  argument-passing discipline  */
                language,       /*  language coded in   */
                params,         /*  parameter list if relevant  */
                loctab;         /*  local table  */
};

struct Hunk {
        lispval hunk[1];
};

struct Vector {
        lispval vector[1];
};

/* the vectori types */
struct Vectorb {
        char vectorb[1];
};

struct Vectorw {
       short  vectorw[1];
};

struct Vectorl {
    long vectorl[1];
};

union lispobj {
        struct atom a;
        FILE *p;
        struct dtpr d;
        long int i;
        long int *j;
        double r;
        lispval (*f)();
        struct array ar;
        struct sdot s;
        char c;
        lispval l;
        struct bfun bcd;
        struct Hunk h;
        struct Vector v;
        struct Vectorb vb;
        struct Vectorw vw;
        struct Vectorl vl;
};


struct trent
{
    lispval (*fcn)(void);           /* function to call                     */
    lispval name;       /* symbol which is the function to call */
};

struct trtab
{
    struct trtab *nxtt;                 /* pointer to next transfer table */
    struct trent trentrs[TRENTS];       /* entries                        */
    int sentinal;                       /* must be zero                   */
};



struct heads {
        struct heads *link;
        char *pntr;
};


struct types
{
        char    *next_free;
        int     space_left,
                space,
                type,
                type_len;               /*  note type_len is in units of int */
        lispval *items,
                *pages,
                *type_name;
        struct heads
                *first;
        char    *next_pure_free;

};

struct str_x
{
        char    *next_free;
        int     space_left;
};
#endif
