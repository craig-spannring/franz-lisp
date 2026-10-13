cmake_minimum_required(VERSION 3.20)

# User-configurable settings
set(GROFF_EXECUTABLE "groff" CACHE PATH "Path to groff executable")
set(DOCS_OUTPUT_DIR "/tmp/usr/lib/lisp" CACHE PATH "Where to install the generated PDF")

set(DOC_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

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
set(UM_APPENDIX_GEN_SRC
  ${CMAKE_CURRENT_BINARY_DIR}/cha.n
  ${CMAKE_CURRENT_SOURCE_DIR}/chb.n
  ${CMAKE_CURRENT_SOURCE_DIR}/chc.n
)
set(UM_SRC 
  ${UM_CHAPTER_SRC_LST}
  ${UM_APPENDIX_GEN_SRC}
)

list(JOIN UM_SRC " " UM_SRC) 
list(JOIN UM_CHAPTER_SRC_LST " " UM_CHAPTER_SRC_STR)

# Output files for User's Manual
set(UM_PDF "${CMAKE_CURRENT_BINARY_DIR}/FRANZ_LISP_Manual.pdf")
set(UM_IDX "${CMAKE_CURRENT_BINARY_DIR}/manual.x")



# Create the Appendix A file (cha.n) from the chapter files.
add_custom_command(
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/cha.n

  COMMAND echo .Ib > ${CMAKE_CURRENT_BINARY_DIR}/um_idx.raw
  COMMAND /bin/sh -c "\"${GROFF_EXECUTABLE}\" -C -t -me -z ${CMAKE_CURRENT_SOURCE_DIR}/lmacs ${UM_CHAPTER_SRC_STR} 2>> ${CMAKE_CURRENT_BINARY_DIR}/um_idx.raw"
  COMMAND grep -E "^\.I" ${CMAKE_CURRENT_BINARY_DIR}/um_idx.raw > ${CMAKE_CURRENT_BINARY_DIR}/cha.n
  
  DEPENDS ${UM_CHAPTER_SRC_LST} "${CMAKE_CURRENT_SOURCE_DIR}/lmacs"
  WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
  COMMENT "Creating Appendix A"
  VERBATIM
)

# Build the user's manual PDF 
add_custom_command(
  OUTPUT "${UM_PDF}"
  COMMAND ${CMAKE_COMMAND} -E echo src_list is ${UM_CHAPTER_SRC_LST} ${UM_APPENDIX_GEN_SRC}

  COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_CURRENT_BINARY_DIR}"
  # COMMAND  /bin/sh -c "\"${GROFF_EXECUTABLE}\" -C -Tpdf -t -me \"${CMAKE_CURRENT_SOURCE_DIR}/lmacs\" ${UM_SRC} > \"${UM_PDF}\" 2> \"${UM_IDX}\""
  COMMAND  /bin/sh -c "echo cmd is \"${GROFF_EXECUTABLE}\" -C -Tpdf -t -me \"${CMAKE_CURRENT_SOURCE_DIR}/lmacs\"  ${UM_SRC} "
  COMMAND  /bin/sh -c "${GROFF_EXECUTABLE} -C -Tpdf -t -me ${CMAKE_CURRENT_SOURCE_DIR}/lmacs ${UM_SRC}" > ${UM_PDF} 2> ${CMAKE_CURRENT_BINARY_DIR}/um_errors.txt
  COMMAND  /bin/sh -c "grep -v -E \"^\.I\" ${CMAKE_CURRENT_BINARY_DIR}/um_errors.txt"
  DEPENDS ${UM_CHAPTER_SRC_LST} ${UM_APPENDIX_GEN_SRC}
  WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
  COMMENT "Building PDF manual with tbl + groff"
  VERBATIM
)

# Create the user's manual
add_custom_target(pdf
  DEPENDS "${UM_PDF}"
  COMMENT "Build the manual PDF (troff-compatible target)"
)

# Install the generated PDF into ${DOCS_OUTPUT_DIR}
add_custom_target(install-manual
  DEPENDS "${UM_PDF}"
  COMMAND ${CMAKE_COMMAND} -E make_directory "${DOCS_OUTPUT_DIR}"
  COMMAND ${CMAKE_COMMAND} -E copy_if_different "${UM_PDF}" "${DOCS_OUTPUT_DIR}/FRANZ_LISP_Manual.pdf"
  COMMENT "Install manual.pdf to ${DOCS_OUTPUT_DIR}"
)


