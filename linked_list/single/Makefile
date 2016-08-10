# Makefile for my_list.t C++ test application

#variables 
PROG		= my_list.test

MAIN		= test_my_list.cpp

LIBS_H		= my_list.h \
			  my_single_unsorted_list.h \
			  my_single_list.h

LIBS_CPP	= my_list.cpp \
			  my_single_unsorted_list.cpp \
			  my_single_list.cpp

OBJS		= test_my_list.o \
			  my_list.o	\
			  my_single_unsorted_list.o \
			  my_single_list.o

CC			= g++
CPPFLAGS	= -g -Wall -I. -I../ -I../../node/

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
