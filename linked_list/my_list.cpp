#include "my_list.h"

#include <stdexcept>

namespace my_data_structures
{

//template<typename T>
//MyList<T>::~MyList()
//{
//    Node<T>* cur = d_root;
//    while (cur)
//    {
//        Node<T>* temp = cur;
//        cur = cur->next;
//        delete temp;
//        --d_size;
//    }
//}

//template<typename T> 
//void MyList<T>::append(T const& value)
//{
//    if (d_root)
//    {
//        d_root = new Node<T>(value);
//        return;
//    }
//    Node<T>* cur = d_root;
//    while (cur->next) cur = cur->next;
//    cur->next = new Node<T>(value);
//    
//    ++d_size;
//}

//template<typename T> 
//void MyList<T>::insert(T const& value)
//{
//    Node<T>* node = new Node<T>(value);
//    node->next = d_root;
//    d_root = node;
//    
//    ++d_size;
//}

//template<typename T> 
//T const& MyList<T>::top()
//{
//    if (d_size == 0) throw std::runtime_error("empty list");
//    return d_root->value;
//}

//template<typename T> 
//T const& MyList<T>::bottom()
//{
//    if (d_size == 0) throw std::runtime_error("empty list");
//    Node<T>* cur = d_root;
//    while (cur->next) cur = cur->next;    
//    return cur->value;
//}

//template<typename T> 
//T const& MyList<T>::at(unsigned const k)
//{
//    if (d_size <= k) throw std::runtime_error("out of range");
//    Node<T>* cur = d_root;
//    for (unsigned i = 0; i < k; ++i) cur = cur->next;
//    return cur->value;
//}

//template<typename T> 
//T MyList<T>::pop()
//{
//    if (d_size == 0) throw std::runtime_error("empty list");
//    T retVal = d_root->value;
//    
//    Node<T>* cur = d_root;
//    d_root = d_root->next;    
//    delete cur;
//    
//    ++d_size;
//    
//    return retVal;
//}


//template<typename T> 
//void MyList<T>::remove(T const& value)
//{
//    if (d_size == 0) throw std::runtime_error("empty list");
//    
//    if (d_root->value == value)
//    {
//        Node<T>* cur = d_root;
//        d_root = d_root->next;
//        delete cur;
//        
//        --d_size;
//        return;
//    }
//    
//    Node<T>* cur = d_root;
//    while (cur->next && 
//           cur->next->value != value) cur = cur->next;
//    if (cur->next && 
//        cur->next->value == value)
//    {
//        Node<T>* tgt = cur->next;
//        cur->next = cur->next->next;    
//        delete tgt;
//        --d_size;    
//    }
//}

//template<typename T> 
//void MyList<T>::removeAll(T const& value)
//{
//    if (d_size == 0) throw std::runtime_error("empty list");
//    
//    //delete forward, from the second to the last
//    Node<T>* cur = d_root;
//    while (cur->next)
//    {
//        if (cur->next->value == value)
//        {
//            Node<T>* tgt = cur->next;
//            cur->next = cur->next->next;    
//            delete tgt;
//            --d_size;
//        }
//        cur = cur->next;
//    }
//    
//    //delete the first, if its value is the target one
//    if (d_root && 
//        d_root->value == value)
//    {
//        Node<T>* cur = d_root;
//        d_root = d_root->next;
//        delete cur;
//        
//        --d_size;
//    }
//}



} //my_data_structures
