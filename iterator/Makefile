# Makefile for C++ test application

#variables 
LIBS_H		= my_iterator.h 

LIBS_CPP	= my_iterator.cpp 

OBJS		= my_iterator.o	

CC			= g++
CPPFLAGS	= -g -Wall -I. 

#commands
build: compile

compile : $(LIBS_H)
	$(CC) $(CPPFLAGS) -c $(MAIN) $(LIBS_CPP)

clean: 
	rm -f core $(OBJS)

