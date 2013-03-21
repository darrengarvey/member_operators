
include_directories( ${CMAKE_SOURCE_DIR} )

add_executable( test_hard_coded_functions main.cpp )
set_target_properties( test_hard_coded_functions
    PROPERTIES COMPILE_DEFINITIONS TYPE1 )
target_link_libraries( test_hard_coded_functions
    ${Boost_TIMER_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
)

add_executable( test_hard_coded_functions_inline main.cpp )
set_target_properties( test_hard_coded_functions_inline
    PROPERTIES COMPILE_DEFINITIONS TYPE2 )
target_link_libraries( test_hard_coded_functions_inline
    ${Boost_TIMER_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
)

add_executable( test_hard_coded_function_objects main.cpp )
set_target_properties( test_hard_coded_function_objects
    PROPERTIES COMPILE_DEFINITIONS TYPE3 )
target_link_libraries( test_hard_coded_function_objects 
    ${Boost_TIMER_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
)

add_executable( test_templated_function_objects_with_hard_coded_member_name main.cpp )
set_target_properties( test_templated_function_objects_with_hard_coded_member_name
    PROPERTIES COMPILE_DEFINITIONS TYPE4 )
target_link_libraries( test_templated_function_objects_with_hard_coded_member_name 
    ${Boost_TIMER_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
)

add_executable( test_bind_expressions_returned_as_boost_functions_from_hard_coded_functions main.cpp )
set_target_properties( test_bind_expressions_returned_as_boost_functions_from_hard_coded_functions
    PROPERTIES COMPILE_DEFINITIONS TYPE5 )
target_link_libraries( test_bind_expressions_returned_as_boost_functions_from_hard_coded_functions 
    ${Boost_TIMER_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
)

add_executable( test_bind_expressions_returned_as_boost_functions main.cpp )
set_target_properties( test_bind_expressions_returned_as_boost_functions
    PROPERTIES COMPILE_DEFINITIONS TYPE6 )
target_link_libraries( test_bind_expressions_returned_as_boost_functions 
    ${Boost_TIMER_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
)

add_executable( test_bind_expressions_inline main.cpp )
set_target_properties( test_bind_expressions_inline
    PROPERTIES COMPILE_DEFINITIONS TYPE7 )
target_link_libraries( test_bind_expressions_inline 
    ${Boost_TIMER_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
)

add_executable( test_operator_wrapper_with_operator_passed_to_it main.cpp )
set_target_properties( test_operator_wrapper_with_operator_passed_to_it
    PROPERTIES COMPILE_DEFINITIONS TYPE8 )
target_link_libraries( test_operator_wrapper_with_operator_passed_to_it 
    ${Boost_TIMER_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
)

add_executable( test_operator_wrapper_with_operator_templated_on_op_type_enable_if main.cpp )
set_target_properties( test_operator_wrapper_with_operator_templated_on_op_type_enable_if
    PROPERTIES COMPILE_DEFINITIONS TYPE9 )
target_link_libraries( test_operator_wrapper_with_operator_templated_on_op_type_enable_if 
    ${Boost_TIMER_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
)

add_executable( test_operator_wrapper_with_operator_templated_on_op_type_full_specialization main.cpp )
set_target_properties( test_operator_wrapper_with_operator_templated_on_op_type_full_specialization
    PROPERTIES COMPILE_DEFINITIONS TYPE10 )
target_link_libraries( test_operator_wrapper_with_operator_templated_on_op_type_full_specialization 
    ${Boost_TIMER_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
)

add_executable( test_operator_wrapper_with_operator_selected_using_enum1 main.cpp )
set_target_properties( test_operator_wrapper_with_operator_selected_using_enum1
    PROPERTIES COMPILE_DEFINITIONS TYPE11 )
target_link_libraries( test_operator_wrapper_with_operator_selected_using_enum1 
    ${Boost_TIMER_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
)

add_executable( test_operator_wrapper_with_operator_selected_using_enum2 main.cpp )
set_target_properties( test_operator_wrapper_with_operator_selected_using_enum2
    PROPERTIES COMPILE_DEFINITIONS TYPE12 )
target_link_libraries( test_operator_wrapper_with_operator_selected_using_enum2 
    ${Boost_TIMER_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
)

add_executable( test_operator_wrapper_with_operator_selected_using_enum3 main.cpp )
set_target_properties( test_operator_wrapper_with_operator_selected_using_enum3
    PROPERTIES COMPILE_DEFINITIONS TYPE13 )
target_link_libraries( test_operator_wrapper_with_operator_selected_using_enum3 
    ${Boost_TIMER_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
)

add_executable( test_operator_wrapper_clever_lookup main.cpp )
set_target_properties( test_operator_wrapper_clever_lookup
    PROPERTIES COMPILE_DEFINITIONS TYPE14 )
target_link_libraries( test_operator_wrapper_clever_lookup 
    ${Boost_TIMER_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
)

