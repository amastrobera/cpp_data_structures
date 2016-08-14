#include "my_set.h"

#include <cassert>
#include <iostream>
 
void testSet()
{
    using my_data_structures::Set;
    using my_data_structures::RBNode;
    
    std::cout << "testSet ... " << std::endl;

    //init
    std::cout << "    * init" << std::endl;
    Set<int> intSet;
    assert (0 == intSet.size() && "    >>> failed");

    //insert
    std::cout << "    * insert" << std::endl;
    intSet.insert(2);
    intSet.insert(3);
    intSet.insert(1);
    assert (3 == intSet.size() && "    >>> failed");

    //find
    std::cout << "    * find" << std::endl;
    intSet.insert(8);
    intSet.insert(6);
    intSet.insert(5);
    assert (6 == intSet.size() && "    >>> failed");
    std::pair< RBNode<int>*, bool > found = intSet.find(6);
    assert (true == found.second && "    >>> failed found(6)");
    assert (6 == found.first->value && "    >>> failed found(6)");
    assert (5 == found.first->left->value && "    >>> failed found(5)");
    assert (NULL == found.first->right && "    >>> failed found(NULL)");

    std::pair< RBNode<int>*, bool > notFound = intSet.find(7);
    assert (false == notFound.second && "    >>> failed not found(7)");
    assert (NULL == notFound.first && "    >>> failed not found(7)");

    //rebalance
    std::cout << "    * rebalance" << std::endl;
    intSet.insert(0);
    intSet.insert(-1);
    intSet.insert(-2);
    assert (9 == intSet.size() && "    >>> failed");
    
    std::cout << "OK" << std::endl;    
}


int main(int argc, char** argv)
{   
    testSet();
    
    return 0;
}

