#include "my_dynamic_array.h"

#include <cassert>
#include <iostream>
 
void testDynamicArray()
{
    using my_data_structures::DynamicArray;
    
    std::cout << "testDynamicArray ... " << std::endl;

    //init
    std::cout << "    * init" << std::endl;
    DynamicArray<std::string> dyno;
    dyno.append("ciao");
    assert (1 == dyno.size() && "    >>> failed");
    
    //operator[]
    std::cout << "    * opeator[]" << std::endl;
    assert ("ciao" == dyno[0] && "    >>> failed");

//    //next
//    std::cout << "    * next" << std::endl;
//    dyno->next = new SingleNode<int>(2);
//    assert (2 == dyno->next->value && "    >>> failed");
//    assert (NULL == dyno->next->next && "    >>> failed");

//    //delete
//    std::cout << "    * delete" << std::endl;
//    delete dyno->next; dyno->next = NULL;
//    assert (NULL == dyno->next && "    >>> failed");

    
    std::cout << "OK" << std::endl;
}


int main(int argc, char** argv)


{
    testDynamicArray();
        
    return 0;
}

