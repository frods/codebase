 /*

Heapsort is a comparison-based sorting algorithm.
Heapsort is part of the selection sort family; it improves on the basic selection sort by using a logarithmic-time priority queue rather than a linear-time search.
Although somewhat slower in practice on most machines than a well-implemented quicksort, it has the advantage of a more favorable worst-case O(n log n) runtime.
Heapsort is an in-place algorithm, but it is not a stable sort. It was invented by J. W. J. Williams in 1964.[2]


*/

#ifndef HEAP_SORT
#define HEAP_SORT

#include <stdio.h>
#include "../containers/arrays/maxheaparray.h"

template<typename T>
inline void HeapSort(T *Array, int Length)
{
	MaxHeapArray<T>::Heapify(Array, Length);

	int End = Length - 1;
	while(End > 0)
	{
		T Temp = Array[End];
		Array[End] = Array[0];
		Array[0] = Temp;
		End--;
		MaxHeapArray<T>::ShiftDown(Array,0, End);
	}
};


#endif
