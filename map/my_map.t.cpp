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
    assert (3 == intMap.insert(
                std::pair<std::string, int>("c", 3)).first->value.second && 
                "    >>> failed insertion");
    assert (3 == intMap.size() && "    >>> failed");

    //balancing
    std::cout << "    * balancing" << std::endl;
    intMap.insert(std::pair<std::string, int>("d", 4));
    intMap.insert(std::pair<std::string, int>("e", 5));
    intMap.insert(std::pair<std::string, int>("f", 6));
    intMap.insert(std::pair<std::string, int>("g", 7));
    intMap.insert(std::pair<std::string, int>("h", 8));
    assert (9 == intMap.insert(
                std::pair<std::string, int>("i", 9)).first->value.second && 
                "    >>> failed insertion");    
    intMap.print();
    assert (true == intMap.isBalanced() && "    >>> failed");


    //find
    std::cout << "    * find" << std::endl;
    std::pair< RBNode< std::pair<std::string, int> >*, 
                            bool > found = intMap.find("d");
    assert (true == found.second && "    >>> failed found(d)");
    assert (4 == found.first->value.second && "    >>> failed found(d)");
    std::pair< RBNode< std::pair<std::string, int> >*, 
                            bool > notFound = intMap.find("q");
    assert (false == notFound.second && "    >>> failed not found(q)");
    assert (NULL == notFound.first && "    >>> failed not found(q)");

    //first and last
    std::cout << "    * first and last" << std::endl;
    RBNode< std::pair<std::string, int> >* first = intMap.first();
    assert ("a" == first->value.first && "    >>> failed");
    assert (1 == first->value.second && "    >>> failed");
    RBNode< std::pair<std::string, int> >* last = intMap.last();
    assert ("i" == last->value.first && "    >>> failed");
    assert (9 == last->value.second && "    >>> failed");

    //operator[]
    std::cout << "    * operator[]" << std::endl;
    intMap["e"] = 20;
    assert (20 == intMap["e"] && "    >>> failed");
    intMap["z"] = 10;
    assert (10 == intMap.size() && "    >>> failed");
    assert (10 == intMap["z"] && "    >>> failed");
    
    //at
    std::cout << "    * at" << std::endl;
    intMap.at("e") = 25;
    assert (25 == intMap.at("e") && "    >>> failed");

    //todo: erase
        
    std::cout << "OK" << std::endl;
}


int main(int argc, char** argv)
{   
    testMap();
    
    return 0;
}


