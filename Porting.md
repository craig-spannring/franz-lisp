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



## A More Human Oriented Perspective ##


### Build System ###


### Building Documentation ###


### Building rawlisp ###


### Building liszt ###


### Building snlisp and nlisp ### 

