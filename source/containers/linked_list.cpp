#include "linked_list.h"

ListNode *ReverseList(ListNode *Head)
{
  if(Head->m_Next == 0)
    return Head;

  ListNode *NewHead = ReverseList(Head->m_Next);
  
  assert(Head->m_Next->m_Next == 0)
  Head->m_Next->m_Next = Head;
  Head->m_Next = 0;

  return NewHead;
}

