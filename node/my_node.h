// single knot node

#ifndef NULL_H
#define NULL 0
#endif

#ifndef NODE_H
#define NODE_H

namespace my_data_structures 
{

template<typename T>
struct Node
{
    Node(T const& v): value(v) {}
    T value;
};

template<typename T>
struct SingleNode : public Node<T>
{
    SingleNode(T const& v): Node<T>(v), next(NULL) {}
    SingleNode* next;
};

template<typename T>
struct DoubleNode : public Node<T>
{
    DoubleNode(T const& v): Node<T>(v), left(NULL), right(NULL) {}
    DoubleNode* left;
    DoubleNode* right;
};

template<typename T>
struct RBNode : public Node<T>
{
    RBNode(T const& v): Node<T>(v), 
						left(NULL), right(NULL), red(false) {}
    RBNode* left;
    RBNode* right;
    bool red;
};

////need a dynamic array here. todo
//template<typename T>
//struct MultiNode : public Node<T>
//{
//    MultiNode(T const& v, int size);
//    ~MultiNode();
//    append(T const& v); // only unique nodes are added; on duplicate do nothing
//    remove(T const& v);
//    
//    MultiNode* children[];
//    int size;
//};


    
} //my_data_structures

#endif
