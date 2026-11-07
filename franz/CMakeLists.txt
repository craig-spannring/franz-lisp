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
  ${CMAKE_CURRENT_LIST_DIR}/low.c
  ${CMAKE_CURRENT_LIST_DIR}/lowaux.s
)

# Memory allocation and data space setup. 
set(MipSrc2
  ${CMAKE_CURRENT_LIST_DIR}/alloc.c
  ${CMAKE_CURRENT_LIST_DIR}/data.c
)

# Code positioned between low level support code and the lisp kernel.
set(MipSrc3
  ${CMAKE_CURRENT_LIST_DIR}/rlc.c
)

# Bulk of the lisp run-time and interpreter
set(MipSrc4
  ${CMAKE_CURRENT_LIST_DIR}/lisp.c
  ${CMAKE_CURRENT_LIST_DIR}/eval.c
  ${CMAKE_CURRENT_LIST_DIR}/eval2.c
  ${CMAKE_CURRENT_LIST_DIR}/inits.c
  ${CMAKE_CURRENT_LIST_DIR}/io.c
  ${CMAKE_CURRENT_LIST_DIR}/error.c
  ${CMAKE_CURRENT_LIST_DIR}/sysat.c
  ${CMAKE_CURRENT_LIST_DIR}/lam1.c
  ${CMAKE_CURRENT_LIST_DIR}/lam2.c
  ${CMAKE_CURRENT_LIST_DIR}/lam3.c
  ${CMAKE_CURRENT_LIST_DIR}/lam4.c
  ${CMAKE_CURRENT_LIST_DIR}/lam5.c
  ${CMAKE_CURRENT_LIST_DIR}/lam6.c
  ${CMAKE_CURRENT_LIST_DIR}/lam7.c
  ${CMAKE_CURRENT_LIST_DIR}/lam8.c
  ${CMAKE_CURRENT_LIST_DIR}/lam9.c
  ${CMAKE_CURRENT_LIST_DIR}/lamr.c
  ${CMAKE_CURRENT_LIST_DIR}/lamp.c
  ${CMAKE_CURRENT_LIST_DIR}/fex1.c
  ${CMAKE_CURRENT_LIST_DIR}/fex2.c
  ${CMAKE_CURRENT_LIST_DIR}/fex3.c
  ${CMAKE_CURRENT_LIST_DIR}/fex4.c
  ${CMAKE_CURRENT_LIST_DIR}/fexr.c
  ${CMAKE_CURRENT_LIST_DIR}/fpipe.c
  ${CMAKE_CURRENT_LIST_DIR}/subbig.c
  ${CMAKE_CURRENT_LIST_DIR}/pbignum.c
  ${CMAKE_CURRENT_LIST_DIR}/divbig.c
  ${CMAKE_CURRENT_LIST_DIR}/ffasl.c
  ${CMAKE_CURRENT_LIST_DIR}/fasl.c
  ${CMAKE_CURRENT_LIST_DIR}/trace.c
  ${CMAKE_CURRENT_LIST_DIR}/evalf.c
  ${CMAKE_CURRENT_LIST_DIR}/frame.c
  ${CMAKE_CURRENT_LIST_DIR}/lamgc.c
)
 
set(Headers
  ${CMAKE_CURRENT_BINARY_DIR}/config.h
  
  ${CMAKE_CURRENT_LIST_DIR}/h/README.txt.h

  ${CMAKE_CURRENT_LIST_DIR}/h/68kframe.h
  ${CMAKE_CURRENT_LIST_DIR}/h/aout.h
  ${CMAKE_CURRENT_LIST_DIR}/h/catchfram.h
  ${CMAKE_CURRENT_LIST_DIR}/h/chars.h
  ${CMAKE_CURRENT_LIST_DIR}/h/chkrtab.h
  ${CMAKE_CURRENT_LIST_DIR}/h/dfuncs.h
  ${CMAKE_CURRENT_LIST_DIR}/h/dualaout.h
  ${CMAKE_CURRENT_LIST_DIR}/h/duallispo.h
  ${CMAKE_CURRENT_LIST_DIR}/h/frame.h
  ${CMAKE_CURRENT_LIST_DIR}/h/gc.h
  ${CMAKE_CURRENT_LIST_DIR}/h/global.h
  ${CMAKE_CURRENT_LIST_DIR}/h/gtabs.h
  ${CMAKE_CURRENT_LIST_DIR}/h/hpagsiz.h
  ${CMAKE_CURRENT_LIST_DIR}/h/lconf.h
  ${CMAKE_CURRENT_LIST_DIR}/h/lfuncs.h
  ${CMAKE_CURRENT_LIST_DIR}/h/lispo.h
  ${CMAKE_CURRENT_LIST_DIR}/h/ltypes.h
  ${CMAKE_CURRENT_LIST_DIR}/h/sigtab.h
  ${CMAKE_CURRENT_LIST_DIR}/h/structs.h
  ${CMAKE_CURRENT_LIST_DIR}/h/stubs.h
  ${CMAKE_CURRENT_LIST_DIR}/h/tahoeframe.h
  ${CMAKE_CURRENT_LIST_DIR}/h/types.h
  ${CMAKE_CURRENT_LIST_DIR}/h/vaxframe.h
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
    string(JOIN " " RawLispSrcs ${RawLispSrcs})
    
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
