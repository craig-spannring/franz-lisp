if (NOT ((CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
      OR (CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
      OR (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")))
  message(FATAL_ERROR "${CMAKE_CXX_COMPILER_ID} is not currently supported")
endif()

set(fl_cc_flags "")

#
# Setup flags common to GCC and Clang
# 
if ((CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    OR (CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
    OR (CMAKE_CXX_COMPILER_ID STREQUAL "GNU"))
  list(APPEND fl_cc_flags "-Wno-error=implicit-function-declaration")
  list(APPEND fl_cc_flags "-Wall")
endif()

#
# Setup flags specific to Clang
#
if ((CMAKE_CXX_COMPILER_ID STREQUAL "Clang") OR (CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang"))
  # no Clang specific flags yet
endif()

#
# Setup flags specific to GCC
#
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  # no gcc specific flags yet
endif()





