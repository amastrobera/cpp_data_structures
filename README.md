# C++ Data strutures #


This repo contains my implementations of common data structures for aesthetic purposes. 

### Content libraries ###
A file for each structure and its unit test. 
If the implementation includes naked pointers, memory leaks are checked with Valgrind. 

### How to build it  ###
Use the "build.sh" script from the root directory of this repo. Help available. 

#### Making containiers from scratch  ####
C++03, naked pointers, built with Makefile

* node, single and RB node
* iterator (interface)
* vector + iterator (dynamic array, can implement Stack/Queue) 
* linked_list unordered single + iterator (can implement Stack/Queue)
* linked_list single + iterator (sorted)
* linked_list double + iterator (circular, sorted)
* set (RB tree)
* map (RB tree)
* unordered_map (hash table)

##### todo #####
* iterator for set, map, hashtable
* add function delete to set and map (erase)
* build script concurrent

#### Modifying STL libs ####
* interval map (derived from c++11 std::map)

