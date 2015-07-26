/*
    Templated binary tree
 */

#ifndef ITERATORBREADTHFIRST
#define ITERATORBREADTHFIRST

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "binary_tree_node.h"
#include "binary_tree.h"
#include "../lists/double_linked_list.h"

template<class T> 
class BreadthFristTraversal
{
 public:
    BreadthFristTraversal(BinaryTree<T> *Tree);
    virtual ~BreadthFristTraversal();
    
    T Next();
    BinaryTreeNode<T> *NextNode();
    bool HasMore();
    void Reset();
 private:
    DoubleLinkedList<BinaryTreeNode<T> *> m_VisitQueue;
    BinaryTree<T> *m_Tree;
    int m_Visited;
};

////////////////////////////////////////////////////////////////////////////////
// Implementation
////////////////////////////////////////////////////////////////////////////////

template<class T>
BreadthFristTraversal<T>::BreadthFristTraversal(BinaryTree<T> *Tree)
{
    m_Tree = Tree;
    m_VisitQueue.AddBack(m_Tree->GetHead());
    m_Visited = 0;
}

template<class T>
BreadthFristTraversal<T>::~BreadthFristTraversal()
{

}
    
template<class T>
BinaryTreeNode<T> *BreadthFristTraversal<T>::NextNode()
{
    BinaryTreeNode<T> *Result;
    if(!m_VisitQueue.IsEmpty())
    {
        BinaryTreeNode<T> *Current = m_VisitQueue.PopFront();
        // Add Root nodes children to the end of the queue
        if(Current != NULL)
        {
            Result = Current;
            if(Current->m_Left != NULL)
            {
                m_VisitQueue.AddBack(Current->m_Left);
            }
            if(Current->m_Right != NULL)
            {
                m_VisitQueue.AddBack(Current->m_Right);
            }
        }
    }
    return Result;
}

template<class T>
T BreadthFristTraversal<T>::Next()
{
    printf("Get next value\n");
    BinaryTreeNode<T> *Next = NextNode();
    printf("Got next Node %p\n", Next);
    T Result;
    if(Next != NULL)
    {
        printf("Got next value %i\n", Next->m_Value);
        Result = Next->m_Value;
    }
    return Result;
}

template<class T>
bool BreadthFristTraversal<T>::HasMore()
{
    return !m_VisitQueue.IsEmpty();
}

template<class T>
void BreadthFristTraversal<T>::Reset()
{
    m_VisitQueue.Clear();
    m_VisitQueue.AddBack(m_Tree->GetHead());
    m_Visited = 0;
}

#endif