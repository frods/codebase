#ifndef GRAPHEDGE
#define GRAPHEDGE

extern class GraphNode;

class GraphEdge
{
public:
	GraphEdge();
	~GraphEdge();

	bool operator <(GraphNode *Other);
	bool operator >(GraphNode *Other);

	GraphNode *m_Start;
	GraphNode *m_End;
	unsigned int m_Cost;		
};

GraphEdge::GraphEdge()
{
	m_Start = NULL;
	m_End = NULL;
	m_Cost = 0;
}

bool GraphNode::operator <(GraphNode *Other)
{
	return m_Cost < Other->m_Cost;
}

bool GraphNode::operator >(GraphNode *Other)
{
	return m_Cost > Other->m_Cost;
}

#endif