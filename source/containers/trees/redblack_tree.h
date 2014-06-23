/*
Red Black Tree
A balanced binary search tree

The tree satisfies the following constraints
1- A node is either red or black.
2- The root is black. (This rule is sometimes omitted. Since the root can always be changed from red to black, but not necessarily vice-versa, this rule has little effect on analysis.)
3- All leaves (NIL) are black. (All leaves are same color as the root.)
4- Every red node must have two black child nodes.
5- Every path from a given node to any of its descendant leaves contains the same number of black nodes.
*/

#ifndef REDBLACKTREE
#define REDBLACKTREE

#import "redblack_tree_node.h"

template<class T>
class RedBlackTree: public BinaryTree<T>
{
public:
	RedBlackTree();
	~RedBlackTree();

	virtual void Insert(T Value);

	void EnforceConstraints(RedBlackTreeNode<T> *Node);

	RedBlackTreeNode<T> *GetHead();

	void RotateLeft(RedBlackTreeNode<T> *Node);
	void RotateRight(RedBlackTreeNode<T> *Node);

	void PrintTree();
};

template<class T>
RedBlackTree<T>::RedBlackTree():BinaryTree<T>()
{
}

template<class T>
RedBlackTree<T>::~RedBlackTree()
{

}

template<class T>
void RedBlackTree<T>::Insert(T Value)
{
  RedBlackTreeNode<T> *NewNode = new RedBlackTreeNode<T>();
  assert(NewNode);
  NewNode->m_Value = Value;

  if(!BinaryTree<T>::m_Head)
  {
    BinaryTree<T>::m_Head = (BinaryTreeNode<T> *)NewNode;
    assert(BinaryTree<T>::m_Count == 0);
  }
  else
  {
    BinaryTree<T>::InsertAt(BinaryTree<T>::m_Head, (BinaryTreeNode<T> *)NewNode);
  }
  EnforceConstraints(NewNode);
  BinaryTree<T>::m_Count++;	
}

template<class T>
void RedBlackTree<T>::EnforceConstraints(RedBlackTreeNode<T> *Node)
{
	assert(Node != NULL);
	printf("Enforce constraints of %i\n", Node->m_Value);
	// Enforce the constraints of the RedBlack tree
	// Case 1
	// Simplest case the Node is the head
	assert(Node->m_Colour == RED);
	if(Node == BinaryTree<T>::m_Head)
	{
		Node->m_Colour = BLACK;
		printf("At root, set it to black\n");
		return;
	}

	// Case 2
	// Parent is black so constriant 4 is satisfied
	assert(Node->m_Parent != NULL);
	if(((RedBlackTreeNode<T> *)Node->m_Parent)->m_Colour == BLACK)
	{
		printf("Red child of a Black parent, do nothing\n");
		return;
	}

	// Case 3
	// Both parent and Uncle are red, repaint them to black and change
	// grandparent to red. This maintains property 5
	assert(((RedBlackTreeNode<T> *)Node->m_Parent)->m_Colour == RED);
	RedBlackTreeNode<T> *Uncle = (RedBlackTreeNode<T> *)Node->Uncle();
	if(Uncle != NULL && Uncle->m_Colour == RED)
	{
		printf("Parent and uncle are red repaint black and grandparent red and move up\n");
		((RedBlackTreeNode<T> *)Node->m_Parent)->m_Colour = BLACK;
		Uncle->m_Colour = BLACK;
		RedBlackTreeNode<T> *Grandparent = (RedBlackTreeNode<T> *)Node->Grandparent();
		assert(Grandparent != NULL && Grandparent->m_Colour == BLACK);
		Grandparent->m_Colour = RED;
		EnforceConstraints(Grandparent);
		return;
	}

	// Case 4
	// The uncle is Black or NULL (which is implicitly Black)
	assert(Uncle == NULL || Uncle->m_Colour == BLACK);
	RedBlackTreeNode<T> *Grandparent = (RedBlackTreeNode<T> *)Node->Grandparent();
	if(Grandparent != NULL)
	{
		if(Node == Node->m_Parent->m_Right && Node->m_Parent == Grandparent->m_Left)
		{
			printf("Rotate Left %i\n", Node->m_Parent->m_Value);
			RotateLeft((RedBlackTreeNode<T> *)Node->m_Parent);
			Node = (RedBlackTreeNode<T> *)Node->m_Left;
			printf("Node is now %i\n", Node->m_Value);
		}
		else if(Node == Node->m_Parent->m_Left && Node->m_Parent == Grandparent->m_Right)
		{
			printf("Rotate Right %i\n", Node->m_Parent->m_Value);
			RotateRight((RedBlackTreeNode<T> *)Node->m_Parent);
			Node = (RedBlackTreeNode<T> *)Node->m_Right;
			printf("Node is now %i\n", Node->m_Value);
		}

		// Case 5
		// Parent is red but Uncle is black
		Grandparent = (RedBlackTreeNode<T> *)Node->Grandparent();
		assert(Grandparent != NULL);
		Uncle = (RedBlackTreeNode<T> *)Node->Uncle();
		assert(((RedBlackTreeNode<T> *)Node->m_Parent)->m_Colour == RED && (Uncle == NULL || Uncle->m_Colour == BLACK));
		((RedBlackTreeNode<T> *)Node->m_Parent)->m_Colour = BLACK;
		assert(Grandparent->m_Colour == BLACK);
		Grandparent->m_Colour = RED;
		if(Node == Node->m_Parent->m_Left)
		{
			printf("Rotate Grandparent %i Right\n", Grandparent->m_Value);
			RotateRight(Grandparent);
		}
		else
		{
			printf("Rotate Grandparent %i Left\n", Grandparent->m_Value);
			RotateLeft(Grandparent);
		}
	}
	else
	{
		printf("No Grandparent\n");
	}
}

