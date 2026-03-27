
add_executable(api_crawler
    api_crawler.cpp
)

target_include_directories(api_crawler PUBLIC
  $<BUILD_INTERFACE:${CMAKE_INCLUDE_PATH}/>
  $<BUILD_INTERFACE:${CMAKE_INCLUDE_PATH}/xcwpr>
  $<BUILD_INTERFACE:${CMAKE_INCLUDE_PATH}/xcgen>
  $<BUILD_INTERFACE:${CMAKE_INCLUDE_PATH}/tpp>
  $<INSTALL_INTERFACE:include>
)

target_link_libraries(api_crawler PRIVATE 
                      xcwpr
                      fmt::fmt)

target_compile_options(api_crawler PRIVATE
                       -Wall -Wextra -pedantic
                       $<$<CONFIG:Debug>:-Og -g>
                       $<$<CONFIG:Release>:-O3 -DNDEBUG>)

#========================================================================                   
add_executable(robot_crawler
    robot_crawler.cpp
)

target_include_directories(robot_crawler PUBLIC
  $<BUILD_INTERFACE:${CMAKE_INCLUDE_PATH}/>
  $<BUILD_INTERFACE:${CMAKE_INCLUDE_PATH}/xcwpr>
  $<BUILD_INTERFACE:${CMAKE_INCLUDE_PATH}/xcgen>
  $<BUILD_INTERFACE:${CMAKE_INCLUDE_PATH}/tpp>
  $<INSTALL_INTERFACE:include>
)

target_link_libraries(robot_crawler PRIVATE 
                      xcwpr
                      fmt::fmt)

target_compile_options(robot_crawler PRIVATE
                       -Wall -Wextra -pedantic
                       $<$<CONFIG:Debug>:-Og -g>
                       $<$<CONFIG:Release>:-O3 -DNDEBUG>)
