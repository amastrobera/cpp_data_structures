# Makefile for C++ test application

#variables 
PROG		= $(patsubst %node/%, test_my_node)
MAIN		= $(patsubst %.t.cpp,node/%.t.cpp, my_node.t.cpp)
LIBS_CPP	= $(patsubst %.cpp,node/%.cpp, my_node.cpp)
OBJS		= $(patsubst %.o,node/%.o, my_node.o) \
			  $(patsubst %.t.o,node/%.t.o, my_node.t.o)

INC_LIBS	= -I.\
			  -Inode/

CC			= g++
CPPFLAGS	= -g -Wall $(INC_LIBS)

#commands
build: 
	echo "options: compile, link"

compile_node:
	$(CC) $(CPPFLAGS) -c $(LIBS_CPP) $(MAIN)

link_node:
	$(CC) -o $(PROG) $(OBJS)

compile: compile_node

link: link_node

clean: $()
	rm -f core $(PROG) $(OBJS)

