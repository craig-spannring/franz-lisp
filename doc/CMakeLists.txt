cmake_minimum_required(VERSION 3.20)

# User-configurable settings
set(GROFF_EXECUTABLE "groff" CACHE PATH "Path to groff executable")
# TODO the install path for DOCS_OUTPUT_DIR should be set at the top level CMakeLists.txt file
set(DOCS_OUTPUT_DIR "/tmp/usr/lib/lisp" CACHE PATH "Where to install the generated PDF") 

# Define all the source files that make up the User's Manual.
set(UM_CHAPTER_SRC_LST 
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
)
set(UM_APPENDIX_SRC_LST
  ${CMAKE_CURRENT_BINARY_DIR}/cha.n
  ${CMAKE_CURRENT_SOURCE_DIR}/chb.n
  ${CMAKE_CURRENT_SOURCE_DIR}/chc.n
)
set(UM_SRC 
  ${UM_CHAPTER_SRC_LST}
  ${UM_APPENDIX_SRC_LST}
)

set(SM_SRC ${CMAKE_CURRENT_SOURCE_DIR}/franz.n)

list(JOIN UM_SRC " " UM_SRC) 
list(JOIN UM_CHAPTER_SRC_LST " " UM_CHAPTER_SRC_STR)

# Define the output file names for User's Manual
set(SM_PDF "${CMAKE_CURRENT_BINARY_DIR}/FRANZ_LISP_Internals.pdf")
set(UM_PDF "${CMAKE_CURRENT_BINARY_DIR}/FRANZ_LISP_Manual.pdf")
set(UM_IDX "${CMAKE_CURRENT_BINARY_DIR}/um_idx.tmp")

# Create the Appendix A file (cha.n) from the chapter files.
add_custom_command(
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/cha.n

  COMMAND echo .Ib >  ${UM_IDX}
  COMMAND /bin/sh -c "\"${GROFF_EXECUTABLE}\" -C -t -me -z ${CMAKE_CURRENT_SOURCE_DIR}/lmacs ${UM_CHAPTER_SRC_STR} 2>> \"${UM_IDX}\""
  COMMAND grep -E "^\.I" ${UM_IDX} > ${CMAKE_CURRENT_BINARY_DIR}/cha.n
  
  DEPENDS ${UM_CHAPTER_SRC_LST} "${CMAKE_CURRENT_SOURCE_DIR}/lmacs"
  WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
  COMMENT "Creating Appendix A"
  VERBATIM
)

# Build the user's manual PDF
#
# Note- The format should roughly match
#   https://softwarepreservation.computerhistory.org/LISP/franz/Foderaro-The_FRANZ_LISP_Manual-1980.pdf
add_custom_command(
  OUTPUT "${UM_PDF}"

  COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_CURRENT_BINARY_DIR}"
  COMMAND  /bin/sh -c "${GROFF_EXECUTABLE} -C -Tpdf -t -me ${CMAKE_CURRENT_SOURCE_DIR}/lmacs ${UM_SRC}" > ${UM_PDF} 2> ${CMAKE_CURRENT_BINARY_DIR}/um_errors.txt
  COMMAND  /bin/sh -c "grep -v -E \"^\.I\" ${CMAKE_CURRENT_BINARY_DIR}/um_errors.txt"

  DEPENDS ${UM_CHAPTER_SRC_LST} ${UM_APPENDIX_SRC_LST}
  WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
  COMMENT "Building PDF manual."
  VERBATIM
)

# Create the user's manual
add_custom_target(user-manual
  DEPENDS "${UM_PDF}"
  COMMENT "Creating the manual PDF."
)

# Build the system internals manual PDF
add_custom_command(
  OUTPUT "${SM_PDF}"

  COMMAND  /bin/sh -c "${GROFF_EXECUTABLE} -C -Tpdf -t -me ${CMAKE_CURRENT_SOURCE_DIR}/lmacs ${SM_SRC}" > ${SM_PDF} 2> ${CMAKE_CURRENT_BINARY_DIR}/sm_errors.txt
  # COMMAND  /bin/sh -c "grep -v -E \"^\.I\" ${CMAKE_CURRENT_BINARY_DIR}/sm_errors.txt && true"
  COMMAND  cat ${CMAKE_CURRENT_BINARY_DIR}/sm_errors.txt

  DEPENDS ${SM_SRC} 
  WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
  COMMENT "Building PDF internals manual."
  VERBATIM
)

# Create the user's manual
add_custom_target(internals-manual
  DEPENDS "${SM_PDF}"
  COMMENT "Creating the internals manual PDF."
)

# Install the generated PDFs into ${DOCS_OUTPUT_DIR}
add_custom_target(install-manual
  DEPENDS "${UM_PDF}" "${SM_PDF}"
  COMMAND ${CMAKE_COMMAND} -E make_directory "${DOCS_OUTPUT_DIR}"
  COMMAND ${CMAKE_COMMAND} -E copy_if_different "${UM_PDF}" "${DOCS_OUTPUT_DIR}/FRANZ_LISP_Manual.pdf"
  COMMAND ${CMAKE_COMMAND} -E copy_if_different "${SM_PDF}" "${DOCS_OUTPUT_DIR}/FRANZ_LISP_Internals.pdf"
  COMMENT "Install manual.pdf to ${DOCS_OUTPUT_DIR}"
)

message("  DEPENDS ${SM_PDF}  ${SM_PDF}")
# convenience target to create all docs. 
add_custom_target(docs
  DEPENDS "${SM_PDF}" "${UM_PDF}"
)

