#include "my_single_unsorted_list.h"

#include <cassert>
#include <iostream>
 
void testSingleUnsortedList()
{
    using my_data_structures::SingleUnsortedList;
    
    std::cout << "testSingleUnsortedList ... " << std::endl;

    //init
    std::cout << "    * init" << std::endl;
    SingleUnsortedList<int> intList;
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
    
    
    //top and bottom
    std::cout << "    * top and bottom" << std::endl;
    intList.insert(4);
    intList.insert(3);
    intList.append(3);
    intList.append(4);
    intList.append(2);
    //list: 3, 4, 1, 3, 4, 2
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

    //iterator
    std::cout << "    * iterator" << std::endl;
    SingleUnsortedList<int>::iterator it = intList.begin();
    assert (3 == *it && "    >>> failed");
    ++it;
    assert (1 == *it && "    >>> failed");
    --it; //has no effect on a forward list
    assert (1 == *it && "    >>> failed");
    ++it; ++it; ++it; ++it; 
    assert (intList.end() == it && "    >>> failed");
    unsigned i = 0;
    for (it = intList.begin(); it != intList.end(); ++it)
        std::cout << "iter(" << ++i << "): " << *it << " >> ";
    std::cout << std::endl;

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
    testSingleUnsortedList();
        
    return 0;
}

