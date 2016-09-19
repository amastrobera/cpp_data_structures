#include "my_single_list.h"

#include <cassert>
#include <iostream>
 
void testSingleList()
{
    using my_data_structures::SingleList;
    using my_data_structures::SingleNode;
    
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

    intList.insert(3);
    intList.insert(2);
    intList.insert(0);
    //list: 0, 1, 2, 3
    
    //iterator
    std::cout << "    * iterator" << std::endl;
    SingleList<int>::iterator it = intList.begin();
    assert (0 == *it && "    >>> failed");
    ++it;
    assert (1 == *it && "    >>> failed");
    --it; //has no effect on a forward list
    assert (1 == *it && "    >>> failed");
    ++it; ++it; ++it;
    assert (intList.end() == it && "    >>> failed");
    unsigned i = 0;
    for (it = intList.begin(); it != intList.end(); ++it)
        std::cout << "iter(" << ++i << "): " << *it << " >> ";
    std::cout << std::endl;
    
    
    //sorted insertions    
    std::cout << "    * sorted insertion" << std::endl;
    assert (4 == intList.size() && "    >>> failed size");
    assert (0 == intList.pop() && "    >>> failed(0)");
    assert (1 == intList.pop() && "    >>> failed(1)");
    assert (2 == intList.pop() && "    >>> failed(2)");
    assert (3 == intList.pop() && "    >>> failed(3)");
    
    //append == insert (because the list is sorted)
    std::cout << "    * append == insert" << std::endl;
    intList.append(4);
    intList.append(2);
    assert (2 == intList.size() && "    >>> failed size");
    assert (2 == intList.at(0) && "    >>> failed size");
    assert (4 == intList.at(1) && "    >>> failed size");
    
    //find
    std::cout << "    * find " << std::endl;
    intList.insert(1);
    intList.insert(3);
    std::pair< SingleNode<int>*, bool > found = intList.find(3);
    assert (true == found.second && "    >>> failed found(3)");
    assert (3 == found.first->value && "    >>> failed found(3)");
    assert (4 == found.first->next->value && "    >>> failed found(4)");

    std::pair< SingleNode<int>*, bool > notFound = intList.find(5);
    assert (false == notFound.second && "    >>> failed not found(5)");
    assert (NULL == notFound.first && "    >>> failed not found(5)");
    
}


int main(int argc, char** argv)
{   
    testSingleList();
    
    return 0;
}

