#include "my_unordered_map.h"

#include <cassert>
#include <iostream>
#include <utility>
 
void testUnorderedMap()
{
    using my_data_structures::UnorderedMap;
    
    std::cout << "testUnorderedMap ... " << std::endl;

    //init
    std::cout << "    * init" << std::endl;
    UnorderedMap<std::string, int> intMap;
    assert (0 == intMap.size() && "    >>> failed");
    
    //insert 
    std::cout << "    * insert" << std::endl;
    intMap.insert(std::pair<std::string, int>("angelo", 30));
    intMap.insert(std::pair<std::string, int>("stefeno", 27));
    assert (2 == intMap.size() && "    >>> failed");
    
    
    std::cout << "OK" << std::endl;
}


int main(int argc, char** argv)
{   
    testUnorderedMap();
    
    return 0;
}


