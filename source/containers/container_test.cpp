#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "lists/linked_list.h"
#include "lists/double_linked_list.h"
#include "trees/binary_tree.h"
#include "trees/iterator_inorder.h"
#include "trees/iterator_breadthfirst.h"
#include "trees/maxheap.h"
#include "arrays/maxheaparray.h"
#include "arrays/vector.h"
#include "trees/redblack_tree.h"

void LinkedListTest()
{
	printf("Linked List\n");
	LinkedList<int> List;
	for(int i = 0; i < 10; i++)
	{
		List.AddFront(i);
	}
	ListNode<int> *CurrentNode = List.GetHead();
	while(CurrentNode != NULL)
	{
		printf("%i ", CurrentNode->m_Value);
		CurrentNode = CurrentNode->Next();
	}
	printf("\n");

	CurrentNode = List.GetHead();
	CurrentNode = CurrentNode->Reverse();
	while(CurrentNode != NULL)
	{
		printf("%i ", CurrentNode->m_Value);
		CurrentNode = CurrentNode->Next();
	}
	printf("\n");	
}

void DoubleLinkedListTest()
{
	printf("\nDouble Linked List\n");
	DoubleLinkedList<int> DoubleList;
	for(int x = 0; x < 10; x++)
	{
		DoubleList.AddBack(x);
	}
	DoubleListNode<int> *CurrentDoubleNode = DoubleList.GetHead();
	while(CurrentDoubleNode != NULL)
	{
		printf("%i ", CurrentDoubleNode->m_Value);
		CurrentDoubleNode = CurrentDoubleNode->Next();
	}
	printf("\n");	
}

void BinaryTreeTest()
{
	printf("\nBinary Tree\n");
	BinaryTree<int> Tree;
	srand(time(NULL));
	for(int x = 0; x < 10; x++)
	{
		int val = rand() % 50;
		printf("%i ", val);
		Tree.Insert(val);
	}
	printf("\n");
	InorderTraversal<int> TreeIterator(&Tree);
	printf("start iterating inorder\n");
	while(TreeIterator.HasMore())
	{
	  printf("%i ", TreeIterator.Next());
	}
	printf("\n");
	BreadthFristTraversal<int> TreeBreadthFirstIterator(&Tree);
	printf("start iterating breadth first\n");
	while(TreeBreadthFirstIterator.HasMore())
	{
	  printf("%i ", TreeBreadthFirstIterator.Next());
	}
	printf("\n");
}

void MaxHeapTest()
{
	printf("\nMax Heap\n");
	MaxHeap<int> Heap;
	srand(time(NULL));
	for(int x = 0; x < 10; x++)
	{
		int val = rand() % 50;
		printf("%i ", val);
		Heap.Insert(val);
	}
	printf("\n");

	InorderTraversal<int> HeapIterator(&Heap);
	printf("start iterating inorder\n");
	while(HeapIterator.HasMore())
	{
	  printf("%i ", HeapIterator.Next());
	}
	printf("\n");

	printf("Remove Head from Heap %i\n", Heap.GetHead()->m_Value);
	Heap.Remove(Heap.GetHead());
	HeapIterator.Reset();
	printf("start iterating inorder\n");
	while(HeapIterator.HasMore())
	{
	  printf("%i ", HeapIterator.Next());
	}
	printf("\n");
	printf("Remove Head from Heap %i\n", Heap.GetHead()->m_Value);
	Heap.Remove(Heap.GetHead());
	HeapIterator.Reset();
	printf("start iterating inorder\n");
	while(HeapIterator.HasMore())
	{
	  printf("%i ", HeapIterator.Next());
	}
	printf("\n");
	printf("Remove Head from Heap %i\n", Heap.GetHead()->m_Value);
	Heap.Remove(Heap.GetHead());
	HeapIterator.Reset();
	printf("start iterating inorder\n");
	while(HeapIterator.HasMore())
	{
	  printf("%i ", HeapIterator.Next());
	}
	printf("\n");
	printf("Remove Head Left from Heap %i\n", Heap.GetHead()->m_Left->m_Value);
	Heap.Remove(Heap.GetHead()->m_Left);
	HeapIterator.Reset();
	printf("start iterating inorder\n");
	while(HeapIterator.HasMore())
	{
	  printf("%i ", HeapIterator.Next());
	}
	printf("\n");

}

void MaxHeapArrayTest()
{
	int TestSize = 15;
	printf("\nHeapify\n");
	int Array[TestSize];
	srand(time(NULL));
	for(int x = 0; x < TestSize; x++)
	{
		int val = rand() % 50;
		printf("%i ", val);
		Array[x] = (val);
	}

	MaxHeapArray<int>::Heapify(Array, TestSize);
	printf("\nHeap ");
	for(int x = 0; x < TestSize; x++)
	{
		printf("%i ", Array[x]);
	}
	printf("\n");

	printf("\nMaxHeapArray\n");
	MaxHeapArray<int> HeapArray;
	srand(time(NULL));
	for(int x = 0; x < TestSize; x++)
	{
		int val = rand() % 50;
		printf("%i ", val);
		HeapArray.Insert(val);
	}
	printf("\n");
	for(int x = 0; x < TestSize; x++)
	{
		printf("%i ", HeapArray[x]);
	}
	printf("\n");
}

void VectorTest()
{
	int TestSize = 15;
	printf("\nVector\n");
	Vector<int> TestVector;
	srand(time(NULL));
	for(int x = 0; x < TestSize; x++)
	{
		int val = rand() % 50;
		printf("%i ", val);
		TestVector.PushBack(val);
	}
	printf("\n");
	for(int x = 0; x < TestSize; x++)
	{
		printf("%i ", TestVector[x]);
	}
	printf("\n");	
}

void RedBlackTreeTest()
{
	printf("\nRed Black Tree\n");
	RedBlackTree<int> Tree;
	printf("Start building tree\n");
	srand(time(NULL));
	BreadthFristTraversal<int> TreeBreadthFirstIterator(&Tree);
	for(int x = 0; x < 10; x++)
	{
		int val = rand() % 50;
		printf("Inserting %i \n", val);
		Tree.Insert(val);
		Tree.PrintTree();
		printf("\n");	
	}
	printf("\n");
	InorderTraversal<int> TreeIterator(&Tree);
	printf("start iterating inorder\n");
	while(TreeIterator.HasMore())
	{
	  printf("%i ", TreeIterator.Next());
	}
	printf("\n");	
	printf("start iterating breadth first\n");
	TreeBreadthFirstIterator.Reset();
	// while(TreeBreadthFirstIterator.HasMore())
	// {
	//   printf("%i ", TreeBreadthFirstIterator.Next());
	// }
	printf("%i ", TreeBreadthFirstIterator.Next());
	printf("%i ", TreeBreadthFirstIterator.Next());
	printf("%i ", TreeBreadthFirstIterator.Next());
	printf("%i ", TreeBreadthFirstIterator.Next());
	printf("%i ", TreeBreadthFirstIterator.Next());
	printf("%i ", TreeBreadthFirstIterator.Next());
	printf("%i ", TreeBreadthFirstIterator.Next());
	printf("%i ", TreeBreadthFirstIterator.Next());
	printf("%i ", TreeBreadthFirstIterator.Next());
	printf("%i ", TreeBreadthFirstIterator.Next());
	printf("\n");	
}

int main(int argc, const char *argv[])
{
	//LinkedListTest();

	//DoubleLinkedListTest();

	//BinaryTreeTest();

	//MaxHeapTest();

	//MaxHeapArrayTest();

	//VectorTest();

	RedBlackTreeTest();
}