# Porting to Modern Architecture #


## AI Perspective ##

The parts of lisplib/ most obviously still tied to the original Berkeley Unix toolchain are:

- The build/install assumptions in lisplib/Makefile
  - It hard-codes /usr/lib/lisp as the install path and expects the Franz compiler (Liszt) and the legacy system tools to be present.
  - It contains explicit targets like as and nld, which copy /bin/as and /bin/ld into the repo:
    - as: copies /bin/as to as
    - nld: copies /bin/ld to nld
  - That is a very direct reminder that the library was designed to be built and run in a classic Berkeley Unix environment.
- The documentation in lisplib/ReadMe
  - It explicitly calls out:
    - as as the “Berkeley assembler”
    - nld as the “Berkeley loader”
    - It also describes the library as meant to live under /usr/lib/lisp, which is a classic Unix installation layout.
- The Unix syscall layer in lisplib/syscall.l
  - This file is basically a wrapper around Unix system calls (sys_open, sys_chdir, sys_close, sys_time, sys_ioctl, etc.).
  - The comments say it is for Unix system calls and even note compatibility with Eunice under VMS, so it is clearly not cross-platform in a modern sense.
- The machine-specific startup files in lisplib/autorun/
  - autorun/vax, autorun/tahoe, autorun/unisoft, autorun/sun4.2, autorun/mc500, autorun/68k
  - These are exact examples of the old architecture-specific Unix/toolchain assumptions of the original Franz system.
-The Berkeley-era standard library files themselves
  - Files like common0.l, common1.l, common2.l, syntax.l, toplevel.l, and trace.l are part of the classic Berkeley Franz environment rather than a portable modern Lisp package.
  - The ReadMe labels them as “supported and documented by people at Berkeley,” which is a strong sign of their historical environment dependence.

In short: the most Unix-specific pieces are the build glue (Makefile +
/usr/lib/lisp assumptions), the assembler/loader wrapper (as/nld), the
Unix syscall layer (syscall.l), and the architecture-specific startup
scripts in autorun/. Those are the pieces still most visibly tied to
the original Berkeley Unix toolchain.

## A More Human Oriented Perspective
TBD

