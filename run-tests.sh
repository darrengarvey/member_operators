#!/bin/sh

# Run all tests and produce a tab-separated report of
# run-times.
#
# The output is of the format:
#
# compiler  test-type   wall-clock-time     cpu-time    system-time     test-name

tests="less_than greater_than equal_to multi_sort"

function run_tests_for_compiler_and_test_set {
    compiler="$1"
    test_set="$2"
    for t in build-${compiler}/src/test_${test_set}_*
    do
        result="$(./$t | tail -1 | awk '{print $1 "\t" $3 "\t" $6 "\t" $9}' | sed 's/s//g')"
        echo -e "$compiler\t$test_set\t$result\t${t#*test_${test_set}_}"
    done
}

function run_tests_for_compiler {
    compiler="$1"
    for test_set in $tests;
    do
        run_tests_for_compiler_and_test_set $compiler $test_set | sort -n -k 6
    done
}

for build_folder in build-*;
do
    compiler="${build_folder#*-}"
    run_tests_for_compiler $compiler
done

