# Porting to Modern Architecture #

(Franz Lisp)[https://en.wikipedia.org/wiki/Franz_Lisp] ran on VAX-11
and Sun 68k based machines running BSD Unix. It would be fun to be
able to run this lisp on a modern system such as MacOS on an Apple
Silicon CPU.

## Overview ##

The original code was was written for a ILP32 target and abuses the
equivalent sizes of int and pointers.  It also makes assumptions about
the host machine's ABI and manipulates the stack using those
assumptions.  We would like to modify the code to make no assumptions
about the ABI or sizes of int and pointers. 

The documentation was written with troff.  The groff dialect is just
different enough to prevent a clean generation of the documents.  We
will modify the .n files to be compliant with groff.

And the build system was created around BSD Make.  We'd like to do
this port using a new IDEs like Visual Studio or Xcode (or even Emacs
with the newer IDE capabilities.  Make won't provide that capability.
We will change to a cmake based build system. 

## AI Perspective ##

### lisplib ###
The parts of lisplib/ most obviously still tied to the original
Berkeley Unix toolchain are: 

- The build/install assumptions in lisplib/Makefile
  - It hard-codes /usr/lib/lisp as the install path and expects the
    Franz compiler (Liszt) and the legacy system tools to be present. 
  - It contains explicit targets like as and nld, which copy /bin/as
    and /bin/ld into the repo: 
    - as: copies /bin/as to as
    - nld: copies /bin/ld to nld
  - That is a very direct reminder that the library was designed to be
    built and run in a classic Berkeley Unix environment. 
- The Unix syscall layer in lisplib/syscall.l
  - This file is basically a wrapper around Unix system calls
    (sys_open, sys_chdir, sys_close, sys_time, sys_ioctl, etc.). 
  - The comments say it is for Unix system calls and even note
    compatibility with Eunice under VMS, so it is clearly not
    cross-platform in a modern sense. 
- The machine-specific startup files in lisplib/autorun/
  - autorun/vax, autorun/tahoe, autorun/unisoft, autorun/sun4.2,
    autorun/mc500, autorun/68k 
  - These are exact examples of the old architecture-specific
    Unix/toolchain assumptions of the original Franz system.
- The Berkeley-era standard library files themselves
  - Files like common0.l, common1.l, common2.l, syntax.l, toplevel.l,
    and trace.l are part of the classic Berkeley Franz environment
    rather than a portable modern Lisp package. 
  - The ReadMe labels them as “supported and documented by people at
    Berkeley,” which is a strong sign of their historical environment
    dependence. 

In short: the most Unix-specific pieces are the build glue (Makefile +
/usr/lib/lisp assumptions), the assembler/loader wrapper (as/nld), the
Unix syscall layer (syscall.l), and the architecture-specific startup
scripts in autorun/. Those are the pieces still most visibly tied to
the original Berkeley Unix toolchain.

### franz ###

The right modernization strategy is not “port it blindly to
Windows/Linux/macOS.” It is “re-architect the machine-dependent layer
while keeping the Lisp semantics intact.”

The core idea

A pre-1990s Franz Lisp system likely assumes:
- Unix-centric process model
- 32-bit word assumptions
- direct machine code generation or custom assembler
- old C calling conventions
- fixed-size pointers and integer types
- nonportable file/path/signal handling
- little/no memory safety
- compiler output matching a specific host ABI

Modernizing that onto Linux, macOS, and Windows is feasible, but only if you separate:
- language semantics
- runtime data model
- OS-specific services
- CPU-specific code generation

What needs to change first

1. Kill implicit Unix assumptions
   - Replace `fork`, `wait`, `ioctl`, `signal`, `select`, `mmap` semantics with an abstraction layer
   - Handle path separators (`/` vs `\`)
   - Use UTF-8 internally; normalize file handling and environment vars
   - Threading, timers, locale, and sockets must be behind a portable runtime API
1. Replace old C with modern C/C++ standards
   - No K&R C or implicit int
   - Replace old typedefs with exact-width types: `int32_t`, `uint32_t`, `intptr_t`, `uintptr_t`
   - Use `size_t` correctly
   - Stop relying on undefined behavior such as pointer casts, alignment assumptions, and uninitialized memory
   - Add static analysis and sanitizers from day one
1. Fix the memory model
   - 64-bit clean-up is mandatory
   - Fix pointer arithmetic that assumes 32-bit addresses
   - Handle alignment, big/little endian, padding, and packed structs explicitly
   - If the system uses tagged pointers or custom Lisp objects, define a portable object layout
1. Make machine-code generation portable.  This is the biggest issue.
   If the original system emits machine code directly, modern compilers
   won’t just “work” on Windows/macOS/Linux because: 
   - calling conventions differ
   - object file formats differ
   - relocations differ
   - instruction encodings differ
   - stack alignment differs
   - ABI differences between x86_64, ARM64, Windows vs Unix are nontrivial
   So the port should do one of these:
   - Keep the old code generator as a legacy backend, but hide it behind
     a portable IR/compiler abstraction 
   - Front-end to LLVM IR and let LLVM generate machine code for each target
   - Or, if the Lisp runtime is interpreter-based rather than code
     generator-based, replace the custom backend with a portable virtual
     machine runtime 
   The clean solution is usually:
   - keep the Lisp language and semantics
   - replace the machine-specific backend with a portable VM or
     LLVM-backed backend 
1. Build system must be cross-platform from the start.  Use:
   - CMake + Ninja as the canonical build layer
   - toolchain definitions for GCC, Clang, MSVC, and Apple Clang
   - CI for Linux, macOS, Windows
   - a single set of configuration options for:
     - host arch
     - debug/release
     - static/shared runtime
     - threading model
     - bytecode vs native code

A realistic modernization roadmap

Phase 1: Freeze the behavior
- Build the current version in a legacy environment
- Make a “golden” reference
- Document runtime semantics before touching code
- Capture tests for core Lisp behavior

Phase 2: Isolate the portability boundary
Create a layer like:
- platform.h
- os_interface.h
- memory.h
- file.h
- process.h
- timing.h
- abi.h

Everything machine/OS-specific goes through that.

Phase 3: Make the runtime 64-bit-safe
- audit all pointer arithmetic
- fix type widths
- replace `long` assumptions
- verify object tagging rules and heap layout

Phase 4: Replace custom assembler / code emitter
If the compiler emits native code:
- abstract the backend
- move to LLVM IR if possible
- otherwise generate C stubs and rely on the host compiler
- avoid direct platform assembly unless absolutely necessary

Phase 5: Handle filesystem and platform-specific semantics
- Windows path handling, UNC paths, drive letters
- macOS/Linux case sensitivity differences
- line endings
- file permissions
- symlinks
- process environment variables

Phase 6: Threading and concurrency
Old Lisp systems often assume single-threaded execution. Modern systems need:
- thread-safe heap/gc
- mutexes
- condition variables
- thread-local storage
- signal-safe execution rules

Phase 7: Native library and FFI layer
A modern compiler toolchain often needs:
- C ABI interop
- ABI-safe function calls
- foreign function interface
- bitfield and struct layout compatibility

If this Lisp system exposes native functions or packages, the interface layer must be carefully standardized.

If the project is really “Franz Lisp” in the old sense, there are two strategic choices

Option A: Port the runtime as a compatibility environment
- keep the legacy semantics
- just rebuild for modern systems
- lower risk, higher compatibility
- best if you need a historical Lisp running on modern hardware

Option B: Re-skin it as a modern Lisp implementation
- use a portable VM or LLVM-backed compiler
- throw away the machine-specific assumptions
- higher engineering effort
- best if the goal is maintainability and portability, not historical fidelity

My recommendation

For a project named franz-lisp that is likely old and Unix-oriented, I would do:
- keep the Lisp language semantics and core runtime
- isolate OS and CPU differences behind a strict API
- replace direct machine code generation with LLVM or a portable bytecode VM
- make the entire build cross-platform with CMake
- target x86_64 and ARM64 on Linux/macOS/Windows
- introduce full CI and sanitizer coverage before refactoring deeper

This is the difference between “porting an old codebase” and
“rebuilding a compiler toolchain for modern targets.” 

If you want, I can go one level deeper and sketch:
- an actual architecture for a portable Franz Lisp runtime
- a CMake-based build layout for Linux/macOS/Windows
- a compatibility layer for POSIX vs Win32
- or a migration plan for replacing the old native backend with LLVM.


### Memory Map ###

#### Allocation of Memory for a Lisp Object ####
Yes. In this Franz Lisp codebase, a Lisp object is not created by
`malloc()` in the usual C sense; it is created by a custom allocator
that hands out cells from a Lisp-managed heap. 

The key files are:
- franz/alloc.c
- franz/data.c
- franz/h/global.h
- franz/h/config.h

The overall model

- The system keeps a flat data region for Lisp objects.
- Memory is divided into 512-byte pages (`LBPG`).
- Each page is typed: atom, int, cons cell, string, vector, etc.
- The type table is `typetable[]`, and the page allocator keeps free
  lists per object type. 

The critical definitions in franz/h/global.h show the page size and
type structure: 

- `#define LBPG 512`
- `#define NUMSPACES (VECTORI+1)`
- object families like `ATOMSPP`, `INTSPP`, `DTPRSPP`, `ARRAYSPP`, etc.

This is the basis for a fixed-size, page-oriented memory arena.

How an object is created

Take the simplest one: an integer.

In alloc.c:

- `newint()` calls `next_one(&int_str)`
- `newdot()` calls `next_one(&dtpr_str)`
- `newatom()` calls `next_one(&atom_str)`
- `newvec()` and similar call special vector allocators

So the common path is:

- `newX()` -> `next_one(...)` or `next_pure_one(...)`
- `next_one` ensures there is free space for that object type
- if there isn’t, it triggers GC or allocates a new page

The `next_one` function does exactly this:
- checks the type’s free list
- if empty, calls `gc(type_struct)` if possible
- if still empty, calls `get_more_space(type_struct, FALSE)`
- takes the first free cell from the free list and returns it

That free list is built page-by-page.

How a new page is allocated

The real page allocator is `get_more_space(type_struct, purep)` in alloc.c.

It does this:

- if it is using a hole model, it may allocate from the “hole” region
  instead of normal data space 
- otherwise it does `xsbrk(1)` to get one new 512-byte page
- it sets the page type using `SETTYPE(start, type_struct->type, 20)`
- it initializes the page as a linked list of free cells
- each cell points to the next free cell on that type’s freelist

So each page is not just a block of bytes; it is a structured chunk
whose cells are linked together. 

Example: creating a cons cell

`newdot()` does roughly:

- `temp = next_one(&dtpr_str)`
- fills `temp->d.car = nil`
- fills `temp->d.cdr = nil`
- returns it

So the cons cell is just a cell from a DTPR page, with the fields initialized.

A more elaborate object: strings

`newstr()` is special:
- it uses a string buffer `strbuf`
- if the current string area is full, it allocates a new string page
- it copies the string into that page and returns the pointer

This explains why strings are treated differently than ordinary cells.

What allocates the memory region itself

The low-level `sbrk`-style calls are in alloc.c:

- `xsbrk(n)` allocates a page chunk in groups
- `ysbrk(pages, type)` allocates a block and marks its pages as a given type
- `csegment(typecode, nitems, useholeflag)` allocates a larger chunk
  for arrays/vectors, then zeroes it and tags the pages 

So the heap is built from raw pages, then subdivided into object pages
and free-list cells. 

Memory bookkeeping

There are two important pieces of state:

- `datalim`: pointer to the end of the current data area
- `typetable`: one byte per 512-byte page telling what type the page
  holds 

This gives the runtime a fast way to tell:
- what kind of object is at an address
- whether an address is valid
- where the heap ends

Garbage collection

When a freelist is empty, `next_one` may trigger `gc()`.

The collector:
- marks all reachable Lisp objects
- sweeps the pages
- rebuilds free lists by scanning the heap
- reuses dead cells

This is why a cell is not “allocated with malloc” in the usual sense;
it is reclaimed and reused from the custom heap. 

Simplified flow

Here is the lifecycle in one sentence:

- allocate raw heap pages with `sbrk`/`xsbrk`
- subdivide them into type-specific pages
- link free cells on per-type freelists
- `newint`/`newdot`/`newatom`/`newvec` grab one free cell
- if empty, GC or allocate a new page

A good mental model is:

- Franz Lisp uses a custom object heap, not the C runtime heap.
- Objects are page-based, typed, and managed with per-type freelists.
- The low-level memory allocator is up in alloc.c, while the object
  constructors are the small `new*` wrappers in the same file. 

If you want, I can next walk through one exact object in the codepath
step-by-step, such as: 
- how `newdot()` allocates a cons cell
- how a vector is allocated
- how the garbage collector rebuilds free lists after a GC cycle

#### VAX-11 ####
For the VAX/BSD 4.3 build, the memory model is a flat, page-based Lisp
heap starting at address 0, not a segmented layout. 

The key points from the VAX configuration are:

- `OFFSET` is set to 0 for VAX Unix builds, and `NILIS0` is
  enabled. That means the Lisp heap begins at zero in user space. 
- `CNIL` is defined as `OFFSET - 4`, so the `nil` sentinel sits just
  below the heap base. In other words, the heap is addressed as a
  contiguous region starting immediately at the base of the data
  segment. 
- Lisp objects are page-addressed: each object page is 512 bytes, and
  the address-to-page conversion is 
  effectively `(address - OFFSET) >> 9`.
- The runtime keeps a type table named `typetable` with one entry per
  page, so each 512-byte page knows what kind of Lisp object it
  contains. The default heap size is `TTSIZE = 6120` pages, which is
  roughly 3.1 MB of Lisp heap. 
- The heap itself is stored in `purepage[TTSIZE]`, with `datalim`
  marking the next free allocation point. 

So the practical memory map is:

- low addresses: runtime / C / stack / text
- base of Lisp heap: address 0
- Lisp object area: contiguous pages, 512 bytes each, type-tagged by `typetable`
- higher addresses: the growing Lisp heap up to the limit implied by `TTSIZE`
- `nil` sentinel: immediately below the heap base (`OFFSET - 4`)

There is also a second build variant in the tree that inserts a 2 MB
“hole” between text and data (`-H 2097152`), but that is not the
normal VAX/BSD 4.3 `rawlisp` layout; the standard build is the no-hole
contiguous version.

#### m68k ####
For the m68k build, the map is the same idea as the VAX version, but
shifted upward by a nonzero `OFFSET` instead of starting at zero. 

The key definitions are in `franz/h/config.h` and `franz/h/global.h`:

- For 68000 builds, `m_68k` is enabled.
- `OFFSET` is not 0; it depends on the OS/port:
  - Sun 4.2 / 4.1c / 4.2beta: `0x8000`
  - Sun Unisoft: `0x40000`
  - Dual Unisoft: `0x800000`
  - Pixel / Lisa: `0x20000`
- The heap pages are addressed as:
  - `ATOX(a) = (((int)(a)) - OFFSET) >> 9`
  - `TYPE(a) = typetable[ATOX(a)]`
  - `CNIL = OFFSET - 4`

So the m68k memory map is roughly:

- low address region: text/code and OS/user areas
- gap: addresses below `OFFSET` are reserved / not part of Lisp heap
- Lisp heap starts at `OFFSET`
- heap is broken into 512-byte pages (`LBPG == 512`)
- each page has a type tag in `typetable`
- `datalim` marks the current end of allocated data
- the `nil` sentinel sits just below the heap, at `OFFSET-4`

In other words, this is still a flat heap, but it is not anchored at
address 0. It is a contiguous block beginning at a machine-specific
offset, leaving room between the text segment and the Lisp data
segment. That offset is exactly why the 68k code uses `OFFSET`
throughout the allocator and GC logic instead of assuming a zero base. 

Relevant source:
- `https://github.com/craig-spannring/franz-lisp/blob/062bb7ad66217443c66a9467b5a86aefc8b15bbc/franz/h/config.h`
- `https://github.com/craig-spannring/franz-lisp/blob/062bb7ad66217443c66a9467b5a86aefc8b15bbc/franz/h/global.h`
- `https://github.com/craig-spannring/franz-lisp/blob/062bb7ad66217443c66a9467b5a86aefc8b15bbc/franz/alloc.c`

If you want, I can also sketch the exact page layout for a specific
m68k target (for example Sun 4.2 with `OFFSET=0x8000` versus Sun
Unisoft with `OFFSET=0x40000`). 


## A More Human Oriented Perspective ##


### Build System ###


### Building Documentation ###


### Building rawlisp ###


### Building liszt ###


### Building snlisp and nlisp ### 

