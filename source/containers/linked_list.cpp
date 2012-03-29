#include "linked_list.h"

template<class T>
ListNode<T> *ReverseList(ListNode<T> *Head)
{
  if(Head->m_Next == 0)
    return Head;

  ListNode<T> *NewHead = ReverseList(Head->m_Next);
  
  assert(Head->m_Next->m_Next == 0);
  Head->m_Next->m_Next = Head;
  Head->m_Next = 0;

  return NewHead;
}

