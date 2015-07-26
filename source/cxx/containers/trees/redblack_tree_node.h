/*
Red Black Tree Node
A balanced binary search tree node that is a normal Binary Tree
node with the addition of a colour variable.
*/

#ifndef REDBLACKTREENODE
#define REDBLACKTREENODE

#import "binary_tree_node.h"

#define RED false
#define BLACK true
template<class T>
class RedBlackTreeNode: public BinaryTreeNode<T>
{
public:
	RedBlackTreeNode();
	~RedBlackTreeNode();

	bool m_Colour;
};

template<class T>
RedBlackTreeNode<T>::RedBlackTreeNode():BinaryTreeNode<T>()
{
	m_Colour = RED;
}

#endif