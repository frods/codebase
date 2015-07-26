/*
    Templated minheap binary tree
    Requirements:
        The tree is always balanced
        Every node is greater than all nodes below it

    
 */

#ifndef MINHEAP
#define MINHEAP

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "heap.h"

template<class T> 
class MinHeap: public Heap<T>
{
public:
    MinHeap();
    virtual ~MinHeap();
    
protected:
    bool ComesBefore(BinaryTreeNode<T> *First, BinaryTreeNode<T> *Second);

};

////////////////////////////////////////////////////////////////////////////////
// Implementation
////////////////////////////////////////////////////////////////////////////////

template<class T>
MinHeap<T>::MinHeap()
{
}

template<class T>
MinHeap<T>::~MinHeap()
{
}

template<class T>
bool MinHeap<T>::ComesBefore(BinaryTreeNode<T> *First, BinaryTreeNode<T> *Second)
{
    return First->m_Value < Second->m_Value;
}

#endif