/*
  Templated binary tree
 */

#ifndef BINARYTREE
#define BINARYTREE

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "binary_tree_node.h"

template<class T> 
class BinaryTree
{
 public:
  BinaryTree();
  virtual ~BinaryTree();
  
  int Length();
  bool IsEmpty();
  virtual bool Contains(T Value);
  virtual void Insert(T Value);
  virtual void Insert(BinaryTreeNode<T> *Node);
  virtual void InsertAt(BinaryTreeNode<T> *Start, BinaryTreeNode<T> *NewNode);
  virtual void Remove(BinaryTreeNode<T> *Node);

  BinaryTreeNode<T> *GetHead();
  
 protected:
  virtual BinaryTreeNode<T> *GetNode(T Value);
  BinaryTreeNode<T> *m_Head;
  int m_Count;
};

////////////////////////////////////////////////////////////////////////////////
// Implementation
////////////////////////////////////////////////////////////////////////////////

template<class T>
BinaryTree<T>::BinaryTree()
{
  m_Head = NULL;
  m_Count = 0;
}

template<class T>
BinaryTree<T>::~BinaryTree()
{
  if(!m_Head)
    return;
  
  delete m_Head;
}

template<class T>
int BinaryTree<T>::Length()
{
  return m_Count;
}

template<class T>
bool BinaryTree<T>::IsEmpty()
{
  return m_Head == NULL;
}

template<class T>
bool BinaryTree<T>::Contains(T Value)
{
  BinaryTreeNode<T> *Node = GetNode(Value);
  return Node != NULL;
}

template<class T>
void BinaryTree<T>::Insert(T Value)
{
  BinaryTreeNode<T> *NewNode = new BinaryTreeNode<T>();
  assert(NewNode);
  NewNode->m_Value = Value;
  Insert(NewNode);
}

template<class T>
void BinaryTree<T>::Insert(BinaryTreeNode<T> *NewNode)
{
  if(!m_Head)
  {
    m_Head = NewNode;
    assert(m_Count == 0);
  }
  else
  {
    InsertAt(m_Head, NewNode);
  }
  m_Count++;
}

template<class T>
void BinaryTree<T>::InsertAt(BinaryTreeNode<T> *Start, BinaryTreeNode<T> *NewNode)
{
  assert(Start != NULL);
  assert(NewNode != NULL);
  printf("Inserting %i at %i", NewNode->m_Value, Start->m_Value);
  if(NewNode->m_Value < Start->m_Value)
  {
    if(Start->m_Left == NULL)
    {
      Start->SetLeft(NewNode);
    }
    else
    {
      InsertAt(Start->m_Left, NewNode);
    }
  }
  else
  {
    if(Start->m_Right == NULL)
    {
      Start->SetRight(NewNode);
    }
    else
    {
      InsertAt(Start->m_Right, NewNode);
    }    
  }
}


template<class T>
void BinaryTree<T>::Remove(BinaryTreeNode<T> *Node)
{
  BinaryTreeNode<T> *NewHead = NULL;
  if(Node->m_Right != NULL)
  {
    // The right child is larger and should replace the removed node to preserve
    // the binary charactersitic of the tree
    NewHead = Node->m_Right;
    NewHead->m_Parent = Node->m_Parent;
  }
  if(Node->m_Left != NULL)
  {
    if(NewHead == NULL)
    {
      NewHead = Node->m_Left;
      NewHead->m_Parent = Node->m_Parent;      
    }
    else
    {
      // Place the lesser tree at the leftmost leaf since it is all less than
      BinaryTreeNode<T> *LeftLeaf = NewHead;
      while(LeftLeaf->m_Left != NULL)
      {
        LeftLeaf = LeftLeaf->m_Left;
      }
      LeftLeaf->SetLeft(Node->m_Left);
    }
  }
  if(Node->m_Parent == NULL)
  {
    assert(Node == m_Head);
    m_Head = NewHead;
  }
  if(m_Head == Node)
  {
    m_Head = NULL;
  }
  delete Node;
  m_Count--;
}

template<class T>
BinaryTreeNode<T> *BinaryTree<T>::GetHead()
{
  return m_Head;
}

template<class T>
BinaryTreeNode<T> *BinaryTree<T>::GetNode(T Value)
{
  if(m_Head == NULL)
  {
    return NULL;
  }
  BinaryTreeNode<T> *CurrentNode = m_Head;
  while(CurrentNode != NULL)
  {
    if(CurrentNode->m_Value == Value)
    {
      return CurrentNode;
    }
    if(CurrentNode->m_Value < Value)
    {
      CurrentNode = CurrentNode->m_Right;
    }
    else
    {
      CurrentNode = CurrentNode->m_Left;
    }
  }
}

#endif