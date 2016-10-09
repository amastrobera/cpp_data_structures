# Makefile for C++ test application

#variables 
PROG		= my_double_list.tst

MAIN		= my_double_list.t.cpp

LIBS_H		= my_double_list.h

LIBS_CPP	= my_double_list.cpp 

OBJS		= my_double_list.t.o \
			  my_double_list.o \
              $(patsubst %.o,../../iterator/%.o, my_iterator.o) \
			  $(patsubst %.o,../list/%.o, my_list.o)

CC			= g++ --std=c++11 #<limits> to build sentinel node for end() iterator
CPPFLAGS	= -g -Wall -I. \
                       -I../../iterator \
                       -I../list \
                       -I../../node \

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
