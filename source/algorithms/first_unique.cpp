/*
Find first unique character in the input stream
*/

#include <stdlib.h>
#include <stdio.h>
#include <sstream>

#import "../containers/lists/double_linked_list.h"

char FirstUnique(std::istream *Input)
{
	DoubleLinkedList<char> UniqueChars;

	DoubleListNode<char> *InList[0xff];
	bool Repeated[0xff];

	for(int x=0; x < 0xff; x++)
	{
		InList[x] = 0;
		Repeated[x] = false;
	}

	while(Input->good())
	{
	    char current = (char)Input->get();
		if(!Input->good())
		{
			break;
		}

	    if(Repeated[current] == true)
	    {
	    	continue;
	    }
	    else if(InList[current] != 0)
	    {
	    	Repeated[current] = true;
	    	UniqueChars.Remove(InList[current]);
	    	InList[current] = 0;
	    }
	    else
	    {
	    	UniqueChars.AddBack(current);
	    	InList[current] = UniqueChars.GetTail();
	    }
	}
	char firstUnique = ' ';
	if(!UniqueChars.IsEmpty())
	{
		firstUnique = UniqueChars.PopFront();
	}
	return firstUnique;

}
