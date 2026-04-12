add_executable(test_utils
    test_utils.cpp
)

target_include_directories(test_utils PUBLIC
  $<BUILD_INTERFACE:${CMAKE_INCLUDE_PATH}/utils>
  $<BUILD_INTERFACE:${CMAKE_INCLUDE_PATH}/topology>
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

#==================================================================

add_executable(test_response_hdr
    test_response_hdr.cpp
)

target_include_directories(test_response_hdr PUBLIC
  $<BUILD_INTERFACE:${CMAKE_INCLUDE_PATH}>
  $<BUILD_INTERFACE:${CMAKE_INCLUDE_PATH}/xjson>
  $<BUILD_INTERFACE:${CMAKE_INCLUDE_PATH}/ret>
  $<BUILD_INTERFACE:${CMAKE_INCLUDE_PATH}/tpp>
  $<INSTALL_INTERFACE:include>
)


target_link_libraries(test_response_hdr PRIVATE xjson)

target_link_options(test_response_hdr PRIVATE
                    $<$<CONFIG:Debug>:--coverage>)

target_compile_options(test_response_hdr PRIVATE
                       -Wall -Wextra -pedantic
                       $<$<CONFIG:Debug>:--coverage -Og -g>
                       $<$<CONFIG:Release>:-O3 -DNDEBUG>)

add_test(NAME test_response_hdr COMMAND $<TARGET_FILE:test_response_hdr>)

set_tests_properties(test_response_hdr PROPERTIES
  ENVIRONMENT "RC=${TRC}"
)
