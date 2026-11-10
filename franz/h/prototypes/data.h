/* ./data.c */
#ifndef DATA_9071de900b570f28dcd759af16b39b61_h
#define DATA_9071de900b570f28dcd759af16b39b61_h


extern int            lineleng;
extern int            rlevel;
extern char           keybin;
extern char           protflag;
extern char           rbktf;
extern struct argent *orgnp;
extern struct argent *namptr;
extern struct argent *lbot;
extern struct argent *np;
extern struct argent *nplim;
extern struct nament *bnp;
extern struct nament *orgbnp;
extern struct nament *bnplim;
extern int            hash;
extern int            atmlen;
/* static char i_strbuf[600]; */
extern char          *strbuf;
extern char          *endstrb;
extern long           xstack[16384];
extern long          *xsp;
extern long          *exsp;
extern char           nilpname[];
extern char           eofpname[];
extern int            uctolc;
extern int            dmpmode;
extern int            depth;
extern int            retval;
extern int            rsetsw;
extern int            bcdtrsw;
extern int            evalhcallsw;
extern int            funhcallsw;
extern int            exception;
extern int            sigintcnt;
extern char          *curhbeg;
extern int            usehole;
extern int            holesize;
extern int            itemp;
extern int            sigstruck;
extern int            sigdelay;
extern int            lctrace;
extern int            fvirgin;
extern int            gctime;
extern struct frame  *errp;
extern struct trtab  *trhead;
extern struct trent  *trcur;
extern int            trleft;
extern int           *beginsweep;
extern int            initflag;
extern int            tgcthresh;
extern int            page_limit;
extern int            ttsize;
extern char           purepage[TTSIZE];
extern int            fakettsize;
extern int            gcstrings;
extern int           *bind_lists;
extern struct str_x   str_current[2];
extern struct types   atom_str;
extern struct types   strng_str;
extern struct types   int_str;
extern struct types   dtpr_str;
extern struct types   doub_str;
extern struct types   array_str;
extern struct types   other_str;
extern struct types   sdot_str;
extern struct types   val_str;
extern struct types   funct_str;
extern struct types   vect_str;
extern struct types   vecti_str;
extern struct types   hunk_str[7];
extern unsigned char *ctable;
extern int            gensymcounter;
extern int            hashtop;
extern int            xcycle;
extern struct atom   *hasht[HASHTOP];
extern char           typetable[TTSIZE + 1];
extern char           lsbrkpnt;
extern char           zfreespace;

#endif
