/*
  Templated binary tree
 */

#ifndef ITERATORINORDER
#define ITERATORINORDER

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "binary_tree_node.h"
#include "binary_tree.h"

template<class T> 
class InorderTraversal
{
 public:
  InorderTraversal(BinaryTree<T> *Tree);
  virtual ~InorderTraversal();
  
  T Next();
  bool HasMore();
  void Reset();
 private:
  bool m_LeftVisited;
  int m_Visited;
  BinaryTree<T> *m_Tree;
  BinaryTreeNode<T> *m_Current;
};

////////////////////////////////////////////////////////////////////////////////
// Implementation
////////////////////////////////////////////////////////////////////////////////

template<class T>
InorderTraversal<T>::InorderTraversal(BinaryTree<T> *Tree)
{
  m_Tree = Tree;
  m_Current = m_Tree->GetHead();
  m_LeftVisited = false;
  m_Visited = 0;
}

template<class T>
InorderTraversal<T>::~InorderTraversal()
{

}
  
template<class T>
T InorderTraversal<T>::Next()
{
  if(!m_LeftVisited)
  {
    while(m_Current != 0 && m_Current->m_Left != 0)
    {
      m_Current = m_Current->m_Left;
    }
    m_LeftVisited = true;
    m_Visited++;
    return m_Current->m_Value;
  }

  if(m_Current != 0 && m_Current->m_Right != 0)
  {
    m_Current = m_Current->m_Right;
    while(m_Current->m_Left != 0)
    {
      m_Current = m_Current->m_Left;
    }
    m_Visited++;
    return m_Current->m_Value;
  }  
  
  if(m_Current != 0 && m_Current->m_Parent != 0 && m_Current == m_Current->m_Parent->m_Left)
  {
    m_Current = m_Current->m_Parent;
    m_Visited++;
    return m_Current->m_Value;
  }

  while(m_Current != 0 && m_Current->m_Parent != 0 && m_Current == m_Current->m_Parent->m_Right)
  {
    m_Current = m_Current->m_Parent;
  }
  if(m_Current != 0 && m_Current->m_Parent != 0 && m_Current == m_Current->m_Parent->m_Left)
  {
    m_Current = m_Current->m_Parent;
    m_Visited++;
    return m_Current->m_Value;
  }

  m_Current = 0;


  T Result = T();
  return Result;
}

template<class T>
bool InorderTraversal<T>::HasMore()
{
  return m_Visited < m_Tree->Length();
}

template<class T>
void InorderTraversal<T>::Reset()
{
  m_Current = m_Tree->GetHead();
  m_LeftVisited = false;
  m_Visited = 0;
}

#endif