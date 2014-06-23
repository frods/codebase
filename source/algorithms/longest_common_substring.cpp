#include "longest_common_substring.h"

char ToUpper(char input)
{
	char output = input;
	if(input >= 'a' && input <= 'z')
	{
		output -= UpperOffset;
	}
	return output;
}

const char *LongestCommonSubstring(std::string String1, std::string String2)
{
	std::string LongestSubstring;

	int String1Idx = 0;
	int String2Idx = 0;
	std::string CurrentSubstring;
	int String2CurrentStart = String2Idx;
	while(String1Idx < String1.length() && String2Idx < String2.length())
	{
		char String1Char = ToUpper(String1[String1Idx]);
		char String2Char = ToUpper(String2[String2Idx]);
		if(String1Char == String2Char)
		{
			// In a substring advance both indexes
			if(CurrentSubstring.length() == 0)
			{
				// Track where this substring started in 2 so 
				// it can be rechecked when the substring ends
				String2CurrentStart = String2Idx;
			}
			CurrentSubstring += String1Char;
			String1Idx++;
			String2Idx++;
		}
		else if(CurrentSubstring.length() > 0)
		{
			// At the end of a substring reset counters and store if 
			// longer than previous substring
			if(LongestSubstring.length() < CurrentSubstring.length())
			{
				LongestSubstring = CurrentSubstring;
			}
			CurrentSubstring.clear();
			String2Idx = String2CurrentStart;			
		}
		else if(String1Idx == String1.length() - 1)
		{
			// Reached the end of String1 advance to next char in String2
			// Reset String1Idx
			String2Idx++;
			String1Idx = 0;
		}
		else
		{
			// char at String1Idx doesn't match char at String2Idx
			// Check if next char in String1 starts a substring
			String1Idx++;
		}
	}
	if(LongestSubstring.length() < CurrentSubstring.length())
	{
		LongestSubstring = CurrentSubstring;
	}
	return LongestSubstring.c_str();
}