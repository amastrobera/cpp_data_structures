// Queue
// Implementation with the Single list (unsorted)

#ifndef QUEUE_H
#define QUEUE_H

#include <my_queue_interface.h>
#include <my_single_unsorted_list.h>

namespace my_data_structures 
{


template<typename T>
class Queue : public QueueInterface<T>, 
              private SingleUnsortedList<T>
{
public:

    Queue() : SingleUnsortedList<T>() {}
    
    //destrutor is virtual in the base classes, so it will be automatically called
    
    virtual unsigned size()
    {
        return SingleUnsortedList<T>::size();
    }

    virtual void enqueue(T const& item)
    {
        SingleUnsortedList<T>::append(item); 
        //todo: improve the append function in unsorted list
        //      with a d_last pointer to append things, in O(1) instead of O(N)
    }
    
    virtual T const& first() const
    {
        return SingleUnsortedList<T>::top();
    }

    virtual T dequeue()
    {
        return SingleUnsortedList<T>::pop();
    }
};



} //my_data_structures

#endif

