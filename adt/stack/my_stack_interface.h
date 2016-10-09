// StackInterface
// Interface

#ifndef STACK_INTERFACE_H
#define STACK_INTERFACE_H


namespace my_data_structures 
{


template<typename T>
class StackInterface
{
public:

    virtual unsigned size() = 0;

    virtual void push(T const& item) = 0;
    
    virtual T const& top() const = 0;

    virtual T pop() = 0;
    
};



} //my_data_structures

#endif

