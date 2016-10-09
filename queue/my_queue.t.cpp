#include "my_queue.h"

#include <cassert>
#include <iostream>
 
void testQueue()
{
    using my_data_structures::Queue;
    
    std::cout << "testQueue ... " << std::endl;

    //init
    std::cout << "    * init" << std::endl;
    Queue<std::string> strQueue;
    assert (0 == strQueue.size() && "    >>> failed");

    //push
    std::cout << "    * enqueue" << std::endl;
    strQueue.enqueue("ciao");
    assert (1 == strQueue.size() && "    >>> failed");
    strQueue.enqueue("bello");
    assert (2 == strQueue.size() && "    >>> failed");
    
    //top
    std::cout << "    * first" << std::endl;
    assert ("ciao" == strQueue.first() && "    >>> failed");
    
    //pop
    std::cout << "    * dequeue" << std::endl;
    assert ("ciao" == strQueue.dequeue() && "    >>> failed");
    assert ("bello" == strQueue.first() && "    >>> failed");
    assert (1 == strQueue.size() && "    >>> failed");
    
    std::cout << "OK" << std::endl;
}


int main(int argc, char** argv)
{   
    testQueue();
    
    return 0;
}


