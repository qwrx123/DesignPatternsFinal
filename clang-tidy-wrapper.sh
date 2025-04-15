#!/bin/bash
# Linux/Mac clang-tidy wrapper

ARGS=()

for arg in "$@"; do
    case "$arg" in
        (-fmodules-ts|-fdeps-format=*|-fmodule-mapper=*) ;; #Do nothing when you have found problematic flag 
        (*) ARGS+=("$arg") ;; #Add flag when not problematic
    esac
done

exec clang-tidy "${ARGS[@]}"