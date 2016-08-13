# Makefile for C++ test application

#variables 
PROG		= test_tree

MAIN		= my_tree.t.cpp

LIBS_H		= my_tree.h

LIBS_CPP	= my_tree.cpp 

OBJS		= my_tree.t.o \
			  my_tree.o \
              $(patsubst %.o,../linked_list/single/unsorted/%.o, \
			  my_single_unsorted_list.o)

CC			= g++
CPPFLAGS	= -g -Wall -I. \
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
