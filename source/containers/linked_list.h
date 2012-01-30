/*
  Templated linked list nodes
 */

#ifndef LINKEDLIST
#define LINKEDLIST

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

template<class T> 
class LinkedList;

template<class T>
class DoubleLinkedList;

template<class T>
class ListNode
{
public:
  ListNode();
  ~ListNode();
  
  T AddFront(T Value);
  T GetAt(int RequestedIndex);
  T PopFront();
  
  T m_Value;
private:
  ListNode<T> * m_Next;
  friend class LinkedList<T>;
  friend class DoubleLinkedList<T>;
};
  
template<class T> 
class LinkedList
{
 public:
  LinkedList();
  virtual ~LinkedList();
  
  bool IsEmpty();
  void AddFront(T Value);
  T GetAt(int RequestedIndex);
  T PopFront();
 private:
  ListNode<T> *m_Head;
};

////////////////////////////////////////////////////////////////////////////////
// Double Linked List 
////////////////////////////////////////////////////////////////////////////////

template<class T>
class DoubleListNode:ListNode<T>
{
public:
  DoubleListNode();
  
private:
  DoubleListNode<T> *m_Previous;
  DoubleListNode<T> *m_Next;
  
  friend class DoubleLinkedList<T>;
};

template<class T>
class DoubleLinkedList
{
 public:
  DoubleLinkedList();
  
  bool IsEmpty(); 
  T GetAt(int RequestedIndex);
  T PopFront();
  void AddBack(T Value);
 private:
  DoubleListNode<T> *m_Head;
  DoubleListNode<T> *m_Tail;
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
bool LinkedList<T>::IsEmpty()
{
  return m_Head == NULL;
}

template<class T>
void LinkedList<T>::AddFront(T Value)
{
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
  return CurrentNode->m_Value;
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
  
////////////////////////////////////////////////////////////////////////////////

template<class T>
DoubleListNode<T>::DoubleListNode():ListNode<T>()
{
  m_Previous = NULL;
  m_Next = NULL;
}

template<class T>
DoubleLinkedList<T>::DoubleLinkedList()
{
  m_Head = NULL;
  m_Tail = NULL;
}

template<class T>
bool DoubleLinkedList<T>::IsEmpty()
{
  return m_Head == NULL;
}

template<class T>
T DoubleLinkedList<T>::GetAt(int RequestedIndex)
{
  DoubleListNode<T> *CurrentNode = m_Head;
  int CurrentIndex = 0;
  while(CurrentNode && CurrentIndex < RequestedIndex)
  {
    CurrentNode = CurrentNode->m_Next;
    CurrentIndex++;
  }
  T Result = T();
  if(CurrentNode)
    Result = CurrentNode->m_Value;
  
  return Result;
}

template<class T>
T DoubleLinkedList<T>::PopFront()
{
  if(!m_Head)
    return T();
  
  DoubleListNode<T> *OldHead = m_Head;
  T Result = OldHead->m_Value;
  m_Head = OldHead->m_Next;
  if(m_Head)
    m_Head->m_Previous = NULL;
  else
    m_Tail = NULL;
  OldHead->m_Next = NULL;
  delete OldHead;
  
  return Result;
}

template<class T>
void DoubleLinkedList<T>::AddBack(T Value)
{
  DoubleListNode<T> *NewNode = new DoubleListNode<T>();
  assert(NewNode);
  NewNode->m_Value = Value;
  
  if(!m_Head)
  {
    m_Head = NewNode;
  }
  
  if(m_Tail)
  {
    assert(!m_Tail->m_Next);
    m_Tail->m_Next = NewNode;
    NewNode->m_Previous = m_Tail;
  }
  m_Tail = NewNode;
}

#endif
