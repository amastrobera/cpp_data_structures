# Makefile for C++ test application

#variables 
PROG		= my_single_list.tst

MAIN		= my_single_list.t.cpp

LIBS_H		= my_single_list.h

LIBS_CPP	= my_single_list.cpp

OBJS		= my_single_list.t.o \
              $(patsubst %.o,../../../iterator/%.o, my_iterator.o) \
			  $(patsubst %.o,../unsorted/%.o, my_single_unsorted_list.o) \

CC			= g++
CPPFLAGS	= -g -Wall -I. \
                       -I../unsorted \
                       -I../../list \
                       -I../../../iterator \
                       -I../../../node \

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
