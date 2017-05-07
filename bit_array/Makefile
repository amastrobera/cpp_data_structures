# Makefile for C++ test application

#variables 
PROG		= my_bit_array.tst

MAIN		= my_bit_array.t.cpp
LIBS_H		= my_bit_array.h
LIBS_CPP	= my_bit_array.cpp
OBJS		= my_bit_array.o my_bit_array.t.o 

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
