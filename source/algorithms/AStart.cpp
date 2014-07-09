#import "AStart.h"

EvaluationNode::EvaluationNode()
{
	m_Node = NULL;
	m_Previous = NULL;
	m_Cost = 0;
}

bool EvaluationNode::operator <(Node *Right)
{
	return m_Cost < Right->m_Cost;
}

bool EvaluationNode::operator >(Node *Right)
{
	return m_Cost > Right->m_Cost;
}

EvaluationNode * GetNodeInOpenSet(MinHeap<EvaluationNode *> *OpenSet, Node *Node)
{
	InorderTraversal<int> Iterator(&OpenSet);
	while(Iterator.HasMore())
	{
		EvaluationNode *Current = (EvaluationNode *)TreeIterator.NextNode();
		assert(Current != NULL);
		if(Current->m_Node == Node)
		{
			return Current;
		}
	}
	return NULL;
}

DoubleLinkedList<Nodes *> ReconstructPath(EvaluationNode *Goal, Node *Start)
{
	DoubleLinkedList<Nodes *> Path();
	EvaluationNode *CurrentNode = Goal;
	while(CurrentNode->m_Previous != NULL)
	{
		Path.PushFront(CurrentNode->m_Node);
		CurrentNode = CurrentNode->m_Previous;
	}
	assert(CurrentNode->m_Node == Start);
	Path.PushFront(CurrentNode->m_Node);
	return Path;
}

DoubleLinkedList<Edges *> AStart(Node *Start, Node *End)
{
	MinHeap<int> OpenSet; // Nodes to be checked
	DoubleLinkedList<Node *> ClosedSet; // Nodes already checked

	EvaluationNode *EvaluateNode = new EvaluationNode();
	EvaluateNode->m_Node = Start;
	EvaluateNode->m_Previous = NULL;
	EvaluateNode->m_Value = 0;
	OpenSet.PushBack(EvaluationNode)
	while(!OpenSet.IsEmpty())
	{
		EvaluationNode *CurrentNode = OpenSet.PopMin();
		if(CurrentNode->m_Node == End)
		{
			// Found the goal
			break return ReconstructPath(CurrentNode, Start);
		}
		if(!ClosedSet.Contains(CurrentNode->m_Node))
		{
			ClosedSet.PushBack(CurrentNode->m_Node);
		}
		DoubleLinkedListNode<Edge *> *ListNode = CurrentNode->m_Node->m_Edges.GetHead();
		while(ListNode != NULL)
		{
			Edge *Edge = ListNode->m_Value;
			assert(Edge != NULL);
			Node *Neighbour = Edge->m_Node2;			
			assert(Neighbour != NULL);
			if(ClosedSet.Contains(Neighbour))
			{
				int Cost = CurrentNode->m_Cost + Edge->m_Cost;
				EvaluationNode *EvalNode = GetNodeInOpenSet(OpenSet, Neighbour);
				if(EvalNode == NULL)
				{
					EvalNode = new EvaluationNode();
					EvalNode->m_Node = Neighbour;
					EvalNode->m_Previous = CurrentNode;
					EvalNode->m_Cost = Cost;
					OpenSet.Insert(EvalNode);
				}
				else if(EvalNode->m_Cost > Cost)
				{
					EvalNode->m_Previous = CurrentNode;
					EvalNode->m_Cost = Cost;
					OpenSet.Update(EvalNode);				
				}
			}
			ListNode = ListNode->m_Next;
		}
	}
}