#pragma once

#include <stdlib.h>
#include <string.h>

#define STR_MAX_LEN 32

#include <iostream> 
using std::cout;
using std::endl;
using std::cin;

inline void MemFailed()
{
	cout << "Memory trouble!\n";
	system("pause");
	exit(-1);
}

// Creates a list
char** ListCreate(unsigned int length = 16);
// Destroy list and set pointer to NULL
void ListDestroy(char*** list);

// prints list
void PrintList(char** const list);										

// Inserts value at the end of the list
void ListAdd(char*** list, const char* const str);
// Removes first same string from end of the list
void ListRemove(char** const list, const char* const str);

// Returns the capacity of the list
inline int ListCapacity(char** const list);
// Returns the number of strings in the list
inline int ListSize(char** const list);
// Returns the index position of the first occurrence of str in the list
int ListIndexOf(char** const list, char* str);

// Removes duplicate entries from the list
void ListRemoveDuplicates(char** const list);
// Sorts the list of strings in ascending order
void ListSort(char** const list);
// Replaces every occurrence of the before, in each of the string lists's strings, with after
void ListReplaceInStrings(char** const list, const char* const before, const char* const after);