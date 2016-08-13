#!/bin/bash

#elementary build script, to remove later

makeAllWithOptions()
{
    #make array
    cd $build_path/dynamic_array 
    make $1

    #make node
    cd $build_path/node
    make $1

    #make linked list
    if [ $# == 0 ] || [ "$1" != "link" ]; then
        cd $build_path/linked_list/list
        make $1
    fi
    cd $build_path/linked_list/single/unsorted
    make $1
    cd $build_path/linked_list/single/sorted
    make $1
    cd $build_path/linked_list/double
    make $1

	#make rb tree
    cd $build_path/tree
    make $1

    #finish, come back
    cd $build_path
}

help()
{
    echo "=== build script for my_data_structures ===\n"
    echo "$ ./build.sh <opt>"
    echo "      <opt>:"
    echo "              default: compile and link them to tsk"
    echo "              -e | --clean: clean obj files and tsk"
    echo "              -c | --compile: compile"
    echo "              -l | --link: link compiled to tsk"
    echo "              -t | --test: run unit test"
    echo "              -m | --memory: run valgrind test on memory usage"
}


#variables
build_path=$(pwd)


if [ $# -ge 1 ]; then
    while [ $# -ge 1 ]; do
        key="$1"
        case $key in
            -h|--help)
            help
            shift 
            ;;
            -e|--clean)
            makeAllWithOptions "clean"
            shift 
            ;;
            -c|--compile)
            makeAllWithOptions "compile"
            shift # past argument
            ;;
            -l|--link)
            makeAllWithOptions "link"
            shift # past argument
            ;;
            -t|--test)
            makeAllWithOptions "test"
            shift # past argument
            ;;
            -m|--memory)
            makeAllWithOptions "memory"
            shift # past argument
            ;;
            --default)
            echo "wrong inputs"
            exit 2
            ;;
        esac
        shift 
    done
else
    makeAllWithOptions
fi
