
add_executable(test_xcurl
    test_xcurl.cpp
)

target_include_directories(test_xcurl PUBLIC
  $<BUILD_INTERFACE:${CMAKE_INCLUDE_PATH}/cwpr>
  $<BUILD_INTERFACE:${CMAKE_INCLUDE_PATH}/ret>
  $<INSTALL_INTERFACE:include>
)

target_link_libraries(test_xcurl PRIVATE 
                      cwpr 
                      doctest::doctest 
                      fmt::fmt
                      CURL::libcurl)

target_compile_options(test_xcurl PRIVATE 
                       -Wall -Wextra -pedantic
                       $<$<CONFIG:Debug>:-Og -g>
                       $<$<CONFIG:Release>:-O3 -DNDEBUG>)

add_test(NAME test_xcurl COMMAND $<TARGET_FILE:test_xcurl>)

set_tests_properties(test_xcurl PROPERTIES
  ENVIRONMENT "RC=${TRC}"
)
