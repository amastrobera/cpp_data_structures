#!/bin/bash

#elementary build script, to remove later

#variables
build_path=$(pwd)
# todo: add opt parse to clean, or individual libs

#make array
cd $build_path/dynamic_array
make

#make node
cd $build_path/node
make

#make linked list
cd $build_path/linked_list/list
make
cd $build_path/linked_list/single/unsorted
make
cd $build_path/linked_list/single/sorted
make
cd $build_path/linked_list/double
make

#finish, come back
cd $build_path

