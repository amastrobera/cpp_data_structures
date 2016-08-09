# Makefile for my_list.t C++ test application
PROG = my_list.test
MAIN = my_list.t.cpp
CC = g++
CPPFLAGS = -g -Wall -I. -static
OBJS = my_list.o 
$(PROG): $(OBJS)
	$(CC) -o $(PROG) $(MAIN) $(OBJS)
my_list.o : my_list.h
	$(CC) $(CPPFLAGS) -c my_list.cpp
clean: 
	rm -f core $(PROG) $(OBJS)
