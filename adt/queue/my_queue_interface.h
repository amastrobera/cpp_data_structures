// QueueInterface
// Interface

#ifndef QUEUE_INTERFACE_H
#define QUEUE_INTERFACE_H


namespace my_data_structures 
{


template<typename T>
class QueueInterface
{
public:

    virtual unsigned size() = 0;

    virtual void enqueue(T const& item) = 0;
    
    virtual T const& first() const = 0;

    virtual T dequeue() = 0;
    
};



} //my_data_structures

#endif

