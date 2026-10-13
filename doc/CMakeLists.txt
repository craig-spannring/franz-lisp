
# User-configurable settings
set(GROFF_EXECUTABLE "groff" CACHE PATH "Path to groff executable")
set(DOCS_OUTPUT_DIR "${CMAKE_BINARY_DIR}/installed" CACHE PATH "Where to install the generated PDF")

set(DOC_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

# From the original Makefile's RootGenSrc
set(ROOT_GEN_SRC 
  ${CMAKE_CURRENT_SOURCE_DIR}/ch0.n 
  ${CMAKE_CURRENT_SOURCE_DIR}/ch1.n
  ${CMAKE_CURRENT_SOURCE_DIR}/ch2.n
  ${CMAKE_CURRENT_SOURCE_DIR}/ch3.n
  ${CMAKE_CURRENT_SOURCE_DIR}/ch4.n
  ${CMAKE_CURRENT_SOURCE_DIR}/ch5.n
  ${CMAKE_CURRENT_SOURCE_DIR}/ch6.n
  ${CMAKE_CURRENT_SOURCE_DIR}/ch61.n
  ${CMAKE_CURRENT_SOURCE_DIR}/ch7.n
  ${CMAKE_CURRENT_SOURCE_DIR}/ch8.n
  ${CMAKE_CURRENT_SOURCE_DIR}/ch9.n
  ${CMAKE_CURRENT_SOURCE_DIR}/ch10.n
  ${CMAKE_CURRENT_SOURCE_DIR}/ch11.n
  ${CMAKE_CURRENT_SOURCE_DIR}/ch12.n
  ${CMAKE_CURRENT_SOURCE_DIR}/ch13.n
  ${CMAKE_CURRENT_SOURCE_DIR}/ch14.n
  ${CMAKE_CURRENT_SOURCE_DIR}/ch15.n
  ${CMAKE_CURRENT_SOURCE_DIR}/ch16.n
  ${CMAKE_CURRENT_SOURCE_DIR}/ch17.n
  # ${CMAKE_CURRENT_BINARY_DIR}/cha.n
  ${CMAKE_CURRENT_SOURCE_DIR}/chb.n
  ${CMAKE_CURRENT_SOURCE_DIR}/chc.n
)

# Build outputs
set(MANUAL_PDF "${CMAKE_CURRENT_BINARY_DIR}/manual.pdf")
set(MANUAL_X "${CMAKE_CURRENT_BINARY_DIR}/manual.x")

# Collect all chapter sources as dependencies
set(DOC_DEPENDS "")
foreach(name IN LISTS ROOT_GEN_SRC)
  list(APPEND DOC_DEPENDS "${name}")
endforeach()

list(JOIN ROOT_GEN_SRC " " ROOT_GEN_SRC_SPACE) 

# Make sure the docs macro file exists
list(APPEND DOC_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/lmacs")

# Build the manual PDF using tbl + groff.
# This is the equivalent of the original "troff/pall" flow, but with groff and PDF output.
add_custom_command(
  OUTPUT "${MANUAL_PDF}"
  COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_CURRENT_BINARY_DIR}"
  COMMAND /bin/sh -c "\"${GROFF_EXECUTABLE}\" -C -Tpdf -t -me \"${CMAKE_CURRENT_SOURCE_DIR}/lmacs\" ${ROOT_GEN_SRC_SPACE} > \"${MANUAL_PDF}\" 2> \"${MANUAL_X}\""
  DEPENDS ${DOC_DEPENDS} ${CMAKE_CURRENT_LIST_DIR}/CMakeLists.txt
  WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
  COMMENT "Building PDF manual with tbl + groff"
  VERBATIM
)

# Original "vall" target: create the generated output
add_custom_target(vall
  DEPENDS "${MANUAL_PDF}"
  COMMENT "Build the manual PDF"
)

# Original "troff" target:
# In this PDF-based port, this is mapped to the same output as 'vall'
add_custom_target(pdf
  DEPENDS "${MANUAL_PDF}"
  COMMENT "Build the manual PDF (troff-compatible target)"
)

# Install the generated PDF into ${DOCS_OUTPUT_DIR}
add_custom_target(install-manual
  DEPENDS "${MANUAL_PDF}"
  COMMAND ${CMAKE_COMMAND} -E make_directory "${DOCS_OUTPUT_DIR}"
  COMMAND ${CMAKE_COMMAND} -E copy_if_different "${MANUAL_PDF}" "${DOCS_OUTPUT_DIR}/manual.pdf"
  COMMENT "Install manual.pdf to ${DOCS_OUTPUT_DIR}"
)


