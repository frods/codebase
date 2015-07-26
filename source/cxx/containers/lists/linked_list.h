/*
  Templated linked list nodes
 */

#ifndef LINKEDLIST
#define LINKEDLIST

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "linked_list_node.h"

template<class T>
class LinkedList
{
 public:
  LinkedList();
  virtual ~LinkedList();
  
  int Length();
  bool IsEmpty();
  void AddFront(T Value);
  T GetAt(int RequestedIndex);
  T PeekFront();
  T PopFront();
  ListNode<T> *GetHead();

 private:
  ListNode<T> *m_Head;
};

////////////////////////////////////////////////////////////////////////////////
// Implementation
////////////////////////////////////////////////////////////////////////////////

template<class T>
LinkedList<T>::LinkedList()
{
  m_Head = NULL;
}

template<class T>
LinkedList<T>::~LinkedList()
{
  if(!m_Head)
    return;
  
  delete m_Head;
}

template<class T>
int LinkedList<T>::Length()
{
  ListNode<T> *CurrentNode = m_Head;
  int CurrentIndex = 0;
  while(CurrentNode)
  {
    CurrentNode = CurrentNode->m_Next;
    CurrentIndex++;
  }
  return CurrentIndex;
}

template<class T>
bool LinkedList<T>::IsEmpty()
{
  return m_Head == NULL;
}

template<class T>
void LinkedList<T>::AddFront(T Value)
{
  ListNode<T> *NewNode = new ListNode<T>();
  NewNode->m_Value = Value;
  if(m_Head != NULL)
    NewNode->m_Next = m_Head;
  m_Head = NewNode;
}

template<class T>
T LinkedList<T>::GetAt(int RequestedIndex)
{
  ListNode<T> *CurrentNode = m_Head;
  int CurrentIndex = 0;
  while(CurrentNode && CurrentIndex <= RequestedIndex)
  {
    CurrentNode = CurrentNode->m_Next;
    CurrentIndex++;
  }
  if(CurrentNode == NULL)
    return 0;

  return CurrentNode->m_Value;
}

template<class T>
T LinkedList<T>::PeekFront()
{
  if(!m_Head)
    return T();
  T Result = m_Head->m_Value;
  return Result;  
}

template<class T>
T LinkedList<T>::PopFront()
{
  if(!m_Head)
    return T();
  
  ListNode<T> *OldHead = m_Head;
  T Result = OldHead->m_Value;
  m_Head = OldHead->m_Next;
  OldHead->m_Next = NULL;
  delete OldHead;
  
  return Result;
}

template<class T>
ListNode<T> *LinkedList<T>::GetHead()
{
  return m_Head;
}

#endif
