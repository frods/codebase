/*
A*
Find the shortest path between two nodes in a graph
based on a heuristic about cost of paths between nodes.

Takes and adjacency graph with costs for each 
*/

#ifndef ASTAR
#define ASTAR

#import "../containers/trees/binary_tree_node.h"

class Edge
{
public:
	Edge();
	~Edge();

	bool operator <(Node *Right);
	bool operator >(Node *Right);

	Node *m_Node1;
	Node *m_Node2;
	int m_Cost;
};

class Node
{
public:

	DoubleLinkedList<Edge *> m_Edges;
	int m_Num;
};

class EvaluationNode:public BinaryTreeNode<int>
{
public:
	bool operator <(Node *Right);
	bool operator >(Node *Right);
	
	Node *m_Node;
	EvaluationNode *m_Previous;
};


class Visited
{
	Node *m_Node;
	bool m_Visited;	
};

DoubleLinkedList<Node *> AStart(Node *Start, Node *End);

#endif