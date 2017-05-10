# Makefile for C++ test application

#variables 
PROG		= my_string.tst

MAIN		= my_string.t.cpp
LIBS_H		= my_string.h
LIBS_CPP	= my_string.cpp
OBJS		= my_string.o my_string.t.o \
              $(patsubst %.o,../iterator/%.o, my_iterator.o) \

CC			= g++
CPPFLAGS	= -g -Wall -I. \
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
