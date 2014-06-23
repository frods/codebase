/*
Test harness for algorithms
*/

#include <sstream>

#include "first_unique.h"
#include "longest_common_substring.h"
#include "verify_brackets.h"

int main(int argc, const char *argv[])
{
	std::istringstream Input("asldkgjalscdgjqwel;rkjwq;erj");
	printf("First Unique character %c\n", FirstUnique(&Input));

	std::string String1("abc");
	std::string String2("ababc");
	printf("\nLongest Common Substring %s %s\n", String1.c_str(), String2.c_str());
	const char *LongestSubstring = LongestCommonSubstring(String1, String2);
	printf("Found %s\n", LongestSubstring);
	String1 = "Victory";
	String2 = "asdfvicasdf";
	printf("Longest Common Substring %s %s\n", String1.c_str(), String2.c_str());
	LongestSubstring = LongestCommonSubstring(String1, String2);
	printf("Found %s\n", LongestSubstring);

	std::string BracketTest("(([()]))");
	printf("\nVerify Brackets of %s: %i\n", BracketTest.c_str(), VerifyBrackets(BracketTest));
	BracketTest = "(([(])))";
	printf("\nVerify Brackets of %s: %i\n", BracketTest.c_str(), VerifyBrackets(BracketTest));
	BracketTest = "(((([])))";
	printf("\nVerify Brackets of %s: %i\n", BracketTest.c_str(), VerifyBrackets(BracketTest));
	BracketTest = "(([])))";
	printf("\nVerify Brackets of %s: %i\n", BracketTest.c_str(), VerifyBrackets(BracketTest));

	return 0;
}
