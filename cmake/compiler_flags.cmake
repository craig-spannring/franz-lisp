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
  message("Add flags here")
  # list(APPEND fl_cc_flags "-Wno-error=implicit-function-declaration")
  list(APPEND fl_cc_flags "-Wall")
endif()

#
# Setup flags specific to Clang
#
if ((CMAKE_CXX_COMPILER_ID STREQUAL "Clang") OR (CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang"))
  message("Setting up clang flags.")
  # no Clang specific flags yet
  list(APPEND fl_cc_flags "-ferror-limit=100")
endif()

#
# Setup flags specific to GCC
#
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  message("Setting up gcc flags")
  # no gcc specific flags yet
endif()
