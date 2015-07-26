/*
Map Tree Node
A balanced binary search tree node that is a normal Red Black Tree
node with the addition of a Map Value.
*/

#ifndef MAPTREENODE
#define MAPTREENODE

#import "redblack_tree_node.h"

template<class Key, class Value>
class MapTreeNode: public RedBlackTreeNode<Key>
{
public:
	MapTreeNode();
	~MapTreeNode();

	Value m_MapValue;
};

template<class Key, class Value>
MapTreeNode<Key, Value>::MapTreeNode():RedBlackTreeNode<Key>()
{
	m_MapValue = Value();
}

#endif