#include "my_single_list.h"

#include <cassert>
#include <iostream>
 
void testSingleList()
{
    using my_data_structures::SingleList;
    
    std::cout << "testSingleList ... " << std::endl;

    //init
    std::cout << "    * init" << std::endl;
    SingleList<int> intList;
    assert (0 == intList.size() && "    >>> failed");

    //append
    std::cout << "    * insert one" << std::endl;
    intList.insert(1);
    assert (1 == intList.size() && "    >>> failed");
    assert (1 == intList.top() && "    >>> failed");

    //sorted insertions    
    std::cout << "    * sorted insertion" << std::endl;
    intList.insert(3);
    intList.insert(2);
    intList.insert(0);
    assert (4 == intList.size() && "    >>> failed size");
    assert (0 == intList.pop() && "    >>> failed(0)");
    assert (1 == intList.pop() && "    >>> failed(1)");
    assert (2 == intList.pop() && "    >>> failed(2)");
    assert (3 == intList.pop() && "    >>> failed(3)");
    
    //append is useless
    std::cout << "    * append does nothing" << std::endl;
    intList.append(8);
    assert (0 == intList.size() && "    >>> failed size");
    
    std::cout << "OK" << std::endl;    
}


int main(int argc, char** argv)
{   
    testSingleList();
    
    return 0;
}

