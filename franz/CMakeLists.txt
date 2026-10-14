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
add_executable(rawlisp)

set(rawlisp_cc_flags "")

target_compile_options(rawlisp PRIVATE ${rawlisp_cc_flags})
target_include_directories(rawlisp PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./h
  )
# target_link_libraries(rawlisp PRIVATE )

target_compile_definitions(rawlisp PRIVATE
  HOLE=2097152
  PORTABLE=1
)

set(BottomSrc "")
set(MipSrc1   "")
set(MipSrc2   "")
set(MipSrc3   "")
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

message("MipSrc4:     ${MipSrc4}")
target_sources(rawlisp PRIVATE
  ${BottomSrc}
  ${MipSrc1}
  ${MipSrc2}
  ${MipSrc3}
  ${MipSrc4}
  )
  
