#!/bin/bash
declare -a perm=("123" "132" "213" "231" "312" "321")

for p in "${perm[@]}"
    do
        for x in {A..Z}
        do
            echo "./zygalski $p$x > sheets/$p$x.txt"
            ./zygalski $p$x > sheets/$p$x.txt
        done
    done
