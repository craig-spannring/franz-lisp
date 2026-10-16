set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)

set(CMAKE_C_STANDARD 99)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


include(CheckIncludeFiles)
include(CheckFunctionExists)
include(CheckSymbolExists)
include(CheckTypeSize)


include("${CMAKE_CURRENT_LIST_DIR}/compiler_flags.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/system_info.cmake")

