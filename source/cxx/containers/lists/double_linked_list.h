/*
  Templated linked list nodes
 */

#ifndef DOUBLELINKEDLIST
#define DOUBLELINKEDLIST

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "linked_list_node.h"

template<class T>
class DoubleListNode:public ListNode<T>
{
public:
  DoubleListNode();
  DoubleListNode<T> *Next();
    
  DoubleListNode<T> *m_Previous;
  DoubleListNode<T> *m_Next;
  
};

template<class T>
class DoubleLinkedList
{
public:
  DoubleLinkedList();
  
  int Length();
  bool IsEmpty(); 
  T GetAt(int RequestedIndex);
  T PopFront();
  T PopBack();
  void AddFront(T Value);
  void AddBack(T Value);
  void Remove(DoubleListNode<T> *Node);

  bool Contains(T Value);

  void Clear();

  DoubleListNode<T> *GetHead();
  DoubleListNode<T> *GetTail();
private:
  DoubleListNode<T> *m_Head;
  DoubleListNode<T> *m_Tail;
};

////////////////////////////////////////////////////////////////////////////////
// Implementation
////////////////////////////////////////////////////////////////////////////////

template<class T>
DoubleListNode<T>::DoubleListNode():ListNode<T>()
{
  m_Previous = NULL;
  m_Next = NULL;
}

template<class T>
DoubleListNode<T> *DoubleListNode<T>::Next()
{
  return m_Next;
}

template<class T>
DoubleLinkedList<T>::DoubleLinkedList()
{
  m_Head = NULL;
  m_Tail = NULL;
}

template<class T>
int DoubleLinkedList<T>::Length()
{
  DoubleListNode<T> *CurrentNode = m_Head;
  int CurrentIndex = 0;
  while(CurrentNode)
  {
    CurrentNode = CurrentNode->m_Next;
    CurrentIndex++;
  }
  return CurrentIndex;
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
  if(m_Head == NULL)
    return T();
  
  DoubleListNode<T> *OldHead = m_Head;
  T Result = OldHead->m_Value;
  Remove(OldHead);
  delete OldHead;
  return Result;
}

template<class T>
T DoubleLinkedList<T>::PopBack()
{
  if(!m_Tail)
    return T();
  
  DoubleListNode<T> *OldTail = m_Tail;
  T Result = OldTail->m_Value;
  Remove(OldTail);
  delete OldTail;
  return Result;
}

template<class T>
void DoubleLinkedList<T>::AddFront(T Value)
{
  DoubleListNode<T> *NewNode = new DoubleListNode<T>();
  assert(NewNode);
  NewNode->m_Value = Value;
  
  if(m_Head != NULL)
  {
    m_Head->m_Previous = NewNode;
  }
  NewNode->m_Next = m_Head;
  m_Head = NewNode;

  if(m_Tail == NULL)
  {
    m_Tail = NewNode;
  }

}
template<class T>
void DoubleLinkedList<T>::AddBack(T Value)
{
  DoubleListNode<T> *NewNode = new DoubleListNode<T>();
  assert(NewNode);
  NewNode->m_Value = Value;
  
  if(m_Head == NULL)
  {
    m_Head = NewNode;
  }
  
  if(m_Tail != NULL)
  {
    assert(m_Tail->m_Next == NULL);
    m_Tail->m_Next = NewNode;
    NewNode->m_Previous = m_Tail;
  }
  m_Tail = NewNode;
}

template<class T>
void DoubleLinkedList<T>::Remove(DoubleListNode<T> *Node)
{
  assert(Node != NULL);

  DoubleListNode<T> *Previous = Node->m_Previous;
  DoubleListNode<T> *Next = Node->m_Next;

  if(Previous != NULL)
  {
    Previous->m_Next = Next;
  }

  if(Next != NULL)
  {
    Next->m_Previous = Previous;
  }

  if(m_Head == Node)
  {
    m_Head = Next;
    assert(Previous == NULL);
  }
  
  if(m_Tail == Node)
  {
    m_Tail = Previous;
    assert(Next == NULL);
  }
}

template<class T>
bool DoubleLinkedList<T>::Contains(T Value)
{
  bool Result = false;
  DoubleListNode<T> *CurrentNode = m_Head;
  while(CurrentNode != NULL)
  {
    if(CurrentNode->m_Value == Value)
    {
      return true;
    }
    CurrentNode = CurrentNode->m_Next;
  }
  return Result;
}

template<class T>
void DoubleLinkedList<T>::Clear()
{
  DoubleListNode<T> *Current = m_Head;
  while(Current != NULL)
  {
    DoubleListNode<T> *NextNode = Current->m_Next;
    delete Current;
    Current = NextNode;
  }
  m_Head = NULL;
  m_Tail = NULL;
}

template<class T>
DoubleListNode<T> *DoubleLinkedList<T>::GetHead()
{
  return m_Head;
}

template<class T>
DoubleListNode<T> *DoubleLinkedList<T>::GetTail()
{
  return m_Tail;
}

#endif
