# Makefile for C++ test application

#variables 
PROG		= test_unordered_map

MAIN		= my_unordered_map.t.cpp

LIBS_H		= my_unordered_map.h

LIBS_CPP	= my_unordered_map.cpp 

OBJS		= my_unordered_map.t.o \
			  my_unordered_map.o \
              $(patsubst %.o,../vector/%.o, \
			  my_vector.o) \
			  $(patsubst %.o,../linked_list/single/unsorted/%.o, \
			  my_single_unsorted_list.o) \

CC			= g++
CPPFLAGS	= -g -Wall -I. \
					   -I../vector \
					   -I../node \
			           -I../linked_list/list \
					   -I../linked_list/single/unsorted

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
