/*
Conceptually, a merge sort works as follows

    If the list is of length 0 or 1, then it is already sorted. Otherwise:
    Divide the unsorted list into two sublists of about half the size.
    Sort each sublist recursively by re-applying the merge sort.
    Merge the two sublists back into one sorted list.

Merge sort incorporates two main ideas to improve its runtime:

    A small list will take fewer steps to sort than a large list.
    Fewer steps are required to construct a sorted list from two sorted lists than from two unsorted lists.
    For example, you only have to traverse each list once if they're already sorted (see the merge function below for an example implementation).

Example: Use merge sort to sort a list of integers contained in an array:

Suppose we have an array A with n indices ranging from A0 to An − 1. We apply merge sort to A(A0..Ac − 1) and A(Ac..An − 1) where c is the integer part of n / 2.
When the two halves are returned they will have been sorted. They can now be merged together to form a sorted array.

Worst Case performance O(nlogn)
*/

#ifndef MERGESORT
#define MERGESORT

#include "../containers/lists/double_linked_list.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

template<typename T>
inline void MergeSortPart(T *Array, int Start, int End)
{
  int Length = End - Start;
  
  if(Length <= 1)
    return;
  
  int Division = (Length / 2) + Start;
  MergeSortPart<T>(Array, Start, Division);
  MergeSortPart<T>(Array, Division, End);
  
  // TODO replace with a Vector
  DoubleLinkedList<T> Sorted;

  int iPart1 = Start;
  int iPart2 = Division;
  while(iPart1 < Division && iPart2 < End)
  {
    if(Array[iPart1] < Array[iPart2])
    {
      Sorted.AddBack(Array[iPart1]);
      iPart1++;
    }
    else
    {
      Sorted.AddBack(Array[iPart2]);
      iPart2++;
    }
  }

  assert(iPart1 == Division || iPart2 == End);
  while(iPart1 < Division)
  {
      Sorted.AddBack(Array[iPart1]);
      iPart1++;    
  }
  while(iPart2 < End)
  {
      Sorted.AddBack(Array[iPart2]);
      iPart2++;    
  }
  for(int i = Start; i < End; i++)
  {
    assert(!Sorted.IsEmpty());
    Array[i] = Sorted.PopFront();
  }
  assert(Sorted.IsEmpty());

};

template<typename T>
inline void MergeSort(T *Array, int Length)
{  
  MergeSortPart<T>(Array, 0, Length);
};

#endif
