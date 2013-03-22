#!/bin/sh

for t in ./build*/src/test_*;
do
    echo "$(tput bold)$t   Size: $(stat -c '%s' $t) bytes$(tput sgr0)";
    ./$t;
done
