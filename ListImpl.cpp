#include "ListImpl.h"

#include <stdio.h> // fot printf

void ListInit(char*** list, int length)
{
	// first 2 entries would be capacity and actual size of a list
	*list = reinterpret_cast<char**>(calloc(length + 2, sizeof(char*)));

	*(list)[0] = reinterpret_cast<char*>(calloc(1, sizeof(char)));
	*(list)[1] = reinterpret_cast<char*>(calloc(1, sizeof(char)));	// trouble here
	
	for (int i = 2; i < length + 2; i++)
	{
		*(list)[i] = reinterpret_cast<char*>(calloc(32, sizeof(char)));
	}
}

void ListDestroy(char*** list)
{
	for (int i = 0; i < ListCapacity(*list); i++)
	{
		free(*list[i]);
	}

	free(*list);
}

void PrintList(char** list)
{
	// TODO: use ListSize();
	for (int i = 0; list[i] != NULL; i++) {
		printf("Line #%d(length: %lu): %s\n", i, strlen(list[i]), list[i]);
	}
}

void ListAdd(char** list, char* str)
{
}

void ListRemove(char** list, char* str)
{
}

int ListCapacity(char** list)
{
	return list[0][0];
}

int ListSize(char** list)
{
	return list[1][0];
}

int ListIndexOf(char** list, char* str)
{
	return 0;
}
