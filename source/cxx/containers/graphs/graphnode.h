#ifndef GRAPHNODE
#define GRAPHNODE

#include "graph_edge.h"

class GraphNode
{
public:
	GraphNode();
	~GraphNode();

	DoubleLinkedList<GraphEdge *> *GetEdges();

	DoubleLinkedList<GraphEdge *> m_Edges;
};

GraphNode::GraphNode()
{

}

DoubleLinkedList<GraphEdge *> *GraphNode::GetEdges()
{
	return &m_Edges;
}


#endif