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
	if (ListSize(list) == 0)
	{
		cout << "List is empty!" << endl;
		return;
	}

	cout << "Capacity of a list: " << ListCapacity(list) << "| strings in list: " << ListSize(list) << endl;

	for (int i = 2; i < ListSize(list) + 2; i++)
		printf("String #%d(length: %lu): %s\n", i - 2, strlen(list[i]), list[i]);
} 

void ListAdd(char** list, char* str)
{
	// TODO reallocate
	if (ListSize(list) == ListCapacity(list))
	{
		cout << "No place in list!" << endl;
		return;
	}
	
	// size increased
	list[1][0]++;

	memcpy(list[1 + ListSize(list)], str, sizeof(str));

}

void ListRemove(char** list, char* str)
{
	for (int i = 2; i < ListSize(list) + 2; i++)
	{
		if (!strcmp(list[i], str))	// strcmp returns 0 when strings are equal
		{
			//list[i] = NULL;
			list[1][0]--;

			// shift right part of an array
			for (int j = i; j < ListSize(list) + 2; j++)
			{
				memcpy(list[j], list[j + 1], sizeof(list[j + 1]));
			}
		}
	}
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
