cmake_minimum_required(VERSION 3.16)
project(franzlisp)

set(CMAKE_C_STANDARD 99)

### Require out-of-source builds
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
  message(FATAL_ERROR
    "You cannot build in a source directory (or any "
    "directory with a CMakeLists.txt file). Please "
    "create an out-of-tree build subdirectory.\n"
    "To clean up, remove CMakeCache.txt and CMakeFiles.")
endif()
  

include("${CMAKE_CURRENT_LIST_DIR}/cmake/common.cmake")

add_compile_definitions(
  HOLE=2097152
  PORTABLE=1
  SPISFP=1
  
  os_unix=1
  os_unix_ts=1
  OS="unix"
  # OS="vms"
  
  OFFSET=0x0                  
  
  #OFFSET=0x8000               # on sun_4_2beta || sun_4_2 || sun_4_1c 
  #OFFSET=0x40000              # on sun_unisoft 
  #OFFSET=0x800000             # on dual_unisoft 
  #OFFSET=0x20000              # pixel_unisoft 
  #OFFSET=0x20000              # lisa_unisys3 
  #OFFSET=0x0                  # mc500_2_0  
  #OFFSET=0x0                  # m_vax || m_tahoe 

  RTPORTS=1 
  #define NILIS0	 1        /* m_tahoe */
  #define NILIS0	 1        /* m_vax */
  #define RTPORTS 1        /* os_4_3 this O.S. allocates FILE *'s at run-time */
  
  MACHINE="portable"
  #define MACHINE "68k"
  #define MACHINE "vax"
  #define MACHINE "tahoe"
  
  SPISFP=1                       # sun_4_2beta 
  
  #SPISFP=1       /* sun_4_2beta */ 
  #NPINREG=1       /* m_vax || m_tahoe */ 
  
  DOMAIN="nowhere"
  #define DOMAIN  "ucb"
  
  SITE="unknown-site"
  #define SITE    "unknown-site"
  
  TTSIZE=10216  
  #define TTSIZE 10216  /* sun_4_2 || sun_4_2beta || HOLE */
  #define TTSIZE 6120
)
  
# add_subdirectory(tests)
add_subdirectory(utils)
add_subdirectory(franz)
add_subdirectory(doc)


file(CREATE_LINK
  ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json 
  ${CMAKE_CURRENT_LIST_DIR}/compile_commands.json 
  SYMBOLIC
)
file(TOUCH_NOCREATE ${CMAKE_CURRENT_LIST_DIR}/compile_commands.json)

