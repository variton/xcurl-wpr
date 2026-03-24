
add_library(xcwpr SHARED 
    xcurl.cpp
    xcurl_global.cpp)

target_link_libraries(xcwpr PRIVATE CURL::libcurl
                      $<$<CONFIG:Debug>:--coverage>)

target_include_directories(xcwpr PUBLIC
  $<BUILD_INTERFACE:${CMAKE_INCLUDE_PATH}/xcwpr>
  $<BUILD_INTERFACE:${CMAKE_INCLUDE_PATH}/ret>
  $<BUILD_INTERFACE:${CMAKE_INCLUDE_PATH}/utils>
  $<INSTALL_INTERFACE:include>
)

target_compile_options(xcwpr PRIVATE 
                       -Wall -Wextra -pedantic
                       $<$<CONFIG:Debug>:--coverage -Og -g>
                       $<$<CONFIG:Release>:-O3 -DNDEBUG>)

add_subdirectory(test)
