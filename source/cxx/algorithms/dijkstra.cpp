#include "dijkstra.h"
#include "../containers/trees/minheap.cpp"
#include "../containers/map.h"

DijkstraHelperNode::DijkstraHelperNode()
{
	m_Node = NULL;
	m_Previous = NULL;
	m_Cost = UINT_MAX;
}

inline bool DijkstraHelperNode::operator <(DijkstraHelperNode *Other)
{
	return m_Cost < Other->m_Cost;
}
	
inline bool DijkstraHelperNode::operator >(DijkstraHelperNode *Other)
{
	return m_Cost > Other->m_Cost;
}

DoubleLinkedList<GraphNode *> Dijkstra(GraphNode *Start, GraphNode * End)
{
	Map<GraphNode *, DijkstraHelperNode *> NodeHelperMap;
	DoubleLinkedList<DijkstraHelperNode *> Visited;
	MinHeap<DijkstraHelperNode *> OpenHeap;
	DijkstraHelperNode *NewHelper = new DijkstraHelperNode();
	NewHelper->m_Node = Start;
	NewHelper->m_Cost = 0;
	NodeHelperMap.Insert(Start, NewHelper);
	OpenHeap.Insert(NewHelper);
	while(!OpenHeap.IsEmpty())
	{
		DijkstraHelperNode *CurrentHelperNode = OpenHeap.PopTop();
		assert(CurrentHelperNode != NULL);
		GraphNode *CurrentGraphNode = CurrentHelperNode->m_Node;
		assert(CurrentGraphNode != NULL);
		DoubleLinkedList<GraphEdge *> *CurrendEdges = CurrentGraphNode->GetEdges();
		DoubleListNode<GraphEdge *> *CurrentEdge = CurrentEdges.GetHead();
		while(CurrentEdge != NULL)
		{
			GraphNode *OtherNode = CurrentEdge->m_End;
			if(OtherNode == CurrentGraphNode)
			{
				OtherNode = CurrentEdge->m_Start;
			}
			assert(OtherNode != CurrentGraphNode);
			DijkstraHelperNode *NodeHelper = NodeHelperMap.GetValue(OtherNode);
			if(NodeHelper == NULL)
			{
 				NodeHelper = new DijkstraHelperNode();
				NodeHelper->m_Node = OtherNode;
				NodeHelperMap.Insert(OtherNode, NodeHelper);		
				OpenHeap.Insert(NodeHelper);
			}
			int CostToNode = CurrentHelperNode->m_Cost + CurrentEdge->m_Cost;
			if(CostToNode < NodeHelper->m_Cost)
			{		
				NodeHelper->m_Cost = CostToNode;
				NodeHelper->m_Previous = CurrentGraphNode;
				OpenHeap.Update(NodeHelper);
			}
			if(OtherNode == End)
			{
				break;
			}
		}
	}

	DoubleLinkedList<GraphNode *> Path;
	DijkstraHelperNode *EndHelper = NodeHelperMap.GetValue(End);
	if(EndHelper != NULL)
	{
		DijkstraHelperNode *CurrentHelper = EndHelper;
		while(CurrentHelper != NULL)
		{
			Path.AddFront(CurrentHelper->m_Node);
			CurrentHelper = CurrentHelper->m_Previous;
		}
	}
}
