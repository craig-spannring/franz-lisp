# Franz Lisp: Changes to Compile in the Modern World

The original Franz Lisp dates back to the early 1980's, before POSIX, before ANSI C.  

## #Defines

### SPISFP

SPISFP -- this is to indicate that the stack and frame pointer
are the same, or at least that you can't pull the same shenanigans
as on the vax or sun by pushing error frames at the end of C
frames and using alloca.  This should make life easier for
a native VMS version or IBM or RIDGE or Bellmac-32.

#define SPISFP 1

### OFFSET

this is the offset to the users address space. 
NB: this is not necessarily tied to the hardware.  Pixel
informs us that when they put up 4.1 the offsetis likely
to change 

### OS

unix or vms

### NILIS0 

for any UNIX implementation in which the users
adress space starts at 0 (like m_vax, above). 

### NPINREG

for the verison if lisp that keeps np and lbot in global
registers.  On the 68000, there is a special `hacked' version
of the C compiler that is needed to do this.


### DOMAIN

This is put on the (status features) list and is the value of (status
domain)


### SITE 

The name of the particular machine this lisp is running on this value
is available via (sys:gethostname).  On 4.1a systems it is possible to
determine this dynamically cheaply
 

### TTSIZE 

absolute limit, in pages (both text and data), of the size to which
the lisp system may grow. If you change this, you must recompile
alloc.c and data.c.


### Defines used in #ifdefs
```
68k
AS
debug
EUNICE_UNIX_OBJECT_FILE_CFASL
GCSTRINGS
HOLE
lint
LISZT
m_68k
mc500
METER
MSTATS
NILIS0
NO_A_OUT
NOTNOW
npinreg
NPINREG
OFFSET
os_4_1
os_4_1a
os_4_1c
os_4_2
os_4_3
os_masscomp
os_unisoft
os_unix_ts
os_vms
PORTABLE
PROF
RCHECK
RTPORTS
SIXONLY
SLOCLEAR
SPISFP
sun
sun_4_1c
sun_4_2
sun_4_2beta
SunGotItsActTogetherAboutTakingMcountOutOfCrt0
sunII
swapper
tahoe
ucbstd
unisoft
unisys3botch
UNIXTS
vax
vax_eunice_vms
VMS
WILD
```
