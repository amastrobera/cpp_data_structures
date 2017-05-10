// #include "my_string.h"
#include "my_vector.h"

#include <cassert>
#include <iostream>
 
void testVector()
{
    using my_data_structures::Vector;
    // using my_data_structures::String;
    
    std::cout << "testVector ... " << std::endl;

    //init
    std::cout << "    * init" << std::endl;
    Vector<std::string> dyno;
    
    //append
    std::cout << "    * append" << std::endl;
    dyno.append("bello");
    assert (1 == dyno.size() && "    >>> failed");

    //push
    std::cout << "    * push" << std::endl;
    dyno.push("ciao");
    assert (2 == dyno.size() && "    >>> failed");
    
    //operator[]
    std::cout << "    * opeator[]" << std::endl;
    assert ("ciao" == dyno[0] && "    >>> failed[0]");
    assert ("bello" == dyno[1] && "    >>> failed[1]");

    //iterator
    std::cout << "    * iterator" << std::endl;
    Vector<std::string>::iterator it = dyno.begin();
    assert ("ciao" == *it && "    >>> failed");
    ++it;
    assert ("bello" == *it && "    >>> failed");
    --it;
    assert ("ciao" == *it && "    >>> failed");
    ++it; ++it;
    assert (dyno.end() == it && "    >>> failed");
    unsigned i = 0;
    for (it = dyno.begin(); it != dyno.end(); ++it)
        std::cout << "iter(" << ++i << "): " << *it << " >> ";
    std::cout << std::endl;

    
    //top
    std::cout << "    * top" << std::endl;
    assert ("ciao" == dyno.top() && "    >>> failed");
    
    //bottom
    std::cout << "    * bottom" << std::endl;
    assert ("bello" == dyno.bottom() && "    >>> failed");

    //pop
    std::cout << "    * pop" << std::endl;
    assert ("ciao" == dyno.pop() && "    >>> failed");
    
    //removeAt
    std::cout << "    * removeAt" << std::endl;
    dyno[0] = "bella";
    dyno.append("ciao");
    assert ("bella" == dyno[0] && "    >>> failed[0]");
    assert ("ciao" == dyno[1] && "    >>> failed[1]");
    dyno.removeAt(1);
    assert (1 == dyno.size() && "    >>> failed");


    // //join
    // std::cout << "    * join (from vector)" << std::endl;
    // Vector<String> vec(10);
    // vec.append("ciao");
    // vec.append("bello");
    // vec.append("come");
    // vec.append("va");
    // vec.append("?");
    // String s = String::join(vec, ' ');
    // assert ("ciao bello come va ?" == s && "    >>> failed");
    
    std::cout << "OK" << std::endl;
}


int main(int argc, char** argv)


{
    testVector();
        
    return 0;
}

