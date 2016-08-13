#include "my_tree.h"

#include <cassert>
#include <iostream>
 
void testTree()
{
    using my_data_structures::Tree;
    
    std::cout << "testTree ... " << std::endl;

    //init
    std::cout << "    * init" << std::endl;
    Tree<int> intTree;
    assert (0 == intTree.size() && "    >>> failed");

    //insert
    std::cout << "    * insert" << std::endl;
    intTree.insert(2);
    intTree.insert(3);
    intTree.insert(1);
    assert (3 == intTree.size() && "    >>> failed");

    
    std::cout << "OK" << std::endl;    
}


int main(int argc, char** argv)
{   
    testTree();
    
    return 0;
}

