
add_library(cwpr SHARED 
    xcurl.cpp
    xcurl_global.cpp)

target_link_libraries(cwpr PRIVATE CURL::libcurl
                      $<$<CONFIG:Debug>:--coverage>)

target_include_directories(cwpr PUBLIC
  $<BUILD_INTERFACE:${CMAKE_INCLUDE_PATH}/cwpr>
  $<BUILD_INTERFACE:${CMAKE_INCLUDE_PATH}/ret>
  $<BUILD_INTERFACE:${CMAKE_INCLUDE_PATH}/utils>
  $<INSTALL_INTERFACE:include>
)

target_compile_options(cwpr PRIVATE 
                       -Wall -Wextra -pedantic
                       $<$<CONFIG:Debug>:--coverage -Og -g>
                       $<$<CONFIG:Release>:-O3 -DNDEBUG>)

add_subdirectory(test)
