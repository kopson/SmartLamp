#!/bin/bash

show_help() {
    echo "build.sh [param]:"
    echo "  -a  rebuild"
    echo "  -m  build project"
    echo "  -s  run project"
    echo "  -t  build tests"
    echo "  -r  run tests"
    echo "  -c  clean"
    echo "  -h  show help"
}

clean() {
    make clean
}

build_project() {
    find src -maxdepth 1 -mindepth 1 -type d -exec touch {} \+

    echo "## make starts... ##"
    make dirs && make main && echo "## make finished ##"
}

build_tests() { 
    echo "## make starts... ##"
    make dirs && make utest && echo "## make finished ##"
}

run_test() {
    LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$HOME/workspace/CPP/lib/
    export LD_LIBRARY_PATH
    ./out/utest
}

rebuild() {
    echo "## make starts... ##"
    make clean && make all && echo "## make finished ##"
}

run_project() {
    ./out/main
}

OPTIND=1 

while getopts "h?trmsac" opt; do
    case "$opt" in
    h|\?)
        show_help
        exit 0
        ;;
    a)  
        rebuild
        ;;
    c)  
        clean
        ;;  
    t)  
        build_tests
        ;;
    r)  
        run_test
        ;;
    m)  
        build_project
        ;;
    s)
        run_project 
        ;;
    *) 
        rebuild && run_test
        ;;   
    esac
done

shift $((OPTIND-1))

[ "$1" = "--" ] && shift