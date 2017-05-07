#include "my_bit_array.h"

#include <cassert>
#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>
 
using my_data_structures::BitArray;

void testBitArray()
{  
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

    //copy
    std::cout << "    * copy constructor & assigment operator" << std::endl;
    BitArray baCopy(ba);
    assert (ba.print() ==  baCopy.print() && "    >>> failed copy");
    BitArray baAssigned = ba;
    assert (ba.print() ==  baAssigned.print() && "    >>> failed assignment");

    
    std::cout << "OK" << std::endl;
}

void subsets(int setSize, std::vector<BitArray>& solutions)
{
    solutions.push_back(BitArray(setSize)); //empty set solution

    for (unsigned int index = 1; index <= setSize; ++index)
    {
        unsigned int numPrevSolutions = pow(2, index-1);
        for (unsigned int i = 0; i < numPrevSolutions; ++i)
        {
            BitArray ba = solutions[i];
            ba.set(index-1, true);
            solutions.push_back(ba);
        }
    }
}


void testAllSubsets()
{   
    std::cout << "testAllSubsets ... " << std::endl;
    
    int testSet[] = {1,2,3,4}; //expect 2^4 = 16 combinations (non repeated)
    int setSize = sizeof(testSet)/sizeof(int);

    std::vector<BitArray> solutions;
    subsets(setSize, solutions);

    std::cout << "    * print all solutions" << std::endl;
    std::string solStr;
    for (unsigned int i = 0; i < solutions.size(); ++i)
    {
        BitArray& ba = solutions[i];
        
        std::ostringstream os;
        os << "{";
        for (unsigned int j = 0; j < setSize; ++j)
            if (ba.get(j))
                os << testSet[j] <<  " ";
        os << "}";

        solStr += os.str();
    }
    std::cout << "      " << solStr << std::endl;

    std::cout << "    * size" << std::endl;
    assert(pow(2, setSize) == solutions.size() && "    >>> failed (size soluton)");

    std::cout << "OK" << std::endl; 
}


int main(int argc, char** argv)


{
    testBitArray();
    
    testAllSubsets();

    return 0;
}

