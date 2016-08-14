#include "my_double_list.h"

#include <cassert>
#include <iostream>
 
void testDoubleList()
{
    using my_data_structures::DoubleList;
    using my_data_structures::DoubleNode;
    
    std::cout << "testDoubleList ... " << std::endl;

    //init
    std::cout << "    * init" << std::endl;
    DoubleList<int> intList;
    assert (0 == intList.size() && "    >>> failed");

    //insert
    std::cout << "    * insert " << std::endl;
    intList.insert(1);
    assert (1 == intList.size() && "    >>> failed");
        
    //top
    std::cout << "    * top " << std::endl;
    intList.insert(2);
    assert (2 == intList.size() && "    >>> failed");
    assert (1 == intList.top() && "    >>> failed");

    //append
    std::cout << "    * append == insert " << std::endl;
    intList.append(0);
    assert (3 == intList.size() && "    >>> failed");
    assert (0 == intList.top() && "    >>> failed");    

    //bottom
    std::cout << "    * bottom " << std::endl;
    assert (2 == intList.bottom() && "    >>> failed");

    //at
    std::cout << "    * at " << std::endl;
    assert (1 == intList.at(1) && "    >>> failed");

    //pop
    std::cout << "    * pop " << std::endl;
    assert (0 == intList.pop() && "    >>> failed");
    assert (2 == intList.size() && "    >>> failed");
    assert (1 == intList.pop() && "    >>> failed");
    assert (1 == intList.size() && "    >>> failed");
    assert (2 == intList.pop() && "    >>> failed");
    assert (0 == intList.size() && "    >>> failed");
 
 
    //find
    std::cout << "    * find " << std::endl;
    intList.insert(2);
    intList.insert(0);
    intList.insert(3);
    intList.insert(0);
    intList.insert(0);
    intList.insert(1);
    std::pair< DoubleNode<int>*, bool > found = intList.find(2);
    assert (true == found.second && "    >>> failed found(2)");
    assert (2 == found.first->value && "    >>> failed found(2)");
    assert (3 == found.first->right->value && "    >>> failed found(2)");
    assert (1 == found.first->left->value && "    >>> failed found(2)");

    std::pair< DoubleNode<int>*, bool > notFound = intList.find(4);
    assert (false == notFound.second && "    >>> failed not found(4)");
    assert (NULL == notFound.first && "    >>> failed not found(4)");

    
    //remove
    std::cout << "    * remove " << std::endl;
    assert (6 == intList.size() && "    >>> failed");
    assert (1 == intList.at(3) && "    >>> failed");
    intList.remove(1);
    assert (5 == intList.size() && "    >>> failed");
    assert (2 == intList.at(3) && "    >>> failed");
    
    //removeAll
    std::cout << "    * removeAll " << std::endl;
    intList.removeAll(0);
    assert (2 == intList.size() && "    >>> failed");
    assert (2 == intList.top() && "    >>> failed");
        
    
    std::cout << "OK" << std::endl;    
}


int main(int argc, char** argv)
{   
    testDoubleList();
    
    return 0;
}

