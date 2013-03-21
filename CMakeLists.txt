
cmake_minimum_required( VERSION 2.8 )
project( MEMBER_OPERATORS )

find_package(Boost COMPONENTS timer system REQUIRED)
include_directories(${INCLUDE_DIRECTORIES} ${Boost_INCLUDE_DIRS} include)
link_directories(${LINK_DIRECTORIES} ${Boost_LIBRARY_DIRS})

set( CMAKE_CXX_FLAGS "-Wall" )
add_subdirectory( src )

