#include "ListImpl.h"

#include <stdio.h> // fot printf

void ListInit(char*** list, int length)
{
	*list = (char**)malloc((sizeof(char*) * length + 1) + sizeof(NULL));

	for (int i = 0; i < length; i++)
	{
		*(*(list + i)) = (char*)malloc(sizeof(char) * 32);
		// to initialize or not to initialize?
		*list[i] = "test";
	}

	// end of list
	*list[length] = NULL;
}

void ListDestroy(char** list)
{
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

int ListSize(char** list)
{
	size_t count = 0;
	while (!list[count] == NULL)
		count++;

	return count;
}

int ListIndexOf(char** list, char* str)
{
	return 0;
}
