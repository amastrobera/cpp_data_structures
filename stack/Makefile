# Makefile for C++ test application

#variables 
PROG		= my_stack.tst

MAIN		= my_stack.t.cpp

LIBS_H		= my_stack.h

LIBS_CPP	= my_stack.cpp 

OBJS		= my_stack.t.o \
			  my_stack.o \
			  $(patsubst %.o,../adt/stack/%.o, my_stack_interface.o) \
			  $(patsubst %.o,../node/%.o, my_node.o) \
			  $(patsubst %.o,../linked_list/list/%.o, my_list.o) \
			  $(patsubst %.o,../linked_list/single/unsorted/%.o, my_single_unsorted_list.o) \
              $(patsubst %.o,../iterator/%.o, my_iterator.o) \

CC			= g++ --std=c++11
CPPFLAGS	= -g -Wall -I. \
                       -I../adt/stack \
                       -I../node \
                       -I../linked_list/list \
					   -I../linked_list/single/unsorted \
                       -I../iterator \

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
