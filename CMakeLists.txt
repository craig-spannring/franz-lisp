cmake_minimum_required(VERSION 3.16)
project(franzlisp)

set(CMAKE_C_STANDARD 89)

### Require out-of-source builds
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You cannot build in a source directory (or any directory with a CMakeLists.txt file). Please make a build subdirectory. Feel free to remove CMakeCache.txt and CMakeFiles.")
  endif()
  

include("${CMAKE_CURRENT_LIST_DIR}/cmake/common.cmake")

  
add_subdirectory(franz)
add_subdirectory(utils)
