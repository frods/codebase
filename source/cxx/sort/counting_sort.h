 /*

Counting Sort

*/

#ifndef COUNTING_SORT
#define COUNTING_SORT

#include <stdio.h>

template<typename T>
inline void CountingSort(T *Array, int Length)
{
	int *Historgram = new int[Length];

	for(int i = 0; i < Length; i++)
	{
		Histogram[i] = 0;
	}

	for(int i = 0; i < Length; i++)
	{
		Histogram[Array[i]] += 1;
	}

	for(int i = 0; i < Length; i++)
	{
		Histogram[Array[i]] += 1;
	}
	

	delete Historgram;
};


#endif
