# Makefile for C++ test application

#variables 
PROG		= my_node.tst

MAIN		= my_node.t.cpp
LIBS_H		= my_node.h
LIBS_CPP	= my_node.cpp
OBJS		= my_node.o my_node.t.o

CC			= g++
CPPFLAGS	= -g -Wall -I.

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
