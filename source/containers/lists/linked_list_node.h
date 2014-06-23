/*
  Templated linked list nodes
 */

#ifndef LINKEDLISTNODE
#define LINKEDLISTNODE

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

template<class T>
class ListNode
{
public:
  ListNode();
  ~ListNode();

  ListNode<T> *Next();
  ListNode<T> *Reverse();

  T GetValue();
  
  T m_Value;
  ListNode<T> *m_Next;
};
  
////////////////////////////////////////////////////////////////////////////////
// Implementation
////////////////////////////////////////////////////////////////////////////////

template<class T>
ListNode<T>::ListNode()
{
  m_Value = T();
  m_Next = 0;
}

template<class T>
ListNode<T>::~ListNode()
{
  if(!m_Next)
    return;
  
  delete m_Next;
}

template<class T>
ListNode<T> *ListNode<T>::Next()
{
  return m_Next;
}

template<class T>
T ListNode<T>::GetValue()
{
  return m_Value;
}

template<class T>
ListNode<T> *ListNode<T>::Reverse()
{
  if(m_Next == 0)
    return this;

  ListNode<T> *NewHead = m_Next->Reverse();
  
  assert(m_Next->m_Next == 0);
  m_Next->m_Next = this;
  m_Next = 0;

  return NewHead;
}

#endif
