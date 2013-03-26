#!/bin/sh

tests="less_than greater_than equal_to multi_sort"

function get_sizes_for_compiler_and_test_set {
    compiler="$1"
    test_set="$2"
    for t in build-${compiler}/src/test_${test_set}_*
    do
        strip $t
        echo -e "$compiler\t$test_set\t$(stat -c '%s' $t)\t${t#*test_${test_set}_}"
    done
}

function get_sizes_for_compiler {
    compiler="$1"
    for test_set in $tests;
    do
        get_sizes_for_compiler_and_test_set $compiler $test_set | sort -n -k 3
    done
}

for build_folder in build-*;
do
    compiler="${build_folder#*-}"
    get_sizes_for_compiler $compiler
done

