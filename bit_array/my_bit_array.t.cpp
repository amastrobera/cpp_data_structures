#include "my_bit_array.h"

#include <cassert>
#include <iostream>
 
void testBitArray()
{
    using my_data_structures::BitArray;
    
    std::cout << "testBitArray ... " << std::endl;

    //init and print
    std::cout << "    * init and print" << std::endl;
    BitArray ba;
    assert (10 == ba.size() && "    >>> failed");
    assert("0000000000" == ba.print() && "    >>> failed");

    //set and get
    std::cout << "    * set and get" << std::endl; 
    ba.set(3, true);
    assert(true == ba.get(3) && "    >>> failed(1)");
    ba.set(3, false);
    assert(false == ba.get(3) && "    >>> failed(2)");
    ba.set(ba.size()-1, true);
    assert(ba.get(ba.size()-1) && "    >>> failed(3)");
    ba.set(ba.size()-1, false);

    //print
    std::cout << "    * print" << std::endl;
    ba.set(4, true);
    ba.set(8, true);
    assert ("0100010000" ==  ba.print() && "    >>> failed");
    
    std::cout << "OK" << std::endl;
}


int main(int argc, char** argv)


{
    testBitArray();
        
    return 0;
}

