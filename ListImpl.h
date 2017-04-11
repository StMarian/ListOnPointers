#pragma once
#include <stdlib.h>
#include <string.h>
#include <stdio.h> // for printf
#include <iostream> // for cout, cin, endl

#define DEFAULT_LIST_INIT_SIZE 16

// System warnings and info
inline void Info(char const* const info) { std::cout << info << std::endl; }

// Initialise a list
void ListInitialize(char*** list, unsigned int length = DEFAULT_LIST_INIT_SIZE);
// Destroy list and set pointer to nullptr
void ListDestroy(char*** list);

// Prints list
void PrintList(const char* const* list);										

// Inserts value at the end of the list
void ListAdd(char*** list, const char* const str);
// Removes first same string from end of the list
void ListRemove(char** const list, char* const str);

// Returns the capacity of the list
inline int get_ListCapacity(const char* const* list) { return (int)(*(list - 2)); }
// Returns the number of strings in the list
inline int get_ListSize(const char* const* list) { return (int)(*(list - 1)); }
// Returns the index position of the first occurrence of str in the list
int ListIndexOf(const char* const* list, char* str);

// Removes duplicate entries from the list
void ListRemoveDuplicates(char** const list);
// Sorts the list of strings in ascending order
void ListSort(char** const list);
// Replaces every occurrence of the before, in each of the string lists's strings, with after
void ListReplaceInStrings(char** const list, const char* const before, const char* const after);