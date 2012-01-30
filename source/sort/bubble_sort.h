/*

Bubble sort is a simple sorting algorithm. The algorithm starts at the beginning of the data set. It compares the first two elements, and if the first is greater than the second, it swaps them. It continues doing this for each pair of adjacent elements to the end of the data set. It then starts again with the first two elements, repeating until no swaps have occurred on the last pass. This algorithm's average and worst case performance is O(n2), so it is rarely used to sort large, unordered, data sets. Bubble sort can be used to sort a small number of items (where its inefficiency is not a high penalty). Bubble sort may also be efficiently used on a list that is already sorted except for a very small number of elements. For example, if only one element is not in order, bubble sort will take only 2n time. If two elements are not in order, bubble sort will take only at most 3n time.

Bubble sort average case and worst case are both O(n²).

*/

#ifndef BUBBLE_SORT
#define BUBBLE_SORT

#include <stdio.h>

template<typename T>
inline void BubbleSort(T *Array, int Length)
{
  bool Swapped = true;
  while(Swapped)
  {
    Swapped = false;
    int i = 0;
    for(i = 0; i < Length - 1; i++)
    {
      if(Array[i] > Array[i + 1])
      {
        Swapped = true;
        T temp = Array[i + 1];
        Array[i + 1] = Array[i];
        Array[i] = temp;
      }
    }
    printf("[");
    for(int i = 0; i < Length; i++)
      printf("%i ", Array[i]);
    printf("%c]\n",0x8);
  }
};


#endif
