/*
    Templated map binary tree
    Requirements:
        The tree is always balanced
        Every node is greater than all nodes below it

    
 */

#ifndef MAP
#define MAP

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "map_tree_node.h"
#include "redblack_tree.h"

//#define DEBUG

template<class Key, class Value> 
class Map:protected RedBlackTree<Key>
{
public:
    Map();
    virtual ~Map();
    
    void Insert(Key KeyVal, Value ValueVal);
    Value GetValue(Key KeyVal);

private:

};

////////////////////////////////////////////////////////////////////////////////
// Implementation
////////////////////////////////////////////////////////////////////////////////

template<class Key, class Value>
Map<Key, Value>::Map()
{
}

template<class Key, class Value>
Map<Key, Value>::~Map()
{
}

template<class Key, class Value>
void Map<Key, Value>::Insert(Key KeyVal, Value ValueVal)
{
  MapTreeNode<Key, Value> *NewNode = new MapTreeNode<Key, Value>();
  assert(NewNode);
  NewNode->m_Value = Value;
  Insert((BinaryTreeNode<Key> *)NewNode);
}

template<class Key, class Value>
Value Map<Key, Value>::GetValue(Key KeyVal)
{
    MapTreeNode<Key, Value> *Node = (MapTreeNode<Key, Value> *)GetNode(Key);
    if(Node != NULL)
    {
        return Node->MapValue;
    }
    return Value();
}


#endif