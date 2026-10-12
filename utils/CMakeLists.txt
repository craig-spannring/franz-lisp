
message("need stuff here")

function(add_util name)
  # Add utility program
  add_executable(${name} ${name}.c)
  # target_sources(${name} PRIVATE 
  # 
  # )
  include_directories(${name} ${CMAKE_CURRENT_LIST_DIR}/../franz/h)
  # target_link_libraries(${name} gtest_main)
  # target_link_libraries(${name} ArgumentParserCXX)
  
  # add_test(NAME ${name} COMMAND ${name})
  
  add_custom_command(TARGET ${name} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink $<TARGET_FILE:${name}> ${CMAKE_CURRENT_LIST_DIR}/${name}
    COMMENT "creating symlink")
  
endfunction()

add_util(append)
add_util(divide)
add_util(tackon)
target_compile_definitions(tackon PRIVATE
  NO_A_OUT=1
)
