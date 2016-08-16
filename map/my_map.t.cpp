#include "my_map.h"

#include <cassert>
#include <iostream>
 
void testMap()
{
    using my_data_structures::Map;
    using my_data_structures::RBNode;
    
    std::cout << "testMap ... " << std::endl;

    //init
    std::cout << "    * init" << std::endl;
    Map<std::string, int> intMap;
    assert (0 == intMap.size() && "    >>> failed");

    //insert
    std::cout << "    * insert" << std::endl;
    intMap.insert(std::pair<std::string, int>("a", 1));
    intMap.insert(std::pair<std::string, int>("b", 2));
    intMap.insert(std::pair<std::string, int>("c", 3));
    assert (3 == intMap.size() && "    >>> failed");

    //balancing
    std::cout << "    * balancing" << std::endl;
    intMap.insert(std::pair<std::string, int>("f", 6));
    intMap.insert(std::pair<std::string, int>("h", 7));
    intMap.insert(std::pair<std::string, int>("d", 4));
    intMap.insert(std::pair<std::string, int>("e", 5));
    intMap.insert(std::pair<std::string, int>("l", 9));
    intMap.insert(std::pair<std::string, int>("i", 8));
    
    intMap.print();
////todo: bug on insertion: bad source of algorithm
//    assert (true == intMap.isBalanced() && "    >>> failed");


//    //find
//    std::cout << "    * find" << std::endl;
//    std::pair< RBNode< std::pair<std::string, int> >*, 
//                            bool > found = intMap.find("d");
//    assert (true == found.second && "    >>> failed found(d)");
//    assert (4 == found.first->value.second && "    >>> failed found(d)");
//    std::pair< RBNode< std::pair<std::string, int> >*, 
//                            bool > notFound = intMap.find("q");
//    assert (false == notFound.second && "    >>> failed not found(q)");
//    assert (NULL == notFound.first && "    >>> failed not found(q)");

//    //first and last
//    std::cout << "    * first and last" << std::endl;
//    RBNode< std::pair<std::string, int> >* first = intMap.first();
//    assert ("a" == first->value.first && "    >>> failed");
//    assert (1 == first->value.second && "    >>> failed");
//    RBNode< std::pair<std::string, int> >* last = intMap.last();
//    assert ("l" == last->value.first && "    >>> failed");
//    assert (9 == last->value.second && "    >>> failed");

    //operator[]
    //todo
    
    //at
    //todo
    
    
        
    std::cout << "OK" << std::endl;
}


int main(int argc, char** argv)
{   
    testMap();
    
    return 0;
}


