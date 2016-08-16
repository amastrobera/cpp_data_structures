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
    intSet.insert(1);
    intSet.insert(2);
    intSet.insert(3);
    assert (3 == intSet.size() && "    >>> failed");

    //balancing
    std::cout << "    * balancing" << std::endl;
    intSet.insert(8);
    intSet.insert(6);
    intSet.insert(5);
    intSet.insert(0);
    intSet.insert(-1);
    intSet.insert(-2);
    intSet.print();
    assert (true == intSet.isBalanced() && "    >>> failed");

    //find
    std::cout << "    * find" << std::endl;
    std::pair< RBNode<int>*, bool > found = intSet.find(6);
    assert (true == found.second && "    >>> failed found(6)");
    assert (6 == found.first->value && "    >>> failed found(6)");
    std::pair< RBNode<int>*, bool > notFound = intSet.find(7);
    assert (false == notFound.second && "    >>> failed not found(7)");
    assert (NULL == notFound.first && "    >>> failed not found(7)");

    //first and last
    std::cout << "    * first and last" << std::endl;
    RBNode<int>* first = intSet.first();
    RBNode<int>* last = intSet.last();
    assert (-2 == first->value && "    >>> failed");
    assert (8 == last->value && "    >>> failed");
        
    std::cout << "OK" << std::endl;
}


int main(int argc, char** argv)
{   
    testSet();
    
    return 0;
}


