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
list(JOIN BottomSrc " " BottomSrcStr)

set(MipSrc1 "")
list(JOIN MipSrc1 " " MipSrc1Str)

set(MipSrc2 "")
list(JOIN MipSrc2 " " MipSrc2Str)

set(MipSrc3 "")
list(JOIN MipSrc3 " " MipSrc3Str)

set(MipSrc4 "")
list(JOIN MipSrc4 " " MipSrc4Str)


set(BottomSrc "")
list(JOIN BottomSrc " " BottomSrcStr)

set(MipSrc1 "")
list(JOIN MipSrc1 " " MipSrc1Str)

set(MipSrc2 "")
list(JOIN MipSrc2 " " MipSrc2Str)

set(MipSrc3 "")
list(JOIN MipSrc3 " " MipSrc3Str)

set(MipSrc4 "")
list(JOIN MipSrc4 " " MipSrc4Str)

target_sources(rawlisp PRIVATE
  lisp.c
  )
  
