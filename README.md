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
* vector + iterator (dynamic array) 
* linked_list unordered single + iterator
* linked_list single + iterator (sorted)
* linked_list double + iterator (circular, sorted)
* set (RB tree)
* map (RB tree)
* unordered_map (hash table)
* adt (abstract data types) interfaces
	* stack 
	* queue
* stack
* queue

##### todo #####
* better perf of unsorted_list to make Queue better
* iterator for set, map, hashtable
* add function delete to set and map (erase)
* build script concurrent

#### Modifying STL libs ####
* interval map (derived from c++11 std::map)

