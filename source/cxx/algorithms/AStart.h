/*
A*
Find the shortest path between two nodes in a graph
based on a heuristic about cost of paths between nodes.

Takes and adjacency graph with costs for each 
*/

#ifndef ASTAR
#define ASTAR

#import "../containters/graphs/graph_edge.h"
#import "../containters/graphs/graph_node.h"
#import "../containers/trees/binary_tree_node.h"

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