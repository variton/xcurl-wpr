
add_library(xjson SHARED 
    json_hdr.cpp)

target_include_directories(xjson PUBLIC
  $<BUILD_INTERFACE:${CMAKE_INCLUDE_PATH}/topology>
  $<BUILD_INTERFACE:${CMAKE_INCLUDE_PATH}/utils>
  $<BUILD_INTERFACE:${CMAKE_INCLUDE_PATH}/xjson>
  $<INSTALL_INTERFACE:include>
)

target_link_options(xjson PRIVATE 
                    $<$<CONFIG:Debug>:--coverage>)

target_compile_options(xjson PRIVATE 
                       -Wall -Wextra -pedantic
                       $<$<CONFIG:Debug>:--coverage -Og -g>
                       $<$<CONFIG:Release>:-O3 -DNDEBUG>)

add_subdirectory(test)
