#include "bubble_sort_test.h"
#include "merge_sort.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

int ReverseTest(int i)
{
  return 10 - i;
}

int TestResult10(int i)
{
  return i + 1;
}

int BinaryTestResult10(int i)
{
  int Value = 0;
  if(i >=5)
    Value = 1;
  return Value;
}

int InterleaveTest(int i)
{
  int val = i;
  if(i%2 == 0)
    val = 10 - i;
  return val;
}

int BinaryInterleaveTest(int i)
{
  return i%2;
}

void SortTest(
              char const*TestTitle, int TestLength, 
              int (TestFunc)(int Index), int (ResultFunc)(int Index), 
              void (SortFunc)(int *, int))
{
  int *TestArray = new int[TestLength];
  int *ResultArray = new int[TestLength];
  printf("%s\n", TestTitle);
  
  printf("[");
  for(int i = 0; i < 10; i++)
  {
    TestArray[i] = TestFunc(i);
    printf("%i ", TestArray[i]);
  }
  printf("%c]\n",0x8);
  
  printf("Target Result\n");
  
  printf("[");
  for(int i = 0; i < 10; i++)
  {
    ResultArray[i] = ResultFunc(i);
    printf("%i ", ResultArray[i]);
  }
  printf("%c]\n",0x8);

  printf("Begin Sorting\n");
  
  SortFunc(TestArray, TestLength);
  
  printf("Result\n");
  
  printf("[");
  bool Success = true;
  for(int i = 0; i < 10; i++)
  {
    printf("%i ", TestArray[i]);
    if(TestArray[i] != ResultArray[i])
      Success = false;
    
  }
  printf("%c]\n",0x8);
  
  delete[] TestArray;
  delete[] ResultArray;
  
  if(Success)
    printf("Test Succeeded!\n");
  else
    printf("Test Failed\n");
  
  printf("==========================================\n");
}
  
int main(int argc, const char *argv[])
{
  SortTest("Bubble Sort Reverse Test", 10, &ReverseTest, &TestResult10, &BubbleSort<int>);
  
  SortTest("Bubble Sort Interleaved Test", 10, &InterleaveTest, &TestResult10, &BubbleSort<int>);
  
  SortTest("Bubble Sort Two values Interleaved Test", 10, &BinaryInterleaveTest, &BinaryTestResult10, &BubbleSort<int>);
  
  SortTest("Merge Sort Reverse Test", 10, &ReverseTest, &TestResult10, &MergeSort<int>);
  
  SortTest("Merge Sort Interleaved Test", 10, &InterleaveTest, &TestResult10, &MergeSort<int>);
  
  SortTest("Merge Sort Two values Interleaved Test", 10, &BinaryInterleaveTest, &BinaryTestResult10, MergeSort<int>);
  
}
