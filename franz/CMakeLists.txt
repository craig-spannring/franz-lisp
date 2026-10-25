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
#  mac          #     tahoe        #     68k              # vax       
#  ----------------------------------------------------------------------
   lisp.c       #     lisp.c       #     lisp.c           # lisp.c    
   eval.c       #     eval.c       #     eval.c           # eval.c    
   eval2.c      #     eval2.c      #     eval2.c          # eval2.c   
   inits.c      #     inits.c      #     inits.c          # inits.c   
   io.c         #     io.c         #     io.c             # io.c      
   error.c      #     error.c      #     error.c          # error.c   
   sysat.c      #     sysat.c      #     sysat.c          # sysat.c   
   lam1.c       #     lam1.c       #     lam1.c           # lam1.c    
   lam2.c       #     lam2.c       #     lam2.c           # lam2.c    
   lam3.c       #     lam3.c       #     lam3.c           # lam3.c    
   lam4.c       #     lam4.c       #     lam4.c           # lam4.c    
   lam5.c       #     lam5.c       #     lam5.c           # lam5.c    
   lam6.c       #     lam6.c       #     lam6.c           # lam6.c    
   lam7.c       #     lam7.c       #     lam7.c           # lam7.c    
   lam8.c       #     lam8.c       #     lam8.c           # lam8.c    
   lam9.c       #     lam9.c       #     lam9.c           # lam9.c    
   lamr.c       #     lamr.c       #     lamr.c           # lamr.c    
   lamp.c       #     lamp.c       #     lamp.c           # lamp.c    
   fex1.c       #     fex1.c       #     fex1.c           # fex1.c    
   fex2.c       #     fex2.c       #     fex2.c           # fex2.c    
   fex3.c       #     fex3.c       #     fex3.c           # fex3.c    
   fex4.c       #     fex4.c       #     fex4.c           # fex4.c    
   fexr.c       #     fexr.c       #     fexr.c           # fexr.c    
   fpipe.c      #     fpipe.c      #     fpipe.c          # fpipe.c   
   subbig.c     #     subbig.c     #     subbig.c         # subbig.c  
   pbignum.c    #     pbignum.c    #     pbignum.c        # pbignum.c 
   divbig.c     #     divbig.c     #     divbig.c         # divbig.c  
   ffasl.c      #     ffasl.c      #     ffasl.c          # ffasl.c   
   fasl.c       #     fasl.c       #     fasl.c           # fasl.c    
   trace.c      #     trace.c      #     trace.c          # trace.c   
   evalf.c      #     evalf.c      #     evalf.c          # evalf.c   
   frame.c      #     frame.c      #     frame.c          # frame.c   
   lamgc.c      #     lamgc.c      #     lamgc.c          # lamgc.c   
 )

target_sources(rawlisp PRIVATE
  # ${MipSrc1}
  # ${MipSrc2}
  # ${MipSrc3}
  ${MipSrc4}

  ${MipSrc1}
  ${MipSrc2}
  ${MipSrc3}

  stubs.c
)
target_compile_definitions(rawlisp PUBLIC IGNORE_STATIC_ASSERT=1)
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
    COMMENT "creating symlink")
