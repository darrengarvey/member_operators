
include_directories( ${CMAKE_SOURCE_DIR} )

function( make_test_executable arg1 arg2 arg3 )
    add_executable( test_${arg1} main.cpp )
    set_target_properties( test_${arg1}
        PROPERTIES COMPILE_DEFINITIONS "${arg2} ${arg3}" )
    target_link_libraries( test_${arg1}
        ${Boost_TIMER_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
    )
endfunction()

function( make_test_executables arg1 arg2 )
    make_test_executable( "less_than_${arg1}" ${arg2} "-DLESS_THAN" )
    make_test_executable( "greater_than_${arg1}" ${arg2} "-DGREATER_THAN" )
    make_test_executable( "equal_to_${arg1}" ${arg2} "-DEQUAL_TO" )
    make_test_executable( "multi_sort_${arg1}" ${arg2} "-DLESS_THAN -DGREATER_THAN -DEQUAL_TO" )
endfunction()

make_test_executables( hard_coded_functions TYPE1 )
make_test_executables( hard_coded_functions_inline TYPE2 )
make_test_executables( hard_coded_function_objects TYPE3 )
make_test_executables( templated_function_objects_with_hard_coded_member_name TYPE4 )
make_test_executables( bind_expressions_returned_as_boost_functions_from_hard_coded_functions TYPE5 )
make_test_executables( bind_expressions_returned_as_boost_functions TYPE6 )
make_test_executables( bind_expressions_inline TYPE7 )
make_test_executables( operator_wrapper_with_operator_passed_to_it TYPE8 )
make_test_executables( operator_wrapper_with_operator_templated_on_op_type_enable_if TYPE9 )
make_test_executables( operator_wrapper_with_operator_templated_on_op_type_full_specialization TYPE10 )
make_test_executables( operator_wrapper_with_operator_selected_using_enum1 TYPE11 )
make_test_executables( operator_wrapper_with_operator_selected_using_enum2 TYPE12 )
make_test_executables( operator_wrapper_with_operator_selected_using_enum3 TYPE13 )
#make_test_executable( operator_wrapper_clever_lookup TYPE14 )

