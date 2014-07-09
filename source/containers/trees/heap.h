/*
    Templated heap binary tree
    Requirements:
        The tree is always balanced
        Every node is greater than all nodes below it

    
 */

#ifndef HEAP
#define HEAP

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "binary_tree_node.h"
#include "binary_tree.h"

//#define DEBUG

template<class T> 
class Heap: public BinaryTree<T>
{
public:
    Heap();
    virtual ~Heap();
    
    void InsertAt(BinaryTreeNode<T> *Start, BinaryTreeNode<T> *NewNode);
    void Remove(BinaryTreeNode<T> *Node);

    void Update(BinaryTreeNode<T> *Node);

    T PopTop();

protected:
    virtual bool ComesBefore(BinaryTreeNode<T> *First, BinaryTreeNode<T> *Second);

private:
    void InsertAtEnd(BinaryTreeNode<T> *Start, BinaryTreeNode<T> *NewNode);
    void BubbleUp(BinaryTreeNode<T> *Start);
    bool IsComplete(BinaryTreeNode<T> *Start);
    int NumChildren(BinaryTreeNode<T> *Start);
    int CompleteNodes(BinaryTreeNode<T> *Start);
    void BubbleDown(BinaryTreeNode<T> *Start);
    BinaryTreeNode<T> *GetLastChild(BinaryTreeNode<T> *Node);

};

////////////////////////////////////////////////////////////////////////////////
// Implementation
////////////////////////////////////////////////////////////////////////////////

template<class T>
Heap<T>::Heap()
{
}

template<class T>
Heap<T>::~Heap()
{
}

template<class T>
void Heap<T>::InsertAt(BinaryTreeNode<T> *Start, BinaryTreeNode<T> *NewNode)
{
    InsertAtEnd(Start, NewNode);
    BubbleUp(NewNode);
}

template<class T>
void Heap<T>::Remove(BinaryTreeNode<T> *Node)
{
    assert(Node != NULL);
    // Find the last added child and replace the removed node with it
    BinaryTreeNode<T> *LastChild = GetLastChild(Heap::m_Head);
    if(LastChild != NULL)
    {
        LastChild->Swap(Node);
        Node->Remove();
        if(Node == Heap::m_Head)
        {
            Heap::m_Head = LastChild;
        }
        BubbleDown(LastChild);
    }
    if(Heap::m_Head == Node)
    {
        Heap::m_Head = NULL;
    }
    delete Node;
    Heap::m_Count--;
}

template<class T>
void Heap<T>::Update(BinaryTreeNode<T> *Node)
{
    // Check which direction the node needs to move (if at all)
    if(Node->m_Parent != NULL)
    {
        if(ComesBefore(Node, Node->m_Parent))
        {
            BubbleUp(Node);
            return;
        }
    }
    BubbleDown(Node);
}

template<class T>
T Heap<T>::PopTop()
{
    T Result;
    if(BinaryTree<T>::m_Head != NULL)
    {
        Result = BinaryTree<T>::m_Head->m_Value;
        Remove(BinaryTree<T>::m_Head);
    }
    return Result;
}

template<class T>
bool Heap<T>::ComesBefore(BinaryTreeNode<T> *First, BinaryTreeNode<T> *Second)
{
    return First->m_Value < Second->m_Value;
}

template<class T>
void Heap<T>::InsertAtEnd(BinaryTreeNode<T> *Start, BinaryTreeNode<T> *NewNode)
{
    printf("Insert %i under %i\n", NewNode->m_Value, Start->m_Value);
    // Insert NewNode at the first available spot
    if(Start->m_Left == NULL)
    {
        printf("Insert %i left of %i\n", NewNode->m_Value, Start->m_Value);
        Start->SetLeft(NewNode);
    }
    else if(Start->m_Right == NULL)
    {
        printf("Insert %i right of %i\n", NewNode->m_Value, Start->m_Value);
        printf("Start ");
        printf("%s\n", Start->ToString());
        printf("NewNode ");
        printf("%s\n", NewNode->ToString());
        Start->SetRight(NewNode);
    }
    else
    {
        int LeftChildren = NumChildren(Start->m_Left);
        int RightChildren = NumChildren(Start->m_Right);
        int MaxLeftChildren = CompleteNodes(Start->m_Left);
        if((LeftChildren + 1) < MaxLeftChildren || LeftChildren <= RightChildren)
        {
            InsertAtEnd(Start->m_Left, NewNode);
        }
        else
        {
            InsertAtEnd(Start->m_Right, NewNode);
        }
    }
}

