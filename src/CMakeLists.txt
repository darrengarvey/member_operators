
include_directories( ${CMAKE_SOURCE_DIR} )

add_executable( test main.cpp )

target_link_libraries( test
    ${Boost_TIMER_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
)
