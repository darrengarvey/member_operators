
cmake_minimum_required( VERSION 2.8 )
project( MEMBER_OPERATORS )

find_package(Boost COMPONENTS timer system REQUIRED)
INCLUDE_DIRECTORIES(${INCLUDE_DIRECTORIES} ${Boost_INCLUDE_DIRS})
LINK_DIRECTORIES(${LINK_DIRECTORIES} ${Boost_LIBRARY_DIRS})

#set( CMAKE_CXX_FLAGS "-Wall -std=c++11 -S" )
add_subdirectory( src )

