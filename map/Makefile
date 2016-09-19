# Makefile for C++ test application

#variables 
PROG		= test_map

MAIN		= my_map.t.cpp

LIBS_H		= my_map.h

LIBS_CPP	= my_map.cpp 

OBJS		= my_map.t.o \
			  my_map.o \
              $(patsubst %.o,../iterator/%.o, my_iterator.o) \
              $(patsubst %.o,../linked_list/single/unsorted/%.o, \
			  my_single_unsorted_list.o) \

CC			= g++ --std=c++11 #needed on <limits>: lowest() for operator[]
CPPFLAGS	= -g -Wall -I. \
                       -I../iterator \
					   -I../node \
			           -I../linked_list/list \
					   -I../linked_list/single/unsorted \

#commands
build: compile link

link: 
	$(CC) -o $(PROG) $(OBJS)

compile : $(LIBS_H)
	$(CC) $(CPPFLAGS) -c $(MAIN) $(LIBS_CPP)

clean: 
	rm -f core $(PROG) $(OBJS)

test: #run unit test
	./$(PROG)

debug:
	gdb $(PROG)

memory: #test of memory leak
	valgrind ./$(PROG)
