/*
Quicksort is a divide and conquer algorithm which relies on a partition operation:
 to partition an array an element called a pivot is selected.
 All elements smaller than the pivot are moved before it and all greater elements are moved after it.
 This can be done efficiently in linear time and in-place.
 The lesser and greater sublists are then recursively sorted.
 Efficient implementations of quicksort (with in-place partitioning) are typically unstable sorts and somewhat complex,
 but are among the fastest sorting algorithms in practice.
 Together with its modest O(log n) space usage, quicksort is one of the most popular sorting algorithms and is available in many standard programming libraries.
 The most complex issue in quicksort is choosing a good pivot element;
 consistently poor choices of pivots can result in drastically slower O(n²) performance, if at each step the median is chosen as the pivot then the algorithm works in O(n log n).
 Finding the median however, is an O(n) operation on unsorted lists and therefore exacts its own penalty with sorting.

Worstcase O(n^2)
Average case O(n log n)

In place implimentation doesn't use any extra space.

Uses a naive pivot selection of always choosing the last element of a segment.

*/

#ifndef QUICKSORT
#define QUICKSORT

#include "../containers/lists/linked_list.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

template<typename T>
inline void Swap(T *Array, int Index1, int Index2)
{
    T temp = Array[Index1];
    Array[Index1] = Array[Index2];
    Array[Index2] = temp;   
};

template<typename T>
inline void QuickSortPart(T *Array, int Start, int End)
{
    int Length = End - Start;
  
    if(Length <= 1)
        return;
  
    int PivotLocation = End - 1;
    int PivotVal = Array[PivotLocation];

    //Swap(Array, PivotLocation, End - 1);
    //PivotLocation = End - 1;

    int LessThanIndex = Start;
    for(int i = Start; i < End - 1; i++)
    {
        if(Array[i] <= PivotVal)
        {
            Swap(Array, i, LessThanIndex);
            LessThanIndex++;
        }
    }

    Swap(Array, PivotLocation, LessThanIndex);


    QuickSortPart(Array, Start, LessThanIndex);
    QuickSortPart(Array, LessThanIndex + 1, End);
};

template<typename T>
inline void QuickSort(T *Array, int Length)
{  
    QuickSortPart(Array, 0, Length);
};

#endif
