# C++ Data strutures #


This repo contains my implementations of common data structures for aesthetic purposes. 

### Content libraries ###
A file for each structure and its unit test. 
If the implementation includes naked pointers, memory leaks are checked with Valgrind. 

### How to build it  ###
Use the "build.sh" script from the root directory of this repo. Help available. 

#### Making containiers from scratch  ####
C++03, naked pointers, built with Makefile

* dynamic array (good to implement doubleNode, Stack/Queue)
* node, single and double 
* linked_list unordered single (good to implement Stack/Queue)
* linked_list single (sorted)
* linked_list double (circular, sorted)
* set (rb tree)
* map (rb tree)

##### todo #####
* bug on RB insert algorithm, wrong source 
* add function delete to set and map
* iterators for all 
* build script concurrent

#### Modifying STL libs ####
* interval map (derived from c++11 std::map)

