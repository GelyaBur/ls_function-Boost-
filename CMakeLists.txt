cmake_minimum_required(VERSION 2.8)

find_package(Boost COMPONENTS filesystem)

add_executable(result ls_recur.cpp)

include_directories(${Boost_INCLUDE_DIRS})	

target_link_libraries(result ${Boost_LIBRARIES})


