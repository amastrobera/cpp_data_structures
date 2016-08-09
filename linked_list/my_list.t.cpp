#include "my_list.h"

#include <cassert>
#include <iostream>

using my_data_structures::MyList;
 
void testBasic()
{
    
    std::cout << "testBasic ... " << std::endl;

    //init
    std::cout << "    * init" << std::endl;
    MyList<int> intList;
    assert (0 == intList.size() && "    >>> failed");

    //append
    std::cout << "    * append" << std::endl;
    intList.append(1);
    assert (1 == intList.size() && "    >>> failed");
    assert (1 == intList.top() && "    >>> failed");

    //insert
    intList.insert(0);
    std::cout << "    * insert" << std::endl;
    assert (2 == intList.size() && "    >>> failed");
    assert (0 == intList.top() && "    >>> failed");
    
    //pop
    std::cout << "    * pop" << std::endl;
    assert (0 == intList.pop() && "    >>> failed pop");
    assert (1 == intList.size() && "    >>> failed size");
    
    intList.insert(4);
    intList.insert(3);
    intList.append(3);
    intList.append(4);
    intList.append(2);
    //list: 3, 4, 1, 3, 4, 2
    
    //top and bottom
    std::cout << "    * top and bottom" << std::endl;
    assert (3 == intList.top() && "    >>> failed top");
    assert (2 == intList.bottom() && "    >>> failed bottom");
    
    //at
    std::cout << "    * at" << std::endl;
    assert (1 == intList.at(2) && "    >>> failed at(2)");
    assert (3 == intList.at(0) && "    >>> failed at(0)");
    
    //remove
    std::cout << "    * remove" << std::endl;
    assert (6 == intList.size() && "    >>> failed size pre-remove");
    intList.remove(4);
    assert (5 == intList.size() && "    >>> failed size post-remove");
    assert (1 == intList.at(1) && "    >>> failed at() post-remove");

    //list: 3, 1, 3, 4, 2

    //removeAll
    std::cout << "    * removeAll" << std::endl;
    assert (5 == intList.size() && "    >>> failed size pre-removeAll");
    intList.removeAll(3);
    assert (3 == intList.size() && "    >>> failed size post-removeAll");
    assert (1 == intList.at(0) && "    >>> failed at(0) post-removeAll");
    assert (2 == intList.at(2) && "    >>> failed at(2) post-removeAll");

    //list: 1, 4, 2
    
    std::cout << "OK" << std::endl;
}

int main(int argc, char** argv)
{
    testBasic();
    
    return 0;
}

