/*
Implementation of Dijkstra algorithm

Uses a min heap as inspired by Freedman & Tarjan

A graph search algorithm that finds the shortest path from one node to every other node in the graph
*/

#ifndef DIJKSTRA
#define DIJKSTRA

#include "../containers/graphs/graph_node.h"

class DijkstraHelperNode
{
public:
	DijkstraHelperNode();
	~DijkstraHelperNode();

	inline bool operator <(DijkstraHelperNode *Other);
	inline bool operator >(DijkstraHelperNode *Other);
	GraphNode *m_Node;
	GraphNode m_Previous;
	unsigned int m_Cost;		
};

DoubleLinkedList<GraphNode *> Dijkstra(GraphNode *Start, GraphNode * End);

#endif