#include "my_stack.h"

#include <cassert>
#include <iostream>
 
void testStack()
{
    using my_data_structures::Stack;
    
    std::cout << "testStack ... " << std::endl;

    //init
    std::cout << "    * init" << std::endl;
    Stack<std::string> strStack;
    assert (0 == strStack.size() && "    >>> failed");

    //push
    std::cout << "    * push" << std::endl;
    strStack.push("bello");
    assert (1 == strStack.size() && "    >>> failed");
    strStack.push("ciao");
    assert (2 == strStack.size() && "    >>> failed");
    
    //top
    std::cout << "    * top" << std::endl;
    assert ("ciao" == strStack.top() && "    >>> failed");
    
    //pop
    std::cout << "    * pop" << std::endl;
    assert ("ciao" == strStack.pop() && "    >>> failed");
    assert (1 == strStack.size() && "    >>> failed");
    
    std::cout << "OK" << std::endl;
}


int main(int argc, char** argv)
{   
    testStack();
    
    return 0;
}


