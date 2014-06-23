/*
    A heap which operates on arrays

*/

#ifndef MAXHEAPARRAY
#define MAXHEAPARRAY

#include "vector.h"

template<class T> 
class MaxHeapArray
{
public:
    MaxHeapArray();
    ~MaxHeapArray();

    void Insert(T Value);
    void Remove(int Index);

    inline T GetAt(int Index);
    inline T operator[](int Index);

    static void Heapify(T Array[], int Count);
    static void ShiftDown(T Array[], int Start, int End);

private:
    void BubbleUp(int Start);

    Vector<T> m_Data;
};

// Implementaiton

template<class T>
MaxHeapArray<T>::MaxHeapArray()
{

}

template<class T>
MaxHeapArray<T>::~MaxHeapArray()
{
}

template<class T>
void MaxHeapArray<T>::Insert(T Value)
{
    m_Data.PushBack(Value);
    BubbleUp(m_Data.Size() - 1);
}

template<class T>
void MaxHeapArray<T>::Remove(int Index)
{

}

template<class T>
void MaxHeapArray<T>::Heapify(T Array[], int Count)
{
    // Start with last parent
    int Start = (Count - 2)/2;
    while(Start >= 0)
    {
        ShiftDown(Array, Start, Count - 1);
        Start--;
    }
}

template<class T>
inline T MaxHeapArray<T>::GetAt(int Index)
{
    return m_Data[Index];
}

template<class T>
inline T MaxHeapArray<T>::operator[](int Index)
{
    return m_Data[Index];
}

template<class T>
void MaxHeapArray<T>::ShiftDown(T Array[], int Start, int End)
{
    int Root = Start;
    while(Root * 2 + 1 <= End)
    {
        int LeftChild = (Root << 1) + 1;
        int RightChild = LeftChild + 1;
        int Swap = Root;

        if(Array[Swap] < Array[LeftChild])
        {
            Swap = LeftChild;
        }
        if(RightChild <= End && Array[Swap] < Array[RightChild])
        {
            Swap = RightChild;
        }
        if(Swap != Root)
        {
            T Temp = Array[Swap];
            Array[Swap] = Array[Root];
            Array[Root] = Temp;
            Root = Swap;
        }
        else
        {
            return;
        }
    }
}

template<class T>
void MaxHeapArray<T>::BubbleUp(int Start)
{
    //Ensure the node is in the right place in the tree
    while(Start > 0)
    {
        int Parent = (Start - 1) >> 1;
        if(m_Data[Parent] < m_Data[Start])
        {
            m_Data.Swap(Parent, Start);
            Start = Parent;
        }
        else
        {
            return;
        }
    }
}

#endif