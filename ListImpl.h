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

// Initialize a list, set length+1 item to NULL
void ListInit(char*** list, int length = 16);
// Destroy list and set pointer to NULL
void ListDestroy(char*** list);

// prints list
void PrintList(char** list);

// Inserts value at the end of the list
void ListAdd(char*** list, char* str);
// Removes all occurrences of str in the list
void ListRemove(char** list, char* str);

// Returns the capacity of the list
inline int ListCapacity(char** list);
// Returns the number of items in the list
inline int ListSize(char** list);
// Returns the index position of the first occurrence of str in the list
int ListIndexOf(char** list, char* str);

// Removes duplicate entries from the list
void ListRemoveDuplicates(char** list);
// Sorts the list of strings in ascending order
void ListSort(char** list);
// Replaces every occurrence of the before, in each of the string lists's strings, with after
void ListReplaceInStrings(char** list, char* before, char* after);