template<class T>
RedBlackTreeNode<T> *RedBlackTree<T>::GetHead()
{
	return (RedBlackTreeNode<T> *)BinaryTree<T>::GetHead();
}

template<class T>
void RedBlackTree<T>::RotateLeft(RedBlackTreeNode<T> *Node)
{
	RedBlackTreeNode<T> *NewHead = (RedBlackTreeNode<T> *)Node->RotateLeft();
	if(Node == BinaryTree<T>::m_Head)
	{
		BinaryTree<T>::m_Head = NewHead;
	}
}

template<class T>
void RedBlackTree<T>::RotateRight(RedBlackTreeNode<T> *Node)
{
	RedBlackTreeNode<T> *NewHead = (RedBlackTreeNode<T> *)Node->RotateRight();
	if(Node == BinaryTree<T>::m_Head)
	{
		BinaryTree<T>::m_Head = NewHead;
	}
}

template<class T>
void RedBlackTree<T>::PrintTree()
{
	DoubleLinkedList<RedBlackTreeNode<T> *> Printed;
	DoubleLinkedList<RedBlackTreeNode<T> *> ThisRow;
	ThisRow.AddBack((RedBlackTreeNode<T> *)BinaryTree<T>::m_Head);
	while(!ThisRow.IsEmpty())
	{
		DoubleLinkedList<RedBlackTreeNode<T> *> NextRow;
		printf("\n");
		while(!ThisRow.IsEmpty())
		{
			RedBlackTreeNode<T> *Current = ThisRow.PopFront();
			if(Current != NULL)
			{
				printf("%i%c ", Current->m_Value, Current->m_Colour);
				Printed.AddBack(Current);
				if(!Printed.Contains((RedBlackTreeNode<T> *)Current->m_Left))
				{
					NextRow.AddBack((RedBlackTreeNode<T> *)Current->m_Left);
				}
				if(!Printed.Contains((RedBlackTreeNode<T> *)Current->m_Right))
				{
					NextRow.AddBack((RedBlackTreeNode<T> *)Current->m_Right);
				}
			}
			else
			{
				printf("N ");				
			}
		}
		ThisRow = NextRow;
	}
	printf("\n");
}

#endif