/* Copyright (c) 1982, Regents, University of California */
int 
fixbits (register char *from, register char *to)
{
        register char save;
        
        while(from <= to) {
                save = from[3];
                from[3] = from[0];
                from[0] = save;
                save = from[2];
                from[2] = from[1];
                from[1] = save;
                from += 4;
        }
}
