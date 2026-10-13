cmake_minimum_required(VERSION 3.10)
project(franz-kernel NONE)

# This CMakeLists acts as a thin wrapper around the repository's existing Makefiles.
# It does not reimplement the historic, machine-dependent build logic; instead it
# provides CMake-friendly custom targets that invoke the upstream make targets.

option(MACH "Machine/architecture name to pass to the Makefiles (e.g. tahoe, 68k, vax)" "tahoe")
set(LIBDIR "${CMAKE_INSTALL_PREFIX}/lisplib" CACHE STRING "LibDir passed to make")
set(OBJDIR "${CMAKE_INSTALL_PREFIX}/bin" CACHE STRING "ObjDir passed to make")
set(DESTDIR "" CACHE STRING "DESTDIR passed to make (default empty)")
set(MAKE_TARGET "slow" CACHE STRING "Top-level make target to run (slow, fast, all, install, clean, etc.)")

# Compute the top-level directory (one level up from this franz/ directory)
get_filename_component(TOPDIR "${CMAKE_CURRENT_SOURCE_DIR}/.." REALPATH)

# Helper to build the command line used for invoking make
function(franz_make_command out_var target)
  set(cmd "${CMAKE_MAKE_PROGRAM} -C ${TOPDIR} ${target}")
  # pass variables to make if set
  if(DEFINED MACH)
    set(cmd "${cmd} Mach=${MACH}")
  endif()
  if(DEFINED LIBDIR AND NOT "${LIBDIR}" STREQUAL "")
    set(cmd "${cmd} LibDir=${LIBDIR}")
  endif()
  if(DEFINED OBJDIR AND NOT "${OBJDIR}" STREQUAL "")
    set(cmd "${cmd} ObjDir=${OBJDIR}")
  endif()
  if(DEFINED DESTDIR AND NOT "${DESTDIR}" STREQUAL "")
    set(cmd "DESTDIR=${DESTDIR} ${cmd}")
  endif()
  set(${out_var} "${cmd}" PARENT_SCOPE)
endfunction()

# Default 'build' target: runs the chosen top-level make target (defaults to 'slow')
franz_make_command(_build_cmd "${MAKE_TARGET}")
add_custom_target(build
  COMMAND ${CMAKE_COMMAND} -E echo "Running: ${_build_cmd}"
  COMMAND ${_build_cmd}
  WORKING_DIRECTORY ${TOPDIR}
  COMMENT "Build Franz Lisp via upstream Makefiles (target=${MAKE_TARGET})"
)

# Convenience targets that map to common make targets. They call the top-level make
# which will in turn drive the machine-specific builds in franz/<mach>.
macro(add_franz_make_target name make_target)
  franz_make_command(_cmd "${make_target}")
  add_custom_target(${name}
    COMMAND ${CMAKE_COMMAND} -E echo "Running: ${_cmd}"
    COMMAND ${_cmd}
    WORKING_DIRECTORY ${TOPDIR}
    COMMENT "Run make ${make_target} via upstream Makefile"
  )
endmacro()

add_franz_make_target(all all)
add_franz_make_target(fast fast)
add_franz_make_target(slow slow)
add_franz_make_target(install install)
add_franz_make_target(clean clean)
add_franz_make_target(copylibrary copylibrary)
add_franz_make_target(fromasm fromasm)

# Target to run lispconf (configure the C makefiles). lispconf is at the repo root.
# Usage: cmake --build . --target configure -- -DARG=<conf-name>
add_custom_target(configure
  COMMAND ${CMAKE_COMMAND} -E echo "Running lispconf (use ARG to pass type, e.g. vax_4_1 or tahoe_4_3)"
  COMMAND ${CMAKE_COMMAND} -E echo "To run with a specific configuration: cmake --build . --target configure -- -DARG=vax_4_1"
  COMMENT "Helper: run lispconf to generate machine-specific Makefiles"
)

# If user provides ARG via --, execute lispconf ARG
if(DEFINED ARG)
  add_custom_command(TARGET configure PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "Invoking lispconf ${ARG}"
    COMMAND ${CMAKE_COMMAND} -E chdir ${TOPDIR} ./lispconf ${ARG}
  )
endif()

message(STATUS "franz CMake wrapper configured")
message(STATUS "Top-level directory: ${TOPDIR}")
message(STATUS "Default MAKE_TARGET: ${MAKE_TARGET}")
message(STATUS "MACH: ${MACH}")
message(STATUS "LibDir: ${LIBDIR}")
message(STATUS "ObjDir: ${OBJDIR}")

# Notes for maintainers in the generated build tree
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/README-FRANZ-CMAKE.txt
"This CMake wrapper invokes the repository's existing Makefiles to build Franz Lisp.\n"
"It intentionally does not reimplement the historic platform-specific build rules.\n"
"Common usage examples:\n"
"  cmake -S . -B build && cmake --build build --target build          # runs 'make -C .. slow'\n"
"  cmake --build build --target fast                                # runs 'make -C .. fast'\n"
"  cmake --build build --target configure -- -DARG=tahoe_4_3         # runs ./lispconf tahoe_4_3 at repo root\n"
)
