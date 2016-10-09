# Makefile for C++ test application

#variables 
PROG		= my_set.tst

MAIN		= my_set.t.cpp

LIBS_H		= my_set.h

LIBS_CPP	= my_set.cpp 

OBJS		= my_set.t.o \
			  my_set.o \
              $(patsubst %.o,../iterator/%.o, my_iterator.o) \
              $(patsubst %.o,../linked_list/single/unsorted/%.o, \
			  my_single_unsorted_list.o) \

CC			= g++
CPPFLAGS	= -g -Wall -I. \
                       -I../iterator \
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
