#include "bubble_sort.h"
#include "merge_sort.h"
#include "quick_sort.h"
#include "heap_sort.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

//#define VERBOSE

void ReverseTest(int *Array, int Length)
{
    // Return the inverse set of integers
    for(int i = 0; i < Length; i++)
    {
        Array[i] = Length - i;
    }
}

void InterleaveTest(int *Array, int Length)
{
    for(int i = 0; i < Length; i++)
    {
        int val = i;
        if(i%2 == 0)
            val = Length - i;
        Array[i] = val;
    }
}

void RandomTest(int *Array, int Length)
{
    for(int i = 0; i < Length; i++)
    {
        Array[i] = i + 1;
    }
    srand(time(NULL));
    for(int i = 0; i < Length; i++)
    {
        int x = rand() % Length;
        int temp = Array[x];
        Array[x] = Array[i];
        Array[i] = temp;
    }
}

int TestResult(int num, int i)
{
    return i + 1;
}

void BinaryInterleaveTest(int *Array, int Length)
{
    for(int i = 0; i < Length; i++)
    {
        Array[i] = i%2;
    }
}

int BinaryTestResult(int num, int i)
{
    int Value = 0;
    if(i >=num/2)
        Value = 1;
    return Value;
}

int Succeded = 0;
int Failed = 0;
void SortTest(char const*TestTitle, int TestLength, 
    void (TestFunc)(int *, int), int (ResultFunc)(int, int), 
    void (SortFunc)(int *, int))
{
    int *TestArray = new int[TestLength];
    int *ResultArray = new int[TestLength];
    printf("==========================================\n");
    printf("%s:\t%i elements\t\n", TestTitle, TestLength);

    TestFunc(TestArray, TestLength);
#ifdef VERBOSE
    printf("[");
    for(int i = 0; i < TestLength; i++)
    {
      printf("%i ", TestArray[i]);
    }
    printf("%c]\n",0x8);
    
    printf("Target Result\n");
    
    printf("[");
#endif
    for(int i = 0; i < TestLength; i++)
    {
        ResultArray[i] = ResultFunc(TestLength, i);
#ifdef VERBOSE
        printf("%i ", ResultArray[i]);
#endif
    }
#ifdef VERBOSE
    printf("%c]\n",0x8);
#endif
    clock_t start = clock();
    
    SortFunc(TestArray, TestLength);
    
    printf("Time: %.4f seconds\t\n", (float)(clock() - start)/CLOCKS_PER_SEC);
#ifdef VERBOSE
    printf("Result\n");
    
    printf("[");
#endif
    bool Success = true;
    for(int i = 0; i < TestLength; i++)
    {
#ifdef VERBOSE        
        printf("%i ", TestArray[i]);
#endif
        if(TestArray[i] != ResultArray[i])
            Success = false;
        
    }
#ifdef VERBOSE        
    printf("%c]\n",0x8);
#endif

    delete[] TestArray;
    delete[] ResultArray;
    
    if(Success)
    {
        printf("Test Succeeded!\n");
        Succeded++;
    }
    else
    {
        printf("Test Failed\n");
        Failed++;
    }
    
    printf("==========================================\n");
}

void TestSuite(char const*AlgorithmTitle, void (SortFunc)(int *, int))
{
    std::string AlgorithmString = std::string(AlgorithmTitle);
    SortTest((AlgorithmString + " Reverse Test").c_str(), 10, &ReverseTest, &TestResult, SortFunc);
    
    SortTest((AlgorithmString + " Interleaved Test").c_str(), 10, &InterleaveTest, &TestResult, SortFunc);
    
    SortTest((AlgorithmString + " Two values Interleaved Test").c_str(), 10, &BinaryInterleaveTest, &BinaryTestResult, SortFunc);
    
    SortTest((AlgorithmString + " Random Test").c_str(), 50, &RandomTest, &TestResult, SortFunc);
}
    
int main(int argc, const char *argv[])
{
    TestSuite("Bubble Sort", &BubbleSort<int>);
        
    TestSuite("Merge Sort", &MergeSort<int>);
    
    TestSuite("Quick Sort", &QuickSort<int>);
    
    TestSuite("Heap Sort", &HeapSort<int>);

    printf("%i/%i Failed\n", Failed, Failed + Succeded);
}
