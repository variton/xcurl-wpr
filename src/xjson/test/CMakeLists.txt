
add_executable(test_json_hdr
    test_json_hdr.cpp
)

target_include_directories(test_json_hdr PUBLIC
  $<BUILD_INTERFACE:${CMAKE_INCLUDE_PATH}/xjson>
  $<BUILD_INTERFACE:${CMAKE_INCLUDE_PATH}/platform>
  $<INSTALL_INTERFACE:include>
)

target_link_libraries(test_json_hdr PRIVATE
                      xjson
                      doctest::doctest
                      fmt::fmt
                      $<$<CONFIG:Debug>:--coverage>)

target_compile_options(test_json_hdr PRIVATE
                       -Wall -Wextra -pedantic
                       $<$<CONFIG:Debug>:--coverage -Og -g>
                       $<$<CONFIG:Release>:-O3 -DNDEBUG>)

add_test(NAME test_json_hdr COMMAND $<TARGET_FILE:test_json_hdr>)

set_tests_properties(test_json_hdr PROPERTIES
  ENVIRONMENT "RC=${TRC}"
)
