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
    std::pair< std::pair<std::string, int>*, bool> in1 =
        intMap.insert(std::pair<std::string, int>("angelo", 30));
    assert (true == in1.second && "    >>> failed");
    std::pair< std::pair<std::string, int>*, bool> in2 =
        intMap.insert(std::pair<std::string, int>("angelo", 100));
    assert (false == in2.second && "    >>> failed");
    std::pair< std::pair<std::string, int>*, bool> in3 =
        intMap.insert(std::pair<std::string, int>("stefeno", 27));
    assert (true == in3.second && "    >>> failed");
    assert (2 == intMap.size() && "    >>> failed");

    //find
    std::cout << "    * find" << std::endl;
    std::pair< std::pair<std::string, int>*, bool> f1 = intMap.find("stefeno");
    assert (true == f1.second && "    >>> failed");
    std::pair< std::pair<std::string, int>*, bool> f2 = intMap.find("nano");
    assert (false == f2.second && "    >>> failed");

    //erase
    std::cout << "    * erase" << std::endl;
    intMap.erase("nano");
    assert (2 == intMap.size() && "    >>> failed");
    intMap.erase("stefeno");
    assert (1 == intMap.size() && "    >>> failed");
    assert (false == intMap.find("stefeno").second && "    >>> failed");

    //operator[]
    std::cout << "    * operator[]" << std::endl;
    intMap["nano"] = 26;
    assert (2 == intMap.size() && "    >>> failed");
    assert (26 == intMap["nano"] && "    >>> failed");
    intMap["angelo"] = 31;
    assert (31 == intMap["angelo"] && "    >>> failed");
    assert (31 == intMap.find("angelo").first->second && "    >>> failed");
    
    std::cout << "OK" << std::endl;
}


int main(int argc, char** argv)
{   
    testUnorderedMap();
    
    return 0;
}


