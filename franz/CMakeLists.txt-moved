
add_executable(fl)

target_compile_options(fl PRIVATE ${fl_cc_flags})
target_include_directories(fl PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./h
  )
# target_link_libraries(fl PRIVATE )

target_compile_definitions(fl PRIVATE
  HOLE=2097152
  PORTABLE=1
)

target_sources(fl PRIVATE
  portable/shims.c
  
  # MipObj2     =
  alloc.c
  data.c

  # HoleMipObj2 =
  #Salloc.c
  #Sdata.c

  # HoleMipObj3 =
  rlc.c

  # MipObj4     =
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
