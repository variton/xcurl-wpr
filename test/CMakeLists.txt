add_executable(test_utils
    test_utils.cpp
)

target_include_directories(test_utils PUBLIC
  $<BUILD_INTERFACE:${CMAKE_INCLUDE_PATH}/utils>
  $<INSTALL_INTERFACE:include>
)

target_compile_options(test_utils PRIVATE 
                       -Wall -Wextra -pedantic
                       $<$<CONFIG:Debug>:-Og -g>
                       $<$<CONFIG:Release>:-O3 -DNDEBUG>)

add_test(NAME test_utils COMMAND $<TARGET_FILE:test_utils>)

set_tests_properties(test_utils PROPERTIES
  ENVIRONMENT "RC=${TRC}"
)
