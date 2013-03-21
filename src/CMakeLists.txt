
include_directories( ${CMAKE_SOURCE_DIR} )

function( make_test_executable arg1 arg2 )
    add_executable( test_less_than_${arg1} main.cpp )
    set_target_properties( test_less_than_${arg1}
        PROPERTIES COMPILE_DEFINITIONS "${arg2} -DLESS_THAN" )
    target_link_libraries( test_less_than_${arg1}
        ${Boost_TIMER_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
    )

    add_executable( test_greater_than_${arg1} main.cpp )
    set_target_properties( test_greater_than_${arg1}
        PROPERTIES COMPILE_DEFINITIONS "${arg2} -DGREATER_THAN" )
    target_link_libraries( test_greater_than_${arg1}
        ${Boost_TIMER_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
    )

    add_executable( test_equal_to_${arg1} main.cpp )
    set_target_properties( test_equal_to_${arg1}
        PROPERTIES COMPILE_DEFINITIONS "${arg2} -DEQUAL_TO" )
    target_link_libraries( test_equal_to_${arg1}
        ${Boost_TIMER_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
    )
endfunction()

make_test_executable( hard_coded_functions TYPE1 )
make_test_executable( hard_coded_functions_inline TYPE2 )
make_test_executable( hard_coded_function_objects TYPE3 )
make_test_executable( templated_function_objects_with_hard_coded_member_name TYPE4 )
make_test_executable( bind_expressions_returned_as_boost_functions_from_hard_coded_functions TYPE5 )
make_test_executable( bind_expressions_returned_as_boost_functions TYPE6 )
make_test_executable( bind_expressions_inline TYPE7 )
make_test_executable( operator_wrapper_with_operator_passed_to_it TYPE8 )
make_test_executable( operator_wrapper_with_operator_templated_on_op_type_enable_if TYPE9 )
make_test_executable( operator_wrapper_with_operator_templated_on_op_type_full_specialization TYPE10 )
make_test_executable( operator_wrapper_with_operator_selected_using_enum1 TYPE11 )
make_test_executable( operator_wrapper_with_operator_selected_using_enum2 TYPE12 )
make_test_executable( operator_wrapper_with_operator_selected_using_enum3 TYPE13 )
#make_test_executable( operator_wrapper_clever_lookup TYPE14 )

