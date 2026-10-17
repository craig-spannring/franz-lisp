/* Copyright (c) 1982, Regents, University of California */

extern int Fixzero[];

int *
inewint (int n)
{
        register int *ip;
        int *newint();
        if(n < 1024 && n >= -1024) return (Fixzero+n);
        ip = newint();
        *ip = n;
        return(ip);
}
int 
blzero (void *where, int howmuch)
{
        char *p;
        for(p = where + howmuch; p > where; ) *--p = 0;
}
