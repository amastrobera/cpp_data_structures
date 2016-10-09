# Makefile for C++ test application

#variables 
LIBS_H		= my_queue_interface.h 

LIBS_CPP	= my_queue_interface.cpp

OBJS		= my_queue_interface.o

CC			= g++
CPPFLAGS	= -g -Wall -I. 

#commands
build: compile

compile : $(LIBS_H)
	$(CC) $(CPPFLAGS) -c $(MAIN) $(LIBS_CPP)

clean: 
	rm -f core $(OBJS)
