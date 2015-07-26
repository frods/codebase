#ifndef LONGESTCOMMONSUBSTRING
#define LONGESTCOMMONSUBSTRING

#include <string>

const int UpperOffset = 'a' - 'A';
char ToUpper(char input);

const char *LongestCommonSubstring(std::string String1, std::string String2);

#endif