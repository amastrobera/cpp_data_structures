# Makefile for C++ test application

#variables 
LIBS_H		= my_list.h 

LIBS_CPP	= my_list.cpp 

OBJS		= my_list.o	

CC			= g++
CPPFLAGS	= -g -Wall -I. -I../../node/

#commands
build: compile

compile : $(LIBS_H)
	$(CC) $(CPPFLAGS) -c $(MAIN) $(LIBS_CPP)

clean: 
	rm -f core $(OBJS)

