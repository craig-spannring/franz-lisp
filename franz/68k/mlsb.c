/* Copyright (c) 1982, Regents, University of California */

struct vl       { long high; long low; };
long 
mlsb (register long *utop, register long *ubot, register long *vtop, register nqhat)
{
        register handy, carry;
        struct vl work;
        
        for(carry = 0; utop >= ubot; utop--) {
                emul(nqhat,*--vtop,carry+*utop,&work);
                carry = work.high;
                handy = work.low;
                *utop = handy & 0x3fffffff;
                carry <<= 2;
                if(handy & 0x80000000) carry += 2;
                if(handy & 0x40000000) carry += 1;
        }
        return(carry);
}
long 
adback (register long *utop, register long *ubot, register long *vtop)
{
        register handy, carry;
        carry = 0;
        for(; utop >= ubot; utop--) {
                carry += *--vtop;
                carry += *utop;
                *utop = carry & 0x3fffffff;
                /* next junk is faster version of  carry >>= 30; */
                handy = carry;
                carry = 0;
                if(handy & 0x80000000) carry -= 2;
                if(handy & 0x40000000) carry += 1;
        }
        return(carry);
}
long 
dsdiv (register long *top, register long *bot, register long div)
{
        struct vl work; char err;
        register long handy, carry = 0;
        for(carry = 0;bot <= top; bot++) {
                handy = *bot;
                if(carry & 1) handy |= 0x40000000;
                if(carry & 2) handy |= 0x80000000;
                carry >>= 2;
                work.low = handy;
                work.high = carry;
                *bot = ediv(&work,div,&err);
                carry = work.high;
        }
        return(carry);
}
int 
dsadd1 (long *top, long *bot)
{
        register long *p, work, carry = 0;

        /*
         * this assumes canonical inputs
         */
        for(p = top; p >= bot; p--) {
                work = *p + carry;
                *p = work & 0x3fffffff;
                carry = 0;
                if (work & 0x40000000) carry += 1;
                if (work & 0x80000000) carry -= 2;
        }
        p[1] = work;
}
long 
dsrsh (long *top, long *bot, long ncnt, long mask1)
{
        register long *p = bot;
        register r = -ncnt, l = 30+ncnt, carry = 0, work, save;
        long mask = -1 ^ mask1;

        while(p <= top) {
                save = work = *p; save &= mask; work >>= r;
                carry <<= l; work |= carry; *p++ = work;
                carry = save;
        }
        return(carry);
}
