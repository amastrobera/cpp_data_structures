# Makefile for C++ test application

#variables 
PROG		= my_vector.tst

MAIN		= my_vector.t.cpp
LIBS_H		= my_vector.h
LIBS_CPP	= my_vector.cpp
OBJS		= my_vector.o my_vector.t.o \
              $(patsubst %.o,../iterator/%.o, my_iterator.o) \
              # $(patsubst %.o,../string/%.o, my_string.o) \

CC			= g++
CPPFLAGS	= -g -Wall -I. \
                       -I../iterator \
                       # -I../string \

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