template<class T>
void Heap<T>::BubbleUp(BinaryTreeNode<T> *Start)
{
    //Ensure the node is in the right place in the tree
    while(Start->m_Parent != 0 && ComesBefore(Start, Start->m_Parent))
    {
    #ifdef DEBUG
            printf("Swapping %i and %i\n", Start->m_Value, Start->m_Parent->m_Value);
            printf("Start ");
            printf("%s\n", Start->ToString());
            printf("Parent ");
            printf("%s\n", Start->m_Parent->ToString());
            BinaryTreeNode<T> *OldParent = Start->m_Parent;
            if(OldParent->m_Parent != NULL)
            {
                printf("ParentParent ");
                printf("%s\n", OldParent->m_Parent->ToString());
            }
            BinaryTreeNode<T> *OldParentParent = OldParent->m_Parent;
    #endif
        Start->Swap(Start->m_Parent);
    #ifdef DEBUG
        printf("Swapped %i and %i\n", Start->m_Value, OldParent->m_Value);
        printf("Start ");
        printf("%s\n", Start->ToString());
        if(Start->m_Parent != NULL)
        {
            printf("New Parent ");
            printf("%s\n", Start->m_Parent->ToString());
        }
        printf("Old Parent ");
        printf("%s\n", OldParent->ToString());
        if(OldParentParent != NULL)
        {
            printf("Old Parent Parent ");
            printf("%s\n", OldParentParent->ToString());
        }
    #endif
    }
    if(Start->m_Parent == 0)
    {
        Heap::m_Head = Start;
    }
}

template<class T>
bool Heap<T>::IsComplete(BinaryTreeNode<T> *Start)
{
    int Nodes = NumChildren(Start) + 1;
    int MaxNodes = CompleteNodes(Start);
    return Nodes == MaxNodes;
}

template<class T>
int Heap<T>::NumChildren(BinaryTreeNode<T> *Start)
{
    int Num = 0;
    //Perform a depth first search to visit all nodes
    if(Start->m_Left != 0)
    {
        Num++;
        Num += NumChildren(Start->m_Left);
    }
    
    if(Start->m_Right != 0)
    {
        Num++;
        Num += NumChildren(Start->m_Right);
    }
    return Num;
}

template<class T>
int Heap<T>::CompleteNodes(BinaryTreeNode<T> *Start)
{
    // Return the number of nodes needed to complete
    // the subtree of Start depth
    int Depth = 0;
    BinaryTreeNode<T> *Current= Start;
    while(Current != NULL && Current->m_Left != 0)
    {
        Current = Current->m_Left;
        Depth++;
    }
    int Max = (1 << (Depth + 1)) - 1;
    return Max;
}


template<class T>
BinaryTreeNode<T> * Heap<T>::GetLastChild(BinaryTreeNode<T> *Node)
{
    BinaryTreeNode<T> *LastChild = NULL;
    if(Node == NULL)
    {
        return LastChild;
    }
    int leftChildren = 0;
    int leftCompleteChildren = 0;
    int rightChildren = 0;
    int rightCompleteChildren = 0;
    if(Node->m_Right != NULL)
    {
        rightChildren = NumChildren(Node->m_Right);
    }
    if(Node->m_Left != NULL)
    {
        leftChildren = NumChildren(Node->m_Left);
    }
    if(Node->m_Right != NULL && rightChildren == 0 && leftChildren == 0)
    {
        LastChild = Node->m_Right;
    }
    else if(Node->m_Left != NULL && leftChildren == 0 && Node->m_Right == NULL)
    {
        LastChild = Node->m_Left;  
    }
    if(LastChild == NULL)
    {
        rightCompleteChildren = CompleteNodes(Node->m_Right);
        leftCompleteChildren = CompleteNodes(Node->m_Left);
        if(leftCompleteChildren > rightCompleteChildren)
        {
            LastChild = GetLastChild(Node->m_Left);    
        }
        else
        {
            LastChild = GetLastChild(Node->m_Right);
        }
    }
    return LastChild;
}

template<class T>
void Heap<T>::BubbleDown(BinaryTreeNode<T> *Start)
{
    bool LeftSmaller = false;
    bool RightSmaller = false;
    if(Start->m_Left != NULL && ComesBefore(Start->m_Left, Start))
    {
        LeftSmaller = true;
    }
    if(Start->m_Right != NULL && ComesBefore(Start->m_Right, Start))
    {
        RightSmaller = true;
    }
    if(LeftSmaller && RightSmaller)
    {
        if(ComesBefore(Start->m_Right, Start->m_Left))
        {
            RightSmaller = false;
        }
        else
        {
            LeftSmaller = false;
        }
    }
    if(LeftSmaller)
    {
        BinaryTreeNode<T> *StartLeft = Start->m_Left;
        Start->Swap(StartLeft);
        if(Start == Heap::m_Head)
        {
            Heap::m_Head = StartLeft;
        }
        BubbleDown(Start);
    }
    else if(RightSmaller)
    {
        BinaryTreeNode<T> *StartRight = Start->m_Right;
        Start->Swap(StartRight);
        if(Start == Heap::m_Head)
        {
            Heap::m_Head = StartRight;
        }
        BubbleDown(Start);
    }
}

#endif