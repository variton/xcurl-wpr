add_executable(test_utils
    test_utils.cpp
)

target_include_directories(test_utils PUBLIC
  $<BUILD_INTERFACE:${CMAKE_INCLUDE_PATH}/utils>
  $<INSTALL_INTERFACE:include>
)

target_link_options(test_utils PRIVATE
                    $<$<CONFIG:Debug>:--coverage>)

target_compile_options(test_utils PRIVATE 
                       -Wall -Wextra -pedantic
                       $<$<CONFIG:Debug>:--coverage -Og -g>
                       $<$<CONFIG:Release>:-O3 -DNDEBUG>)

add_test(NAME test_utils COMMAND $<TARGET_FILE:test_utils>)

set_tests_properties(test_utils PROPERTIES
  ENVIRONMENT "RC=${TRC}"
)

#==================================================================

add_executable(test_xcgen
    test_xcgen.cpp
)

target_include_directories(test_xcgen PUBLIC
  $<BUILD_INTERFACE:${CMAKE_INCLUDE_PATH}>
  $<BUILD_INTERFACE:${CMAKE_INCLUDE_PATH}/utils>
  $<BUILD_INTERFACE:${CMAKE_INCLUDE_PATH}/xcwpr>
  $<BUILD_INTERFACE:${CMAKE_INCLUDE_PATH}/xcgen>
  $<BUILD_INTERFACE:${CMAKE_INCLUDE_PATH}/tpp>
  $<INSTALL_INTERFACE:include>
)


target_link_libraries(test_xcgen PRIVATE xcwpr)

target_link_options(test_xcgen PRIVATE 
                    $<$<CONFIG:Debug>:--coverage>)

target_compile_options(test_xcgen PRIVATE 
                       -Wall -Wextra -pedantic
                       $<$<CONFIG:Debug>:--coverage -Og -g>
                       $<$<CONFIG:Release>:-O3 -DNDEBUG>)

add_test(NAME test_xcgen COMMAND $<TARGET_FILE:test_xcgen>)

set_tests_properties(test_xcgen PROPERTIES
  ENVIRONMENT "RC=${TRC}"
)
