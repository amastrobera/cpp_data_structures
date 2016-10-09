# Makefile for C++ test application

#variables 
PROG		= my_unordered_map.tst

MAIN		= my_unordered_map.t.cpp

LIBS_H		= my_unordered_map.h

LIBS_CPP	= my_unordered_map.cpp 

OBJS		= my_unordered_map.t.o \
			  my_unordered_map.o \
              $(patsubst %.o,../iterator/%.o, my_iterator.o) \
              $(patsubst %.o,../vector/%.o, my_vector.o) \
			  $(patsubst %.o,../node/%.o, my_node.o) \

CC			= g++ --std=c++11
CPPFLAGS	= -g -Wall -I. \
                       -I../iterator \
					   -I../vector \
					   -I../node \

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
