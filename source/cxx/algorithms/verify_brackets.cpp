#include "verify_brackets.h"
#include "../containers/lists/linked_list.h"

bool VerifyBrackets(std::string String)
{
	LinkedList<char> OpenBrackets;
	for(int StringIdx = 0; StringIdx < String.length(); StringIdx++)
	{
		char ExpectedOpen = 0;
		switch(String[StringIdx])
		{
			case '(':
			case '[':
			case '<':
			case '{':
				OpenBrackets.AddFront(String[StringIdx]);
				break;
			case ')':
				ExpectedOpen = '(';
				break;
			case ']':
				ExpectedOpen = '[';
				break;
			case '>':
				ExpectedOpen = '<';
				break;
			case '}':
				ExpectedOpen = '}';
				break;
		}
		if(ExpectedOpen != 0)
		{
			if(OpenBrackets.PeekFront() != ExpectedOpen)
			{
				return false;
			}
			OpenBrackets.PopFront();
		}
	}
	if(!OpenBrackets.IsEmpty())
	{

	}
	return OpenBrackets.IsEmpty();
}