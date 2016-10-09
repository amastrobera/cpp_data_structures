// Stack
// Implementation with the Single list (unsorted)

#ifndef STACK_H
#define STACK_H

#include <my_stack_interface.h>
#include <my_single_unsorted_list.h>

namespace my_data_structures 
{


template<typename T>
class Stack : public StackInterface<T>, 
              private SingleUnsortedList<T>
{
public:

    Stack() : SingleUnsortedList<T>() {}
    
    //destrutor is virtual in the base classes, so it will be automatically called
    
    virtual unsigned size()
    {
        return SingleUnsortedList<T>::size();
    }

    virtual void push(T const& item)
    {
        SingleUnsortedList<T>::insert(item);
    }
    
    virtual T const& top() const
    {
        return SingleUnsortedList<T>::top();
    }

    virtual T pop()
    {
        return SingleUnsortedList<T>::pop();
    }
};



} //my_data_structures

#endif

