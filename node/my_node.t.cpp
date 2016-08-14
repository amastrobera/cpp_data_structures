#include "my_node.h"

#include <cassert>
#include <iostream>
 
void testSingleNode()
{
    using my_data_structures::SingleNode;
    
    std::cout << "testSingleNode ... " << std::endl;

    //init
    std::cout << "    * init" << std::endl;
    SingleNode<int>* n1 = new SingleNode<int>(1);
    assert (1 == n1->value && "    >>> failed");
    assert (NULL == n1->next && "    >>> failed");

    //next
    std::cout << "    * next" << std::endl;
    n1->next = new SingleNode<int>(2);
    assert (2 == n1->next->value && "    >>> failed");
    assert (NULL == n1->next->next && "    >>> failed");

    //delete
    std::cout << "    * delete" << std::endl;
    delete n1->next; n1->next = NULL;
    assert (NULL == n1->next && "    >>> failed");
    delete n1;
    
    std::cout << "OK" << std::endl;
}

void testDoubleNode()
{
    using my_data_structures::DoubleNode;
    
    std::cout << "testDoubleNode ... " << std::endl;

    //init
    std::cout << "    * init" << std::endl;
    DoubleNode<int>* n1 = new DoubleNode<int>(1);
    assert (1 == n1->value && "    >>> failed");
    assert (NULL == n1->left && "    >>> failed");
    assert (NULL == n1->right && "    >>> failed");

    //next
    std::cout << "    * append left" << std::endl;
    n1->left = new DoubleNode<int>(2);
    assert (2 == n1->left->value && "    >>> failed");
    assert (NULL == n1->left->left && "    >>> failed");
    assert (NULL == n1->left->right && "    >>> failed");
    
    //delete
    std::cout << "    * delete" << std::endl;
    delete n1->left; n1->left = NULL;
    assert (NULL == n1->left && "    >>> failed");
    delete n1;
    
    std::cout << "OK" << std::endl;
}

void testRBNode()
{
    using my_data_structures::RBNode;
    
    std::cout << "testRBNode ... " << std::endl;

    //init
    std::cout << "    * init" << std::endl;
    RBNode<int>* n1 = new RBNode<int>(1);
    assert (1 == n1->value && "    >>> failed");
    assert (false == n1->red && "    >>> failed");
    assert (NULL == n1->left && "    >>> failed");
    assert (NULL == n1->right && "    >>> failed");

    //next
    std::cout << "    * append left" << std::endl;
    n1->left = new RBNode<int>(2);
    assert (2 == n1->left->value && "    >>> failed");
    assert (NULL == n1->left->left && "    >>> failed");
    assert (NULL == n1->left->right && "    >>> failed");
    
    //checked (red->black)
    std::cout << "    * checked (red->black)" << std::endl;
    n1->red = true;
    assert (true == n1->red && "    >>> failed");
 
    //delete
    std::cout << "    * delete" << std::endl;
    delete n1->left; n1->left = NULL;
    assert (NULL == n1->left && "    >>> failed");
    delete n1;
    
    std::cout << "OK" << std::endl;    
}

void testMultiNode()
{
//todo
//    using my_data_structures::MultiNode;


}


int main(int argc, char** argv)


{
    testSingleNode();
    
    testDoubleNode();
    
    testRBNode();
    
//    testMultiNode();    
    
    return 0;
}

