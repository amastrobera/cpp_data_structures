# Makefile for C++ test application

#variables 
PROG		= test_double_list

MAIN		= my_double_list.t.cpp

LIBS_H		= my_double_list.h

LIBS_CPP	= my_double_list.cpp

OBJS		= my_double_list.t.o \
			  $(patsubst %.o,../list/%.o, my_list.o)

CC			= g++
CPPFLAGS	= -g -Wall -I. -I../list -I../../node

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
