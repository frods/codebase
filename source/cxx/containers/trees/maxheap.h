/*
    Templated maxheap binary tree
    Requirements:
        The tree is always balanced
        Every node is greater than all nodes below it

    
 */

#ifndef MAXHEAP
#define MAXHEAP

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "heap.h"

//#define DEBUG
template<class T> 
class MaxHeap: public Heap<T>
{
 public:
    MaxHeap();
    virtual ~MaxHeap();
    
protected:
    bool ComesBefore(BinaryTreeNode<T> *First, BinaryTreeNode<T> *Second);

};

////////////////////////////////////////////////////////////////////////////////
// Implementation
////////////////////////////////////////////////////////////////////////////////

template<class T>
MaxHeap<T>::MaxHeap()
{
}

template<class T>
MaxHeap<T>::~MaxHeap()
{
}

template<class T>
bool MaxHeap<T>::ComesBefore(BinaryTreeNode<T> *First, BinaryTreeNode<T> *Second)
{
    return First->m_Value > Second->m_Value;
}

#endif