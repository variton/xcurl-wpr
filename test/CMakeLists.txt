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

add_executable(test_ret
    test_ret.cpp
)

target_include_directories(test_ret PUBLIC
  $<BUILD_INTERFACE:${CMAKE_INCLUDE_PATH}>
  $<BUILD_INTERFACE:${CMAKE_INCLUDE_PATH}/xjson>
  $<BUILD_INTERFACE:${CMAKE_INCLUDE_PATH}/platform>
  $<BUILD_INTERFACE:${CMAKE_INCLUDE_PATH}/ret>
  $<BUILD_INTERFACE:${CMAKE_INCLUDE_PATH}/tpp>
  $<INSTALL_INTERFACE:include>
)


target_link_libraries(test_ret PRIVATE xjson)

target_link_options(test_ret PRIVATE
                    $<$<CONFIG:Debug>:--coverage>)

target_compile_options(test_ret PRIVATE
                       -Wall -Wextra -pedantic
                       $<$<CONFIG:Debug>:--coverage -Og -g>
                       $<$<CONFIG:Release>:-O3 -DNDEBUG>)

add_test(NAME test_ret COMMAND $<TARGET_FILE:test_ret>)

set_tests_properties(test_ret PROPERTIES
  ENVIRONMENT "RC=${TRC}"
)

#==================================================================

add_executable(test_platform
    test_platform.cpp
)

target_include_directories(test_platform PUBLIC
  $<BUILD_INTERFACE:${CMAKE_INCLUDE_PATH}>
  $<BUILD_INTERFACE:${CMAKE_INCLUDE_PATH}/utils>
  $<BUILD_INTERFACE:${CMAKE_INCLUDE_PATH}/platform>
  $<INSTALL_INTERFACE:include>
)


#target_link_libraries(test_platform PRIVATE fmt)

target_link_options(test_platform PRIVATE
                    $<$<CONFIG:Debug>:--coverage>)

target_compile_options(test_platform PRIVATE
                       -Wall -Wextra -pedantic
                       $<$<CONFIG:Debug>:--coverage -Og -g>
                       $<$<CONFIG:Release>:-O3 -DNDEBUG>)

add_test(NAME test_platform COMMAND $<TARGET_FILE:test_platform>)

set_tests_properties(test_platform PROPERTIES
  ENVIRONMENT "RC=${TRC}"
)

#==================================================================

add_executable(test_fio
    test_fio.cpp
)

target_include_directories(test_fio PUBLIC
  $<BUILD_INTERFACE:${CMAKE_INCLUDE_PATH}>
  $<BUILD_INTERFACE:${CMAKE_INCLUDE_PATH}/fio>
  $<BUILD_INTERFACE:${CMAKE_INCLUDE_PATH}/utils>
  $<INSTALL_INTERFACE:include>
)

#target_link_libraries(test_fio PRIVATE platform)

target_link_options(test_fio PRIVATE
                    $<$<CONFIG:Debug>:--coverage>)

target_compile_options(test_fio PRIVATE
                       -Wall -Wextra -pedantic
                       $<$<CONFIG:Debug>:--coverage -Og -g>
                       $<$<CONFIG:Release>:-O3 -DNDEBUG>)

add_test(NAME test_fio COMMAND $<TARGET_FILE:test_fio>)

set_tests_properties(test_fio PROPERTIES
  ENVIRONMENT "RC=${TRC}"
)
