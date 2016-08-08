#include <assert.h>
#include <cstdlib>
#include <limits>
#include <map>
#include <iostream>

template<class K, class V>
class interval_map {
    friend void IntervalMapTest(char init, int numGen);

private:
    std::map<K,V> m_map;

public:
    // constructor associates whole range of K with val by inserting (K_min, val)
    // into the map
    interval_map( V const& val) {
        m_map.insert(m_map.begin(),
                    std::make_pair(std::numeric_limits<K>::lowest(),val));
    };
    
    interval_map() = delete; //just in case 

    // Assign value val to interval [keyBegin, keyEnd). 
    // Overwrite previous values in this interval. 
    // Do not change values outside this interval.
    // Conforming to the C++ Standard Library conventions, the interval 
    // includes keyBegin, but excludes keyEnd.
    // If !( keyBegin < keyEnd ), this designates an empty interval, 
    // and assign must do nothing.
    void assign( K const& keyBegin, K const& keyEnd, const V& val ) {
        //wrong inputs
        if ( keyBegin >= keyEnd ) {
            return;
        }
        
        //empty map: initialise one of two nodes if the val is not equal to 
        // the initialisation value of the map 
        if ( 1 == m_map.size() ) {
            if ( val != m_map.begin()->second ) {
                m_map[keyBegin] = val;
                m_map[keyEnd] = m_map.begin()->second;
            }
            return;
        }
        
        //consecutive values not allowed from the left-end of the range
        //or from the right-end of the range
        if ( val == (--m_map.upper_bound(keyBegin))->second ||
             val == (--m_map.upper_bound(keyEnd))->second ) {
            return;
        }

        //find entry node for keyBegin needs to be overridden if it exist, 
        // or created with value = val, if it does't
        auto itBegin = --m_map.upper_bound(keyBegin);
        if ( keyBegin == itBegin->first ) {
            itBegin->second = val;
        } else {
            itBegin = (m_map.insert(std::pair<K,V>(keyBegin, val)).first);
        }
        
        //the entry node for keyEnd doesn't need to be overridden, but just
        // created with value = <initial value> if it does not exist
        auto itEnd = --m_map.upper_bound(keyEnd);
        if ( keyEnd > itEnd->first ) {
            itEnd = m_map.insert(std::pair<K,V>(keyEnd, 
                            m_map.begin()->second)).first;
        }

        //remove duplicates: all nodes contained in the range [itBegin, itEnd) 
        ++itBegin;
        for (auto it = itBegin; it != itEnd; ) {
            m_map.erase(it++);
        }
        //and remove all nodes successive to itEnd which have same value 
        auto itFinal = itEnd;
        ++itFinal;
        while (itFinal != m_map.end() && 
              itFinal->second == itEnd->second ) {
            m_map.erase(itFinal++);
        }

    }

    // look-up of the value associated with key
    V const& operator[]( K const& key ) const {
        return ( --m_map.upper_bound(key) )->second;
    }
};



// Many solutions we receive are incorrect. Consider using a randomized test
// to discover the cases that your implementation does not handle correctly.
// We recommend to implement a function IntervalMapTest() here that tests the
// functionality of the interval_map, for example using a map of unsigned int
// intervals to char.

void IntervalMapTest(char init='a', int numGen=5) {
    
    std::cout << "IntervalMapTest ... " << std::endl;
    std::cout << "   ... initialisation" << std::endl;
//    char init = 'a';
    interval_map<int, char> tMap(init);
    assert(1 == tMap.m_map.size() && "    >>> failed");
        
    std::cout << "   ... requesting non-existing key" << std::endl;
    assert(init == tMap[1] && "    >>> failed");
    assert(1 == tMap.m_map.size() && "    >>> failed");

    std::cout << "   ... random generation(" 
              << init << ", " << numGen << ")" << std::endl;
//    int numGen = 2;
    for ( int i = 0; i < numGen; ++i ) {
        //random generation of parameters
        int k1 = rand() % (122-97) + 97;
        int k2 = rand() % (122-97) + 97;
        if (k1 > k2) continue;
        char val = (char)(rand() % (122-97) + 97);

        //printing results for debugging purposes 
        std::cout << "       assign(" << k1 << ", " 
                  << k2 << ", " << val 
                  << "): \n                         ";
        //calling the function
        tMap.assign(k1, k2, val);
        for (auto it = tMap.m_map.begin(); it != tMap.m_map.end(); ++it) {
            std::cout << "[" << it->first << ": " << it->second << "], " ;
        }        
        std::cout << std::endl;
    }
    
}

int main(int argc, char* argv[]) {
    char init='a'; int numGen = 5;
    if ( argc == 3)
    {
        init = **(argv+1);
        numGen = atoi(argv[2]);
    }
    IntervalMapTest(init, numGen);
    return 0;
}
