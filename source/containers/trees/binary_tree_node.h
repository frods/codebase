/*
    Templated binary tree node
    Defines tree node which can be used by all binary trees
 */

#ifndef BINARYTREENODE
#define BINARYTREENODE

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sstream>
#include <string.h>

template<class T>
class BinaryTreeNode
{
public:
    BinaryTreeNode();
    ~BinaryTreeNode();
    
    inline void SetLeft(BinaryTreeNode<T> *Child);
    inline void SetRight(BinaryTreeNode<T> *Child);
    inline void Swap(BinaryTreeNode<T> *Node);
    inline void Remove();

    BinaryTreeNode<T> *Grandparent();
    BinaryTreeNode<T> *Uncle();

    BinaryTreeNode<T> *RotateLeft();
    BinaryTreeNode<T> *RotateRight();


    const char *ToString();

    T m_Value;
    BinaryTreeNode<T> * m_Parent;
    BinaryTreeNode<T> * m_Left;
    BinaryTreeNode<T> * m_Right;
};
    
////////////////////////////////////////////////////////////////////////////////
// Implementation
////////////////////////////////////////////////////////////////////////////////

template<class T>
BinaryTreeNode<T>::BinaryTreeNode()
{
    m_Value = T();
    m_Parent = NULL;
    m_Left = NULL;
    m_Right = NULL;
}

template<class T>
BinaryTreeNode<T>::~BinaryTreeNode()
{
    Remove();
    if(m_Left != NULL)
    {
        delete m_Left;
    }

    if(m_Right != NULL)
    {
        delete m_Right;
    }
}

template<class T>
inline void BinaryTreeNode<T>::SetLeft(BinaryTreeNode<T> *Child)
{
    m_Left = Child;
    if(Child != NULL)
        Child->m_Parent = this;
}

template<class T>
inline void BinaryTreeNode<T>::SetRight(BinaryTreeNode<T> *Child)
{
    m_Right = Child;
    if(Child != NULL)
        Child->m_Parent = this;
}

template<class T>
void BinaryTreeNode<T>::Swap(BinaryTreeNode<T> *Node)
{
        // Store this nodes references 
        BinaryTreeNode<T> *Parent = m_Parent;
        BinaryTreeNode<T> *Left = m_Left;
        BinaryTreeNode<T> *Right = m_Right;

        // Set this node to Node
        if(Node->m_Parent == this)
        {
            m_Parent = Node;
        }
        else
        {
            m_Parent = Node->m_Parent;
        }
        if(m_Parent != NULL)
        {
            if(m_Parent->m_Left == Node)
            {
                m_Parent->m_Left = this; 
            }
            else if(m_Parent->m_Right == Node)
            {
                m_Parent->m_Right = this;
            }
        }
        if(Node->m_Left == this)
        {
            SetLeft(Node);
        }
        else
        {
            SetLeft(Node->m_Left);
        }
        if(Node->m_Right == this)
        {
            SetRight(Node);
        }
        else
        {
            SetRight(Node->m_Right);
        }

        // Set Node to what this was
        if(Parent == Node)
        {
            Node->m_Parent = this;
        }
        else
        {
            Node->m_Parent = Parent;
        }
        if(Parent != NULL)
        {
            if(Parent->m_Left == this)
            {
                Parent->m_Left = Node; 
            }
            else if(Parent->m_Right == this)
            {
                Parent->m_Right = Node;
            }
        }
        if(Left == Node)
        {
            Node->SetLeft(this);
        }
        else
        {
            Node->SetLeft(Left);
        }
        if(Right == Node)
        {
            Node->SetRight(this);
        }
        else
        {
            Node->SetRight(Right);
        }
}

template<class T>
void BinaryTreeNode<T>::Remove()
{
    if(m_Parent != NULL)
    {
        if(m_Parent->m_Left == this)
        {
            m_Parent->m_Left = NULL;
        }
        else if(m_Parent->m_Right == this)
        {
            m_Parent->m_Right = NULL;
        }
    }
    if(m_Left != NULL)
    {
        m_Left->m_Parent = NULL;
    }

    if(m_Right != NULL)
    {
        m_Right->m_Parent = NULL;
    }
}

template<class T>
BinaryTreeNode<T> *BinaryTreeNode<T>::Grandparent()
{
    BinaryTreeNode<T> *Grandparent = NULL;
    if(m_Parent != NULL)
    {
        Grandparent = m_Parent->m_Parent;
    }
    return Grandparent;
}

template<class T>
BinaryTreeNode<T> *BinaryTreeNode<T>::Uncle()
{
    BinaryTreeNode<T> *Grandparent = this->Grandparent();
    BinaryTreeNode<T> *Uncle = NULL;
    if(Grandparent != NULL)
    {
        if(Grandparent->m_Left == m_Parent)
        {
            Uncle = Grandparent->m_Right;
        }
        else
        {
            Uncle = Grandparent->m_Left;      
        }
    }
    return Uncle;
}

template<class T>
BinaryTreeNode<T> *BinaryTreeNode<T>::RotateLeft()
{
    // Set the right child as the head
    // This node will be the left child of that node
    // Before
    //     this
    //     /  \
    //    1   NewHead
    //         /  \
    //        2    3
    // After
    //     NewHead
    //     /    \
    //    this   3
    //    / \ 
    //   1  2 
    BinaryTreeNode<T> *Parent = m_Parent;
    BinaryTreeNode<T> *NewHead = m_Right;
    assert(NewHead != NULL);
    SetRight(NewHead->m_Left);
    NewHead->SetLeft(this);
    if(Parent != NULL)
    {
        if(Parent->m_Left == this)
        {
            Parent->SetLeft(NewHead);
        }
        else
        {
            Parent->SetRight(NewHead);
        }
    }
    return NewHead;
}

template<class T>
BinaryTreeNode<T> *BinaryTreeNode<T>::RotateRight()
{
    // Set the left child as the head
    // This node will be the right child of that node
    // Before
    //     this
    //     /   \
    // NewHead  3
    //  /  \
    // 1    2
    // After
    //     NewHead
    //     /   \
    //    1    this
    //         / \
    //        2   3
    BinaryTreeNode<T> *Parent = m_Parent;
    BinaryTreeNode<T> *NewHead = m_Left;
    assert(NewHead != NULL);
    SetLeft(NewHead->m_Right);
    NewHead->SetRight(this);
    if(Parent != NULL)
    {
        if(Parent->m_Left == this)
        {
            Parent->SetLeft(NewHead);
        }
        else
        {
            Parent->SetRight(NewHead);
        }
    }
    return NewHead;
}

template<class T>
const char *BinaryTreeNode<T>::ToString()
{
    std::ostringstream NodeStream;
    NodeStream << "(" << m_Value << ")";
    NodeStream << this << ", ";
    if(m_Parent != NULL)
    {
        NodeStream << "(" << m_Parent->m_Value << ")";
    }
    NodeStream << m_Parent << ", ";
    if(m_Left != NULL)
    {
        NodeStream << "(" << m_Left->m_Value << ")";
    }
    NodeStream << m_Left << ", ";
    if(m_Right != NULL)
    {
        NodeStream << "(" << m_Right->m_Value << ")";
    }
    NodeStream << m_Right;
    printf("%s", NodeStream.str().c_str());
    return "";//NodeStream.str().c_str();
}

#endif