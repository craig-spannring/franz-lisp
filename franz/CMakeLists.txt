#
# The original make files create lisp through 2 intermediate programs
# 
#   - rawlisp  Created by linking 
#           ${BottomObj}
#           ${NoHoleObj} or ${HoleObj} 
#           ${MipObj4}
#           ${CPU_SpecificObj}
#           ${OsObjs}
#   - nlisp    Lisp interpreter with compiled lisp
#              functions/macros/etc dumped. 
# nlisp is copied into the install directory.
#

# Find the termcap or tinfo library on Unix-like systems
find_library(TERMCAP_LIBRARY NAMES termcap tinfo curses ncurses)
find_path(TERMCAP_INCLUDE_DIR NAMES termcap.h)

if(TERMCAP_LIBRARY AND TERMCAP_INCLUDE_DIR)
    message(STATUS "Found termcap: ${TERMCAP_LIBRARY}")
else()
    message(FATAL_ERROR "Termcap library or header not found!")
endif()


add_executable(rawlisp)


list(APPEND rawlisp_cc_flags "${fl_cc_flags}")

target_compile_options(rawlisp PRIVATE ${rawlisp_cc_flags})
target_include_directories(rawlisp PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./h
  ${TERMCAP_INCLUDE_DIR}
)
target_link_libraries(rawlisp PRIVATE ${TERMCAP_LIBRARY})


target_compile_definitions(rawlisp PRIVATE
)

# Lowest-level startup/runtime.  Must be linked at the beginning of executable
# note- at one time MipSrc may have refered to machine independent part
set(MipSrc1
  low.c
  lowaux.s
)

# Memory allocation and data space setup. 
set(MipSrc2
  alloc.c
  data.c
)

# Code positioned between low level support code and the lisp kernel.
set(MipSrc3
  rlc.c
)

# Bulk of the lisp run-time and interpreter
set(MipSrc4
  lisp.c
  eval.c
  eval2.c
  inits.c
  io.c
  error.c
  sysat.c
  lam1.c
  lam2.c
  lam3.c
  lam4.c
  lam5.c
  lam6.c
  lam7.c
  lam8.c
  lam9.c
  lamr.c
  lamp.c
  fex1.c
  fex2.c
  fex3.c
  fex4.c
  fexr.c
  fpipe.c
  subbig.c
  pbignum.c
  divbig.c
  ffasl.c
  fasl.c
  trace.c
  evalf.c
  frame.c
  lamgc.c
)
 
set(Headers  
  h/aout.h
  h/bigmath.h
  h/catchfram.h
  h/chars.h
  h/chkrtab.h
  h/dfuncs.h
  h/dualaout.h
  h/duallispo.h
  h/exarith.h
  h/frame.h
  h/gc.h
  h/global.h
  h/gtabs.h
  h/hpagsiz.h
  h/lconf.h
  h/lfuncs.h
  h/lispo.h
  h/ltypes.h
  h/myfrexpr.h
  h/pbignum.h
  h/prunei.h
  h/sigtab.h
  h/structs.h
  h/stubs.h
  h/types.h
)

target_sources(rawlisp PRIVATE
  ${MipSrc1}
  ${MipSrc2}
  ${MipSrc3}
  ${MipSrc4}

  stubs.c

  ${Headers}
)

set(STILL_PORTING true)
if(STILL_PORTING)
  target_compile_definitions(rawlisp PUBLIC STILL_PORTING=1)
  target_compile_definitions(rawlisp PUBLIC FINISHED_PORTING=0)
else()
  target_compile_definitions(rawlisp PUBLIC STILL_PORTING=0)
  target_compile_definitions(rawlisp PUBLIC FINISHED_PORTING=1)
endif()

target_include_directories(rawlisp PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./h
  ${CMAKE_CURRENT_BINARY_DIR}
)
  
configure_file(
  ${CMAKE_CURRENT_LIST_DIR}/h/config.h.in
  ${CMAKE_CURRENT_BINARY_DIR}/config.h
)

add_custom_command(TARGET rawlisp POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E create_symlink $<TARGET_FILE:rawlisp> ${CMAKE_CURRENT_LIST_DIR}/rawlisp
  COMMENT "creating symlink"
)

find_package(Doxygen)

if(Doxygen_FOUND)
    get_target_property(RawLispSrcs rawlisp SOURCES)
    message("RawLispSrcs: ${RawLispSrcs}")
    string(JOIN " ${CMAKE_CURRENT_LIST_DIR}/" RawLispSrcs ${RawLispSrcs})
    
    configure_file(${CMAKE_CURRENT_LIST_DIR}/Doxyfile.in
      ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
    configure_file(${CMAKE_CURRENT_LIST_DIR}/DoxygenLayout.xml.in
      ${CMAKE_CURRENT_BINARY_DIR}/DoxygenLayout.xml)

    add_custom_target(rawlisp_doxydocs ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM)
else()
  message(STATUS "Doxygen not found, API documentation will not be generated")
endif()
