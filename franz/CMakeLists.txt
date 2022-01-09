
add_executable(fl lisp.c)

target_compile_options(fl PRIVATE ${mi_cxx_warnings} ${LIBMODBUS_CFLAGS_OTHER})
target_include_directories(fl PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./h
  )
# target_link_libraries(fl PRIVATE )
# target_sources(fl PRIVATE
